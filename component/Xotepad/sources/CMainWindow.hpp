
#pragma once 

#include <wxx_wincore.h>
#include <wxx_frame.h>
#include <wxx_menubar.h>
#include <wxx_menu.h>
#include <wxx_commondlg.h>

#include <string>
#include <fstream>
#include <optional>

#include "MainWindow.hpp"

class CEditorView : public CEdit {
public:
    virtual void PreCreate(CREATESTRUCT& cs) override {
        cs.style = cs.style | WS_VSCROLL | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN;
    }
};


class CMainWindow : public CFrame, public MainWindow {
private:
    enum  {
        IDM_FILE_NEW = 1000, 
        IDM_FILE_OPEN, 
        IDM_FILE_SAVE, 
        IDM_FILE_SAVEAS, 
        IDM_FILE_EXIT, 

        IDM_EDIT_UNDO = 2000, 
        IDM_EDIT_REDO, 
        IDM_EDIT_CUT, 
        IDM_EDIT_COPY, 
        IDM_EDIT_PASTE, 
        IDM_EDIT_SELECTALL, 
        IDM_EDIT_FINDREPLACE,

        IDM_HELP_ABOUT = 3000,

        IDC_EDITOR_CONTROL = 10000
    };

public:
    CMainWindow(MainWindowPresenter *presenter);

    virtual ~CMainWindow();

    virtual void OnDestroy();

    virtual int OnCreate(CREATESTRUCT& cs) override;

    virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam) override;

public:
    virtual void displayTitle(const std::string &title) override;

    virtual void displayContent(const std::string &content) override;

    virtual void clearContent() override;

    virtual DialogResult showMessageBoxModal(const std::string &title, const std::string &message, const DialogButtons buttons, const DialogIcon icon) override;

    virtual std::optional<std::string> showFilePickModal(const std::string &title) override;

private:
    void setupMenuBar();

private:
    CEditorView editorView;
};
