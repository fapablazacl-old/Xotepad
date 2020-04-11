
#include "CMainWindow.hpp"
#include "MainWindowPresenter.hpp"
#include "WindowsUtils.hpp"
#include "CMyFindReplaceDialog.hpp"

#include <vector>
#include <atldlgs.h>



void CMainWindow::setTitle(const std::string &title) {
    this->SetWindowTextW(widen(title).c_str());
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


class CFileFilterConverter {
public:
    CFileFilterConverter(const std::vector<FileFilter> &filters) {
        // fill the buffer!
        AppendToBuffer(filters);
        AppendToBuffer('\0');

        // construct the final string
        filterString.resize(buffer.size());

        std::memcpy(filterString.data(), buffer.data(), buffer.size());
    }

    CFileFilterConverter(const CFileFilterConverter &other) = delete;

    CFileFilterConverter& operator=(const CFileFilterConverter &other) = delete;

    ~CFileFilterConverter() {
        
    }

    std::wstring GetFileFilterString() {
        return widen(filterString);
    }


private:
    void AppendToBuffer(const std::string &text) {
        for (char ch : text) {
            buffer.push_back(ch);
        }
    }
    

    void AppendToBuffer(const char &ch) {
        buffer.push_back(ch);
    }


    void AppendToBuffer(const std::vector<std::string> &wildcards) {
        for (int i=0; i<wildcards.size(); i++) {
            this->AppendToBuffer(wildcards[i]);

            if (i < wildcards.size() - 1) {
                this->AppendToBuffer(';');
            }
        }
    }


    void AppendToBuffer(const FileFilter &filter) {
        AppendToBuffer(filter.caption);
        AppendToBuffer('\0');
        AppendToBuffer(filter.wildcards);
    }


    void AppendToBuffer(const std::vector<FileFilter> &filters) {
        for (const FileFilter &filter : filters) {
            AppendToBuffer(filter);
            AppendToBuffer('\0');
        }
    }

private:
    std::vector<char> buffer;
    std::string filterString;
};


std::optional<std::string> CMainWindow::showFilePickModal(FileDialog type, const std::string &title, const std::vector<FileFilter> &filters) {
    const std::wstring filter = CFileFilterConverter(filters).GetFileFilterString();
    const std::wstring wtitle = widen(title);

    const DWORD flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST  | OFN_HIDEREADONLY | OFN_SHOWHELP | OFN_EXPLORER | OFN_ENABLESIZING;

    CFileDialog fileDlg(type == FileDialog::Open ? TRUE : FALSE, NULL, 0, flags, filter.c_str());

    fileDlg.m_ofn.lpstrTitle = wtitle.c_str();

    if (fileDlg.DoModal(*this) == IDCANCEL) {
        return {};
    }

    return narrow(fileDlg.m_szFileName);
}


void CMainWindow::terminateApp() {
    PostQuitMessage(0);
}


CMainWindow::CMainWindow(MainWindowPresenter *presenter) : MainWindow(presenter) {
    
}


CMainWindow::~CMainWindow() {
    
}


void CMainWindow::OnClose() { 
    this->getPresenter()->handleCloseRequested();
}


int CMainWindow::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    this->SetupMenuBar();
    this->SetupDocumentEditor();

    getPresenter()->attachView(this);
    
    RECT simpleWindowRect = {200, 200, 1000, 800};
    simpleWindow.Create(*this, simpleWindowRect, L"Test", WS_OVERLAPPEDWINDOW, WS_EX_TOOLWINDOW | WS_EX_CONTROLPARENT);

    return 0;
}


int CMainWindow::OnCommand(WORD wNotifyCode, WORD wID, HWND hWndCtrl, BOOL &bHandled) {
    switch (wID) {
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


LRESULT CMainWindow::OnNotify(int idCtrl, LPNMHDR pnmh) {
    if (pnmh->hwndFrom == documentView) {
        auto notification = reinterpret_cast<SCNotification *>(pnmh);

        switch (pnmh->code) {
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


void CMainWindow::OnSize(UINT nType, CSize size) {
    if (! documentView.IsWindow()) {
        return;
    }

    RECT clientRect;
    this->GetClientRect(&clientRect);

    documentView.SetWindowPos(NULL, &clientRect, SWP_DRAWFRAME);
}


void CMainWindow::SetupMenuBar() {
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

    // GetApp()->SetAccelerators(hAccel, *this);
}


void CMainWindow::SetupDocumentEditor() {
    RECT clientRect;

    this->GetClientRect(&clientRect);

    documentView.Create(L"Scintilla", m_hWnd, clientRect, L"", WS_CHILD | WS_VISIBLE);
    documentView.SetStyle({STYLE_DEFAULT, Black, White, 10, "Consolas"});
}


Document* CMainWindow::getDocument() {
    return &documentView;
}


void CMainWindow::showFindReplace() {
    // CMyFindReplaceDialog dialog;
    // dialog.DoModal();

    simpleWindow.ShowWindow(SW_SHOW);
}
