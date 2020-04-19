
#pragma once 

#include <string>
#include <fstream>
#include <optional>
#include <cassert>

#include <atlbase.h>
#include <atlapp.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atluser.h>
#include <atlcrack.h>
#include <atlsplit.h>
#include <atlmisc.h>

#include "MainWindow.hpp"
#include "CDocument.hpp"
#include "CMyFindReplaceDialog.hpp"


class CMainWindow : public CWindowImpl<CMainWindow, CWindow, CFrameWinTraits>, public MainWindow {
public:
    DECLARE_WND_CLASS(_T("CMainWindow"))
    BEGIN_MSG_MAP(CMainWindow)
        COMMAND_CODE_HANDLER(0, OnCommand)

        MSG_WM_CREATE(OnCreate)
        MSG_WM_CLOSE(OnClose)
        // MSG_WM_DESTROY(OnDestroy)
        MSG_WM_SIZE(OnSize)
        MSG_WM_NOTIFY(OnNotify)
    END_MSG_MAP()

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

    int OnCommand(WORD wNotifyCode  , WORD wID, HWND hWndCtrl, BOOL &bHandled);

    int OnCreate(LPCREATESTRUCT lpCreateStruct);

    void OnClose();

    // void OnDestroy();

    void OnSize(UINT nType, CSize size);

    LRESULT OnNotify(int idCtrl, LPNMHDR pnmh);

public:
    virtual void terminateApp() override;

    virtual void setTitle(const std::string &title) override;

    virtual DialogResult showMessageBoxModal(const std::string &title, const std::string &message, const DialogButtons buttons, const DialogIcon icon) override;

    virtual std::optional<std::string> showFilePickModal(FileDialog type, const std::string &title, const std::vector<FileFilter> &filters) override;

    virtual Document* getDocument() override;

    virtual FindReplaceDialog* getFindReplace() override;

private:
    void SetupMenuBar();

    void SetupDocumentEditor();

private:
    CDocument documentView;
    CFindReplaceDialog findReplaceDialog;
};
