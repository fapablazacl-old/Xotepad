
#pragma once 

#include <string>
#include <optional>
#include <vector>


enum class DialogResult {
    Ok, Cancel, Yes, No
};


enum class DialogButtons {
    Ok,
    YesNo,
    YesNoCancel
};


enum class DialogIcon {
    Question
};


enum class FileDialog {
    Open, Save
};


struct TextSelection {
    int start;
    int end;

    static TextSelection all() {
        return {-1, -1};
    }
};


struct Font {
    const std::string &family;
    const int size;
};


struct FileFilter {
    std::string id;
    std::string caption;
    std::vector<std::string> wildcards;
};


enum class Lexer {
    Text,
    Clike,
    CMake
};


enum ClikeToken {
    CLIKE_COMMENT,
    CLIKE_COMMENTLINE,
    CLIKE_COMMENTDOC,
    CLIKE_NUMBER,
    CLIKE_WORD,
    CLIKE_STRING,
    CLIKE_CHARACTER,
    CLIKE_UUID,
    CLIKE_PREPROCESSOR,
    CLIKE_OPERATOR,
    CLIKE_IDENTIFIER,
    CLIKE_STRINGEOL,
    CLIKE_VERBATIM,
    CLIKE_REGEX,
    CLIKE_COMMENTLINEDOC,
    CLIKE_WORD2,
    CLIKE_COMMENTDOCKEYWORD,
    CLIKE_COMMENTDOCKEYWORDERROR,
    CLIKE_GLOBALCLASS,
    CLIKE_STRINGRAW,
    CLIKE_TRIPLEVERBATIM,
    CLIKE_HASHQUOTEDSTRING,
    CLIKE_PREPROCESSORCOMMENT,
    CLIKE_PREPROCESSORCOMMENTDOC,
    CLIKE_USERLITERAL,
    CLIKE_TASKMARKER,
    CLIKE_ESCAPESEQUENCE
};


struct Color {
    unsigned char r = 0, g = 0, b = 0;
};


struct TokenStylingInformation {
    int tokenCode;
    Color color;
};


struct LexerConfiguration {
    Lexer lexer;
    std::vector<std::string> keywords;
    std::vector<TokenStylingInformation> tokenStyle;
};


class MainWindowPresenter;
class MainWindow {
public:
    explicit MainWindow(MainWindowPresenter *presenter) {
        this->presenter = presenter;
    }

    virtual ~MainWindow();

    virtual void setTitle(const std::string &title) = 0;

    virtual void setContent(const std::string &content) = 0;

    virtual std::string getContent() const = 0;

    virtual void clearContent() = 0;

    virtual DialogResult showMessageBoxModal(const std::string &title, const std::string &message, const DialogButtons buttons, const DialogIcon icon) = 0;

    virtual std::optional<std::string> showFilePickModal(FileDialog type, const std::string &title, const std::vector<FileFilter> &filters) = 0;

    virtual void terminateApp() = 0;

    virtual void setSelection(const TextSelection &selection) = 0;

    virtual void selectAll() = 0;

    virtual void clearSelection() = 0;

    virtual void undo() = 0;

    virtual void redo() = 0;

    virtual void cut() = 0;

    virtual void copy() = 0;

    virtual void paste() = 0;

    virtual TextSelection getSelection() const = 0;

    virtual void setFont(const Font &font) = 0;

    virtual Font getFont() const = 0;

    virtual void applyLexer(const LexerConfiguration &value) = 0;

protected:
    MainWindowPresenter *getPresenter() {
        return presenter;
    }

private:
    MainWindowPresenter *presenter = nullptr;
};
