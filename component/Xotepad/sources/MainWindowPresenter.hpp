
#pragma once

#include <optional>
#include <string>

class MainWindow;
class MainWindowPresenter {
public:
    enum class AfterCheckAction {
        Stop,
        Continue
    };

public:
    void attachView(MainWindow *view);

    AfterCheckAction checkDocumentChanges();

    void handleContentModified();

    void handleFileNew();

    void handleFileOpen();

    int handleFileSave() {
        return 0;
    }

    int handleFileSaveAs() {
        return 0;
    }

    void handleFileExit() {
    }

    void handleEditUndo() {
    }

    void handleEditRedo() {
    }

    void handleEditCut() {
    }

    void handleEditCopy() {
    }

    void handleEditPaste() {
    }

    void handleEditSelectAll() {
    }

    void handleEditFindReplace() {
    }

    void handleHelpAbout() {
    }

private:
    std::string getDocumentName() const;

    std::string computeTitle(const std::string &documentName) const;

    void updateTitle();

    void loadFile(const std::string &fileName);

private:
    MainWindow *view = nullptr;

    std::optional<std::string> documentFileName;
    bool documentDirty = false;
    int documentCount = 1;

    const std::string appTitle = "Xotapad";
    const std::string untitledTitle = "Untitled";
};
