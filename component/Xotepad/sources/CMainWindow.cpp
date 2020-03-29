
#include "CMainWindow.hpp"
#include "MainWindowPresenter.hpp"
#include "WindowsUtils.hpp"

#include <vector>
#include <wxx_taskdialog.h>


void CMainWindow::setTitle(const std::string &title) {
    SetTitle(widen(title).c_str());
}


void CMainWindow::setContent(const std::string &content) {
    editorView.SetText(content.c_str());
}


std::string CMainWindow::getContent() const {
    return editorView.GetText();
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


void CMainWindow::clearContent() {
    editorView.SetWindowText(L"");
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
    editorView.Redo();
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
    HFONT fontHandle = CreateFont(
        font.size, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH, widen(font.family).c_str()
    );

    if (fontHandle) {
        if (this->fontHandle) {
            DeleteObject(fontHandle);
        }
    }

    this->fontHandle = fontHandle;
}


Font CMainWindow::getFont() const {
    return {"", 12};
}


void CMainWindow::applyLexer(const Lexer &value) {
    static const char* cpp_keywords =
		"alignas alignof and and_eq asm atomic_cancel atomic_commit atomic_noexcept auto bitand bitor bool break case catch char "
		"char16_t char32_t class compl concept const constexpr const_cast continue decltype default delete do "
		"double dynamic_cast else enum explicit export extern false float for friend goto if inline int import long "
		"module mutable namespace new noexcept not not_eq nullptr operator or or_eq private protected public "
		"register reinterpret_cast requires return short signed sizeof static static_assert static_cast struct "
		"switch synchronized template this thread_local "
		"throw true try typedef typeid typename union unsigned "
		"using virtual void volatile wchar_t while xor xor_eq";

    static std::map<int, COLORREF> colors = {
        {SCE_C_COMMENT, RGB(0x00, 0x80, 0x00)}, 
        {SCE_C_COMMENTLINE, RGB(0x00, 0x80, 0x00)}, 
        {SCE_C_COMMENTDOC, RGB(0x00, 0x80, 0x00)}, 
        {SCE_C_NUMBER, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_WORD, RGB(0x00, 0x00, 0xFF)}, 
        {SCE_C_STRING, RGB(0x80, 0x00, 0x00)}, 
        {SCE_C_CHARACTER, RGB(0x80, 0x00, 0x00)}, 
        {SCE_C_UUID, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_PREPROCESSOR, RGB(0xA0, 0x00, 0xFF)}, 
        {SCE_C_OPERATOR, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_IDENTIFIER, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_STRINGEOL, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_VERBATIM, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_REGEX, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_COMMENTLINEDOC, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_WORD2, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_COMMENTDOCKEYWORD, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_COMMENTDOCKEYWORDERROR, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_GLOBALCLASS, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_STRINGRAW, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_TRIPLEVERBATIM, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_HASHQUOTEDSTRING, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_PREPROCESSORCOMMENT, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_PREPROCESSORCOMMENTDOC, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_USERLITERAL, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_TASKMARKER, RGB(0x00, 0x00, 0x00)}, 
        {SCE_C_ESCAPESEQUENCE, RGB(0x00, 0x00, 0x00)}
    };

    switch (value) {
    case Lexer::Clike: 
        editorView.SendCommand(SCI_STYLECLEARALL);
        editorView.SendCommand(SCI_SETLEXER, SCLEX_CPP);
        editorView.SendCommand(SCI_SETKEYWORDS, 0, (LPARAM)(cpp_keywords));
        
        for (auto styleIt=colors.begin(); styleIt!=colors.end(); styleIt++) {
            editorView.SendCommand(SCI_STYLESETFORE, styleIt->first, styleIt->second);
        }

        editorView.SendCommand(SCI_STYLESETBOLD, SCE_C_WORD, 1);
        editorView.SendCommand(SCI_STYLESETBOLD, SCE_C_WORD2, 1);
        editorView.SendCommand(SCI_SETTABWIDTH, 4);
        editorView.SendCommand(SCI_SETUSETABS, 0);

        break;

    case Lexer::CMake:
        editorView.SendCommand(SCI_SETLEXER, SCLEX_CMAKE);
        break;

    default:
        editorView.SendCommand(SCI_SETLEXER, SCLEX_NULL);
        break;
    }
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
