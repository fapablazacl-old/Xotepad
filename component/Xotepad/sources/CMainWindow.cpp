
#include "CMainWindow.hpp"
#include "MainWindowPresenter.hpp"
#include <vector>


void CMainWindow::setTitle(const std::string &title) {
    SetTitle(title.c_str());
}


void CMainWindow::setContent(const std::string &content) {
    editorView.SetText(content.c_str());
}


std::string CMainWindow::getContent() const {
    return editorView.GetText();
}


DialogResult CMainWindow::showMessageBoxModal(const std::string &title, const std::string &message, const DialogButtons buttons, const DialogIcon icon) {
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


std::optional<std::string> CMainWindow::showFilePickModal(FileDialog type, const std::string &title) {
    const CString filter = _T("All Files (*.*)|*.*||");
    const DWORD flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST  | OFN_HIDEREADONLY | OFN_SHOWHELP | OFN_EXPLORER | OFN_ENABLESIZING;
        
    CFileDialog fileDlg(type == FileDialog::Open ? TRUE : FALSE, NULL, 0, flags, filter);

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


void CMainWindow::terminateApp() {
    PostQuitMessage(0);
}


void CMainWindow::setSelection(const TextSelection &selection) {
    editorView.SetSel(selection.start, selection.end, FALSE);
}


void CMainWindow::selectAll() {
    editorView.SetSel(0, -1, FALSE);
}


void CMainWindow::clearSelection() {
    editorView.SetSel(-1, -1, FALSE);
}


TextSelection CMainWindow::getSelection() const {
    TextSelection selection = {0, 0};

    editorView.GetSel(selection.start, selection.end);
    
    return selection;
}


void CMainWindow::undo() {
    editorView.Undo();
}


void CMainWindow::redo() {
    
}


void CMainWindow::cut() {
    editorView.Cut();
}


void CMainWindow::copy() {
    editorView.Copy();
}


void CMainWindow::paste() {
    editorView.Paste();
}


void CMainWindow::setFont(const Font &font) {
    HFONT fontHandle = CreateFont(font.size,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT(font.family.c_str()));

    if (fontHandle) {
        if (this->fontHandle) {
            DeleteObject(fontHandle);
        }
    }

    this->fontHandle = fontHandle;

    // editorView.SetFont(this->fontHandle);
}


Font CMainWindow::getFont() const {
    return {"", 12};
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
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_NEW, "&New\t Ctrl+N");
    ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_OPEN, "&Open\t Ctrl+O");
    ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVE, "&Save\t Ctrl+S");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVEAS, "Save &As");
    ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_EXIT, "&Exit\t Alt+F4");

    HMENU hEditMenu = CreateMenu();
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_UNDO, "&Undo\t Ctrl+Z");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_REDO, "&Redo\t Ctrl+Shift+Z");
    ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_CUT, "Cu&t\t Ctrl+X");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_COPY, "&Copy\t Ctrl+C");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_PASTE, "&Paste\t Ctrl+V");
    ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_SELECTALL, "&Select All\t Ctrl+A");
    ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
    ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_FINDREPLACE, "&Find & Replace ...\t Ctrl+F");

    HMENU hHelpMenu = CreateMenu();
    ::AppendMenu(hHelpMenu, MF_STRING, IDM_HELP_ABOUT, "&About ...\t F1");

    HMENU hMenuBar = CreateMenu();
    ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, "&File");
    ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEditMenu, "&Edit");
    ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hHelpMenu, "&Help");

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
