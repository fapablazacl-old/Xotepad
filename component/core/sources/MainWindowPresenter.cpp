
#include "MainWindowPresenter.hpp"
#include "MainWindow.hpp"
#include "FileService.hpp"
#include "WindowsUtils.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/optional/optional.hpp>


class LexerConfigurationService {
public:
    LexerConfiguration getConfiguration(const std::string &languageId) const {
        if (languageId == "c++") {
            LexerConfiguration config;

            config.lexer = Lexer::Clike;

            config.keywords = {
                "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", 
                "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char",
                "char16_t", "char32_t", "class", "compl", "concept", "const", "constexpr", "const_cast", 
                "continue", "decltype", "default", "delete", "do",
                "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float", 
                "for", "friend", "goto", "if", "inline", "int", "import", "long",
                "module", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", 
                "or", "or_eq", "private", "protected", "public",
                "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static", 
                "static_assert", "static_cast", "struct",
                "switch", "synchronized", "template", "this", "thread_local", 
                "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned",
                "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
            };

            config.tokenStyle = {
                {CLIKE_COMMENT, Color{0, 125, 0}}, 
                {CLIKE_COMMENTLINE, Color{0, 125, 0}}, 
                {CLIKE_COMMENTDOC, Color{0, 125, 0}}, 
                {CLIKE_NUMBER, Color{0, 0, 0}}, 
                {CLIKE_WORD, Color{0, 0, 255}},
                {CLIKE_STRING, {125, 0, 0}}, 
                {CLIKE_CHARACTER, {125, 0, 0}}, 
                {CLIKE_UUID, {0, 0, 0}}, 
                {CLIKE_PREPROCESSOR, {160, 0, 255}}, 
                {CLIKE_OPERATOR, {0, 0, 0}}, 
                {CLIKE_IDENTIFIER, {0, 0, 0}}, 
                {CLIKE_STRINGEOL, {0, 0, 0}}, 
                {CLIKE_VERBATIM, {0, 0, 0}}, 
                {CLIKE_REGEX, {0, 0, 0}}, 
                {CLIKE_COMMENTLINEDOC, {0, 0, 0}}, 
                {CLIKE_WORD2, {0, 0, 0}}, 
                {CLIKE_COMMENTDOCKEYWORD, {0, 0, 0}}, 
                {CLIKE_COMMENTDOCKEYWORDERROR, {0, 0, 0}}, 
                {CLIKE_GLOBALCLASS, {0, 0, 0}}, 
                {CLIKE_STRINGRAW, {0, 0, 0}}, 
                {CLIKE_TRIPLEVERBATIM, {0, 0, 0}}, 
                {CLIKE_HASHQUOTEDSTRING, {0, 0, 0}}, 
                {CLIKE_PREPROCESSORCOMMENT, {0, 0, 0}}, 
                {CLIKE_PREPROCESSORCOMMENTDOC, {0, 0, 0}}, 
                {CLIKE_USERLITERAL, {0, 0, 0}}, 
                {CLIKE_TASKMARKER, {0, 0, 0}}, 
                {CLIKE_ESCAPESEQUENCE, {0, 0, 0}}
            };

            return config;
        }

        return {
            Lexer::Text, {""}, {}
        };
    }
};


void MainWindowPresenter::attachView(MainWindow *view) {
    this->view = view;
    this->view->setFont(Font{"Consolas", 14});

    documentDirty = false;
    this->updateTitle();
}


void MainWindowPresenter::handleContentModified() {
    documentDirty = true;
    this->updateTitle();
}


AfterCheckAction MainWindowPresenter::checkDocumentChanges() {
    if (documentDirty) {
        auto result = view->showMessageBoxModal(
            appTitle.c_str(), 
            "Current file was modified. Do you want to save it?", 
            DialogButtons::YesNoCancel, 
            DialogIcon::Question
        );

        if (result == DialogResult::Cancel) {
            return AfterCheckAction::Stop;
        }

        if (result == DialogResult::Yes) {
            this->handleFileSave();
        }
    }

    return AfterCheckAction::Continue;
}


void MainWindowPresenter::handleFileNew() {
    if (auto action = this->checkDocumentChanges(); action == AfterCheckAction::Stop) {
        return;
    }

    this->newFile();
}


DialogUserOutcome MainWindowPresenter::handleFileSave() {
    if (documentFileName) {
        this->saveFile(*documentFileName, view->getContent());

        return DialogUserOutcome::Accept;
    }

    return this->handleFileSaveAs();
}


std::vector<FileFilter> enumerateFilters() {
    return {
        FileFilter{"c++", "C/C++ Files", {"*.c", "*.cpp", "*.cxx", "*.c++", "*.cc", "*.h", "*.hpp", "*.hxx", "*.h++", "*.hh"}},
        FileFilter{"gl", "OpenGL Shader Files", {"*.glsl", "*.vert", "*.frag"}},
        FileFilter{"cl", "OpenCL C Files", {"*.cl"}},
        FileFilter{"cmake", "CMake Files", {"CMakeLists.txt", "*.cmake", "CMakeCache.txt"}},
        FileFilter{"", "All Files", {"*.*"}}
    };
}


boost::optional<FileFilter> matchFileFilter(const std::vector<FileFilter> &filters, const std::string &fileName) {
    for (const FileFilter &filter : filters) {
        for (const std::string &wildcard : filter.wildcards) {
            if (wildcard_match(wildcard.c_str(), fileName.c_str())) {
                return filter;
            }
        }
    }

    return {};
}


Lexer fileType2Lexer(const std::string &fileType) {
    if (fileType == "c++" || fileType == "gl" || fileType == "cl") {
        return Lexer::Clike;
    }

    if (fileType == "cmake") {
        return Lexer::CMake;
    }
    
    return Lexer::Text;
}


DialogUserOutcome MainWindowPresenter::handleFileSaveAs() {
    const std::vector<FileFilter> filters = enumerateFilters();

    if (auto result = view->showFilePickModal(FileDialog::Save, appTitle + " - Save File ...", filters); result) {
        const std::string fileName = *result;
        const std::string content = view->getContent();

        this->saveFile(fileName, content);

        return DialogUserOutcome::Accept;
    }

    return DialogUserOutcome::Cancel;
}


void MainWindowPresenter::newFile() {
    view->clearContent();

    documentFileName.reset();
    documentDirty = false;
    documentCount ++;

    this->updateTitle();
}


void MainWindowPresenter::handleFileOpen() {
    if (auto action = this->checkDocumentChanges(); action == AfterCheckAction::Stop) {
        return;
    }

    const std::vector<FileFilter> filters = enumerateFilters();

    if (auto fileName = view->showFilePickModal(FileDialog::Open, appTitle + " - Open File ...", filters)) {
        this->loadFile(*fileName);
    }
}


std::string MainWindowPresenter::getDocumentTitle() const {
    std::string title;

    if (documentFileName) {
        title = *documentFileName;
    } else {
        title = untitledTitle + " " + std::to_string(documentCount);
    }

    return title + (documentDirty ? "*" : "");
}


std::string MainWindowPresenter::computeTitle(const std::string &documentTitle) const {
    return appTitle + " - " + documentTitle;
}


void MainWindowPresenter::updateTitle() {
    view->setTitle(computeTitle(getDocumentTitle()).c_str());
}


void MainWindowPresenter::loadFile(const std::string &fileName) {
    const FileService fileService;
    const std::string content = fileService.loadFile(fileName.c_str());

    this->documentFileName = fileName;
    this->documentDirty = false;
    
    const auto fileFilter = matchFileFilter(enumerateFilters(), boost::filesystem::path(fileName).filename().string());
    const LexerConfigurationService lexerService;
    const auto lexerConfig = lexerService.getConfiguration(fileFilter->id);

    view->applyLexer(lexerConfig);
    view->setContent(content);

    this->updateTitle();
}


void MainWindowPresenter::saveFile(const std::string &fileName, const std::string &content) {
    FileService fileService;
    fileService.saveFile(fileName.c_str(), content.c_str());

    this->documentFileName = fileName;
    this->documentDirty = false;
    
    this->updateTitle();
}


void MainWindowPresenter::handleFileExit() {
    this->handleCloseRequested();
}


void MainWindowPresenter::handleCloseRequested() {
    if (auto action = this->checkDocumentChanges(); action == AfterCheckAction::Stop) {
        return;
    }

    view->terminateApp();
}


void MainWindowPresenter::handleEditUndo() {
    view->undo();
}


void MainWindowPresenter::handleEditRedo() {
    view->redo();
}


void MainWindowPresenter::handleEditCut() {
    view->cut();
}


void MainWindowPresenter::handleEditCopy() {
    view->copy();
}


void MainWindowPresenter::handleEditPaste() {
    view->paste();
}


void MainWindowPresenter::handleEditSelectAll() {
    view->selectAll();
}


void MainWindowPresenter::handleEditFindReplace() {

}


void MainWindowPresenter::handleHelpAbout() {

}
