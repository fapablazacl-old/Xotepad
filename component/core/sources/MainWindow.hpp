
#pragma once 

#include <string>
#include <optional>
#include <vector>

#include "Document.hpp"


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


struct FileFilter {
    std::string id;
    std::string caption;
    std::vector<std::string> wildcards;
};

class FindReplaceDialog;

class MainWindowPresenter;
class MainWindow {
public:
    explicit MainWindow(MainWindowPresenter *presenter) {
        this->presenter = presenter;
    }

    virtual ~MainWindow();

    virtual void setTitle(const std::string &title) = 0;

    virtual DialogResult showMessageBoxModal(const std::string &title, const std::string &message, const DialogButtons buttons, const DialogIcon icon) = 0;

    virtual std::optional<std::string> showFilePickModal(FileDialog type, const std::string &title, const std::vector<FileFilter> &filters) = 0;

    virtual void terminateApp() = 0;

    virtual Document* getDocument() = 0;

    virtual FindReplaceDialog* getFindReplace() = 0;

protected:
    MainWindowPresenter *getPresenter() {
        return presenter;
    }

private:
    MainWindowPresenter *presenter = nullptr;
};
