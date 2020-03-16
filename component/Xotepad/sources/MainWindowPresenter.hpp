
#pragma once

#include <optional>
#include <string>

enum class AfterCheckAction {
    Stop,
    Continue
};


enum class DialogUserOutcome {
    Cancel,
    Accept
};


class MainWindow;
class MainWindowPresenter {
public:
    void attachView(MainWindow *view);

    AfterCheckAction checkDocumentChanges();

    void handleContentModified();

    void handleFileNew();

    void handleFileOpen();

    DialogUserOutcome handleFileSave();

    DialogUserOutcome handleFileSaveAs();

    void handleFileExit();

    void handleCloseRequested();

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
    std::string getDocumentTitle() const;

    std::string computeTitle(const std::string &documentName) const;

    void updateTitle();

    void loadFile(const std::string &fileName);

    void saveFile(const std::string &fileName, const std::string &content);

    void newFile();

private:
    MainWindow *view = nullptr;

    std::optional<std::string> documentFileName;
    bool documentDirty = false;
    int documentCount = 1;

    const std::string appTitle = "Xotapad";
    const std::string untitledTitle = "Untitled";
};
