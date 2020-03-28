
#include "MainWindowPresenter.hpp"
#include "MainWindow.hpp"
#include "FileService.hpp"
#include <boost/filesystem/path.hpp>

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
        FileFilter{"cpp", "C/C++ Files", {"*.c", "*.cpp", "*.cxx", "*.c++", "*.cc", "*.h", "*.hpp", "*.hxx", "*.h++", "*.hh"}},
        FileFilter{"gl", "OpenGL Shader Files", {"*.glsl", "*.vert", "*.frag"}},
        FileFilter{"cl", "OpenCL C Files", {"*.cl"}},
        FileFilter{"asm", "Assembly Files", {"*.asm"}},
        FileFilter{"cmake", "CMake Files", {"CMakeLists.txt", "*.cmake", "CMakeCache.txt"}},
        FileFilter{"", "All Files", {"*.*"}}
    };
}


bool wildcard_match(const char * wildcard, char * const name) {
    const size_t len = std::strlen(wildcard);

    char *ch = name;

    for (size_t i=0; i<len; i++) {
        const char wc_token = wildcard[i];

        switch (wc_token) {
        case '?':
            if (*ch == '\0') {
                return false;
            }
            ++ch;

            break;

        case '*':

            break;

        default:
            if (*ch != wc_token) {
                return false;
            }
            ++ch;

            break;
        }
    }

    return *ch == '\0';
}


FileFilter matchFileFilter(const std::vector<FileFilter> &filters, const std::string &fileName) {
    for (const FileFilter &filter : filters) {
        for (const std::string &wildcard : filter.wildcards) {
            if (wildcard.find('*') == std::string::npos) {
                if (wildcard == fileName) {
                    return filter;
                }
            } else {
                // extract ext and base from fileName (requires boost!)
                std::string fileTitle = boost::filesystem::path(fileName).stem().string();
                std::string fileExtension = boost::filesystem::path(fileName).extension().string();

                const int pos = wildcard.find('.');

                if (pos == std::string::npos) {
                    const std::string part1 = wildcard.substr(0, pos);
                    const std::string part2 = wildcard.substr(pos);
                } else {
                    
                }
            }
        }
    }
}


Lexer fileType2Lexer(const std::string &fileType) {
    if (fileType == "cpp") return Lexer::Clike;
    if (fileType == "cmake") return Lexer::CMake;
    
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