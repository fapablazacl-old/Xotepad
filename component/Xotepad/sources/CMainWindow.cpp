
#include "CMainWindow.hpp"
#include "MainWindowPresenter.hpp"
#include "WindowsUtils.hpp"

#include <vector>
#include <wxx_taskdialog.h>


void CMainWindow::setTitle(const std::string &title) {
    SetTitle(widen(title).c_str());
}

/*
DialogResult CMainWindow::showMessageBoxModal(const std::string &title, const std::string &message, const DialogButtons buttons, const DialogIcon icon) {
    std::wstring wtitle = widen(title);
    std::wstring wmessage = widen(message);

    CTaskDialog taskDialog;

    taskDialog.SetWindowTitle(wtitle.c_str());
    taskDialog.SetMainInstruction(wmessage.c_str());
    
    switch (buttons) {
        case DialogButtons::Ok: 
            taskDialog.SetCommonButtons(TDCBF_OK_BUTTON); 
            break;

        case DialogButtons::YesNo: 
            taskDialog.SetCommonButtons(TDCBF_YES_BUTTON | TDCBF_NO_BUTTON); 
            break;

        case DialogButtons::YesNoCancel: 
            taskDialog.SetCommonButtons(TDCBF_YES_BUTTON | TDCBF_NO_BUTTON | TDCBF_CANCEL_BUTTON); 
            break;
    }

    switch (icon) {
        case DialogIcon::Question: 
            taskDialog.SetMainIcon(TD_INFORMATION_ICON); 
            break;
    }

    taskDialog.DoModal(this->GetHwnd());
    int result = taskDialog.GetSelectedButtonID();

    switch (result) {
        case IDOK: return DialogResult::Ok;
        case IDCANCEL: return DialogResult::Cancel;
        case IDYES: return DialogResult::Yes;
        case IDNO: return DialogResult::No;
    }
    
    return DialogResult::Cancel;
}
*/


 DialogResult CMainWindow::showMessageBoxModal(const std::string &title, const std::string &message, const DialogButtons buttons, const DialogIcon icon) {
    UINT type = 0;
    std::wstring wtitle = widen(title);
    std::wstring wmessage = widen(message);

    switch (buttons) {
        case DialogButtons::Ok: 
            type |= MB_OK; 
            break;

        case DialogButtons::YesNo: 
            type |= MB_YESNO; 
            break;

        case DialogButtons::YesNoCancel: 
            type |= MB_YESNOCANCEL; 
            break;
    }

    switch (icon) {
        case DialogIcon::Question: 
            type |= MB_ICONQUESTION;
            break;
    }

    int result = MessageBox(wmessage.c_str(), wtitle.c_str(), type);

    switch (result) {
        case IDOK: return DialogResult::Ok;
        case IDYES: return DialogResult::Yes;
        case IDNO: return DialogResult::No;
        case IDCANCEL: return DialogResult::Cancel;
    }

    return DialogResult::Cancel;
}


CString ToDialogFilterString(const std::vector<std::string> &wildcards) {
    CString result;

    for (int i=0; i<wildcards.size(); i++) {
        result += wildcards[i].c_str();
        
        if (i < wildcards.size() - 1) {
            result += ";";
        }
    }

    return result;
}


CString ToDialogFilterString(const FileFilter &filter) {
    return filter.caption.c_str() + CString("|") + ToDialogFilterString(filter.wildcards);
}


CString ToDialogFilterString(const std::vector<FileFilter> &filters) {
    CString result;

    for (const FileFilter &filter : filters) {
        result += ToDialogFilterString(filter);
        result += "|";
    }

    return result;
}


std::optional<std::string> CMainWindow::showFilePickModal(FileDialog type, const std::string &title, const std::vector<FileFilter> &filters) {
    const CString filter = ToDialogFilterString(filters);
    const DWORD flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST  | OFN_HIDEREADONLY | OFN_SHOWHELP | OFN_EXPLORER | OFN_ENABLESIZING;

    CFileDialog fileDlg(type == FileDialog::Open ? TRUE : FALSE, NULL, 0, flags, filter);

    fileDlg.SetTitle(widen(title).c_str());

    if (fileDlg.DoModal(*this) == IDCANCEL) {
        return {};
    }

    CString fileName = fileDlg.GetPathName();

    return narrow(fileName.c_str());
}


void CMainWindow::terminateApp() {
    PostQuitMessage(0);
}


CMainWindow::CMainWindow(MainWindowPresenter *presenter) : MainWindow(presenter) {
    this->SetView(editorView);
}


CMainWindow::~CMainWindow() {
    if (fontHandle) {
        DeleteObject(fontHandle);
    }
}


void CMainWindow::OnClose() { 
    this->getPresenter()->handleCloseRequested();
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

    return FALSE;
}


LRESULT CMainWindow::OnNotify(WPARAM wparam, LPARAM lparam) {
    auto nmhdr = reinterpret_cast<LPNMHDR>(lparam);

    if (nmhdr->hwndFrom == editorView.GetHwnd()) {
        auto notification = reinterpret_cast<SCNotification *>(nmhdr);

        switch (nmhdr->code) {
            case SCN_MODIFIED: {
                if (notification->modificationType & SC_PERFORMED_USER) {
                    // NOTE: This gets called when we set the text via the Scintilla API ...
                    getPresenter()->handleContentModified();
                }
            }
        }
    }

    return 0;
}


void CMainWindow::setupMenuBar() {
    HMENU hFileMenu = CreateMenu();
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_NEW, L"&New\t Ctrl+N");
    ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, L"");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_OPEN, L"&Open\t Ctrl+O");
    ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, L"");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVE, L"&Save\t Ctrl+S");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVEAS, L"Save &As");
    ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, L"");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_EXIT, L"&Exit\t Alt+F4");

    HMENU hEditMenu = CreateMenu();
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_UNDO, L"&Undo\t Ctrl+Z");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_REDO, L"&Redo\t Ctrl+Shift+Z");
    ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, L"");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_CUT, L"Cu&t\t Ctrl+X");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_COPY, L"&Copy\t Ctrl+C");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_PASTE, L"&Paste\t Ctrl+V");
    ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, L"");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_SELECTALL, L"&Select All\t Ctrl+A");
    ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, L"");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_FINDREPLACE, L"&Find & Replace ...\t Ctrl+F");

    HMENU hHelpMenu = CreateMenu();
    ::AppendMenu(hHelpMenu, MF_STRING, IDM_HELP_ABOUT, L"&About ...\t F1");

    HMENU hMenuBar = CreateMenu();
    ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, L"&File");
    ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEditMenu, L"&Edit");
    ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hHelpMenu, L"&Help");

    this->SetMenu(hMenuBar);

    std::vector<ACCEL> accelerators = {
        {FVIRTKEY | FCONTROL, 'N', IDM_FILE_NEW},
        {FVIRTKEY | FCONTROL, 'O', IDM_FILE_OPEN},
        {FVIRTKEY | FCONTROL, 'S', IDM_FILE_SAVE},
        {FVIRTKEY | FALT, VK_F4, IDM_FILE_EXIT},

        {FVIRTKEY | FCONTROL, 'Z', IDM_EDIT_UNDO},
        {FVIRTKEY | FCONTROL | FSHIFT , 'Z', IDM_EDIT_REDO},
        {FVIRTKEY | FCONTROL, 'X', IDM_EDIT_CUT},
        {FVIRTKEY | FCONTROL, 'C', IDM_EDIT_COPY},
        {FVIRTKEY | FCONTROL, 'V', IDM_EDIT_PASTE},
        {FVIRTKEY | FCONTROL, 'A', IDM_EDIT_SELECTALL},
        {FVIRTKEY | FCONTROL, 'F', IDM_EDIT_FINDREPLACE},

        {FVIRTKEY, VK_F1, IDM_HELP_ABOUT},        
    };

    HACCEL hAccel = CreateAcceleratorTable(accelerators.data(), (int)accelerators.size());

    GetApp()->SetAccelerators(hAccel, *this);
}


Document* CMainWindow::getDocument() {
    return &editorView;
}
