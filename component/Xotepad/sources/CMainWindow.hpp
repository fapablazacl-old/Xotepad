
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
#include "CEditorView.hpp"

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

    // virtual void OnDestroy() override;

    virtual void OnClose() override;

    virtual int OnCreate(CREATESTRUCT& cs) override;

    virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam) override;

    virtual void terminateApp() override;

public:
    virtual void setTitle(const std::string &title) override;

    virtual void setContent(const std::string &content) override;

    virtual std::string getContent() const override;

    virtual void clearContent() override;

    virtual DialogResult showMessageBoxModal(const std::string &title, const std::string &message, const DialogButtons buttons, const DialogIcon icon) override;

    virtual std::optional<std::string> showFilePickModal(FileDialog type, const std::string &title) override;

    virtual void setSelection(const TextSelection &selection) override;

    virtual TextSelection getSelection() const override;

    virtual void selectAll() override;

    virtual void clearSelection() override;

    virtual void undo() override;

    virtual void redo() override;

    virtual void cut() override;

    virtual void copy() override;

    virtual void paste() override;

    virtual void setFont(const Font &font) override;

    virtual Font getFont() const override;

private:
    void setupMenuBar();

private:
    CEditorView editorView;
    HFONT fontHandle = NULL;
};
