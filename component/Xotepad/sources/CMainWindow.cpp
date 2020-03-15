
#include "CMainWindow.hpp"
#include "MainWindowPresenter.hpp"


void CMainWindow::displayTitle(const std::string &title) {
    SetTitle(title.c_str());
}


void CMainWindow::displayContent(const std::string &content) {
    editorView.SetWindowTextA(content.c_str());
}


MainWindow::DialogResult CMainWindow::showMessageBoxModal(const std::string &title, const std::string &message, const DialogButtons buttons, const DialogIcon icon) {
    UINT type = 0;

    switch (buttons) {
        case DialogButtons::Ok: type |= MB_OK;
        case DialogButtons::YesNo: type |= MB_YESNO;
        case DialogButtons::YesNoCancel: type |= MB_YESNOCANCEL;
    }

    switch (icon) {
        case DialogIcon::Question: type |= MB_ICONQUESTION;
    }

    int result = MessageBox(message.c_str(), title.c_str(), type);

    switch (result) {
        case IDOK: return DialogResult::Ok;
        case IDCANCEL: return DialogResult::Cancel;
        case IDYES: return DialogResult::Yes;
        case IDNO: return DialogResult::No;
    }
    
    return DialogResult::Cancel;
}


std::optional<std::string> CMainWindow::showFilePickModal(const std::string &title) {
    const CString filter = _T("All Files (*.*)|*.*||");
    const DWORD flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST  | OFN_HIDEREADONLY | OFN_SHOWHELP | OFN_EXPLORER | OFN_ENABLESIZING;
        
    CFileDialog fileDlg(TRUE, NULL, 0, flags, filter);

    fileDlg.SetTitle(title.c_str());

    if (fileDlg.DoModal(*this) == IDCANCEL) {
        return {};
    }

    CString fileName = fileDlg.GetPathName();

    return std::string(fileName.c_str());
}


void CMainWindow::clearContent() {
    editorView.SetWindowTextA("");
}


CMainWindow::CMainWindow(MainWindowPresenter *presenter) : MainWindow(presenter) {
    this->SetView(editorView);
}


CMainWindow::~CMainWindow() {}


void CMainWindow::OnDestroy() { 
    PostQuitMessage(0); 
}


int CMainWindow::OnCreate(CREATESTRUCT& cs) {
    UseIndicatorStatus(FALSE);   // Don't show keyboard indicators in the StatusBar
    UseMenuStatus(FALSE);        // Don't show menu descriptions in the StatusBar
    UseReBar(FALSE);             // Don't use a ReBar
    UseStatusBar(FALSE);         // Don't use a StatusBar
    UseThemes(FALSE);            // Don't use themes
    UseToolBar(FALSE);           // Don't use a ToolBar

    CFrame::OnCreate(cs);

    this->setupMenuBar();

    getPresenter()->attachView(this);
    
    return 0;
}


BOOL CMainWindow::OnCommand(WPARAM wparam, LPARAM lparam) {
    const UINT id = LOWORD(wparam);
    const UINT nc = HIWORD(wparam);

    switch (id) {
        case IDM_FILE_NEW: getPresenter()->handleFileNew(); return FALSE;
        case IDM_FILE_OPEN: getPresenter()->handleFileOpen(); return FALSE;
        case IDM_FILE_SAVE: getPresenter()->handleFileSave(); return FALSE;
        case IDM_FILE_SAVEAS: getPresenter()->handleFileSaveAs(); return FALSE;
        case IDM_FILE_EXIT: getPresenter()->handleFileExit(); return FALSE;
        case IDM_EDIT_UNDO: getPresenter()->handleEditUndo(); return FALSE;
        case IDM_EDIT_REDO: getPresenter()->handleEditRedo(); return FALSE;
        case IDM_EDIT_CUT: getPresenter()->handleEditCut(); return FALSE;
        case IDM_EDIT_COPY: getPresenter()->handleEditCopy(); return FALSE;
        case IDM_EDIT_PASTE: getPresenter()->handleEditPaste(); return FALSE;
        case IDM_EDIT_SELECTALL: getPresenter()->handleEditSelectAll(); return FALSE;
        case IDM_EDIT_FINDREPLACE: getPresenter()->handleEditFindReplace(); return FALSE;
        case IDM_HELP_ABOUT: getPresenter()->handleHelpAbout(); return FALSE;
    }

    if (nc == EN_CHANGE && lparam == (LPARAM)editorView.GetHwnd()) {
        getPresenter()->handleContentModified();
    }

    return FALSE;
}


void CMainWindow::setupMenuBar() {
    HMENU hFileMenu = CreateMenu();
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_NEW, "New");
    ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_OPEN, "Open");
    ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVE, "Save");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVEAS, "Save As");
    ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_EXIT, "Exit");

    HMENU hEditMenu = CreateMenu();
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_UNDO, "Undo");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_REDO, "Redo");
    ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_CUT, "Cut");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_COPY, "Copy");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_PASTE, "Paste");
    ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_SELECTALL, "Select All");
    ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_FINDREPLACE, "Find/Replace ...");

    HMENU hHelpMenu = CreateMenu();
    ::AppendMenu(hHelpMenu, MF_STRING, 0, "About ...");

    HMENU hMenuBar = CreateMenu();
    ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEditMenu, "Edit");
    ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");

    this->SetMenu(hMenuBar);
}
