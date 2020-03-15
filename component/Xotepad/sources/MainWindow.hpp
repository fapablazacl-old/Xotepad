
#pragma once 

#include <string>
#include <optional>

class MainWindowPresenter;
class MainWindow {
public:
    explicit MainWindow(MainWindowPresenter *presenter) {
        this->presenter = presenter;
    }

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

    virtual ~MainWindow();

    virtual void displayTitle(const std::string &title) = 0;

    virtual void displayContent(const std::string &content) = 0;

    virtual void clearContent() = 0;

    virtual DialogResult showMessageBoxModal(const std::string &title, const std::string &message, const DialogButtons buttons, const DialogIcon icon) = 0;

    virtual std::optional<std::string> showFilePickModal(const std::string &title) = 0;

protected:
    MainWindowPresenter *getPresenter() {
        return presenter;
    }


private:
    MainWindowPresenter *presenter = nullptr;
};
