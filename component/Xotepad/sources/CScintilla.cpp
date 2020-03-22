
#include "CScintilla.hpp"


void CScintilla::PreCreate(CREATESTRUCT& cs) {    
    cs.style = WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPCHILDREN;
}


HWND CScintilla::Create(HWND parent) {
    CREATESTRUCT cs;
    ZeroMemory(&cs, sizeof(cs));

    // Set the WNDCLASS parameters
    cs.lpszClass = _T("Scintilla");

    // Set a reasonable default window style
    DWORD dwOverlappedStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    cs.style = WS_VISIBLE | ((parent)? WS_CHILD : dwOverlappedStyle );

    // Set a reasonable default window position
    if (NULL == parent)
    {
        cs.x  = CW_USEDEFAULT;
        cs.cx = CW_USEDEFAULT;
        cs.y  = CW_USEDEFAULT;
        cs.cy = CW_USEDEFAULT;
    }

    // Allow the CREATESTRUCT parameters to be modified
    PreCreate(cs);

    DWORD style = cs.style & ~WS_VISIBLE;
    HWND wnd;

    // Create the window
#ifndef _WIN32_WCE
    wnd = CreateEx(cs.dwExStyle, cs.lpszClass, cs.lpszName, style,
            cs.x, cs.y, cs.cx, cs.cy, parent,
            cs.hMenu, cs.lpCreateParams);

    if (cs.style & WS_VISIBLE)
    {
        if      (cs.style & WS_MAXIMIZE) ShowWindow(SW_MAXIMIZE);
        else if (cs.style & WS_MINIMIZE) ShowWindow(SW_MINIMIZE);
        else    ShowWindow();
    }

#else
    wnd = CreateEx(cs.dwExStyle, cs.lpszClass, cs.lpszName, cs.style,
            cs.x, cs.y, cs.cx, cs.cy, parent,
            0, cs.lpCreateParams);
#endif

    return wnd;
}


void CScintilla::SetStyle(int style, COLORREF fore, COLORREF back, int size, const char *face) {
    this->SendMessage(SCI_STYLESETFORE, style, fore);
    this->SendMessage(SCI_STYLESETBACK, style, back);

    if (size >= 1) {
        this->SendMessage(SCI_STYLESETSIZE, style, size);
    }
        
    if (face) {
        this->SendMessage(SCI_STYLESETFONT, style, (LPARAM)face);
    }
}

    
void CScintilla::SetStyle(const ScintillaStyle &style) {
    const char *face = nullptr;

    if (style.face != "") {
        face = style.face.c_str();
    }

    this->SetStyle(style.style, style.fore, style.back, style.size, face);
}


/*
void CScintilla::OnInitialUpdate() {
    this->SetAStyle(STYLE_DEFAULT, black, white, 10, "Courier New");
    this->SendEditor(SCI_STYLECLEARALL);

    this->SendEditor(SCI_SETLEXER, SCLEX_CPP);
    this->SendEditor(SCI_SETSTYLEBITS, 7);
    this->SendEditor(SCI_SETKEYWORDS, 0, (LPARAM)(cpp_keywords));
        
    this->SetAStyle(SCE_C_DEFAULT, black, white, 10, "Courier New");

    std::map<int, COLORREF> colors = {
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

    for (auto styleIt=colors.begin(); styleIt!=colors.end(); styleIt++) {
        this->SetAStyle(styleIt->first, styleIt->second);
    }

    this->SendEditor(SCI_STYLESETBOLD, SCE_C_WORD, 1);
    this->SendEditor(SCI_STYLESETBOLD, SCE_C_WORD2, 1);
}
*/

void CScintilla::SetText(const std::string &text) {
    this->SendMessage(SCI_SETTEXT, 0, (LPARAM)text.c_str());
}


std::string CScintilla::GetText() const {
    std::string content;
    const int length = (int)this->SendMessage(SCI_GETTEXTLENGTH) + 1;
    content.resize(length);
    this->SendMessage(SCI_GETTEXT, length, (LPARAM)content.c_str());

    return content;
}
    

void CScintilla::SetSavePoint() {
    this->SendMessage(SCI_SETSAVEPOINT);
}


void CScintilla::EmptyUndoBuffer() {
    this->SendMessage(SCI_EMPTYUNDOBUFFER);
}


void CScintilla::ClearAll() { 
    this->SendMessage(SCI_CLEARALL);
}


void CScintilla::SetFont(const std::string &name, const int size) {

}


void CScintilla::SetTabWidth(const int spaces) {
    this->SendMessage(SCI_SETUSETABS, 0);
    this->SendMessage(SCI_SETTABWIDTH, spaces);
}


void CScintilla::Undo() {
}
    

void CScintilla::Redo() {

}


void CScintilla::Cut() {

}

    
void CScintilla::Copy() {
}


void CScintilla::Paste() {

}


void CScintilla::SetMarginType(const int margin, const int type) {
    this->SendMessage(SCI_SETMARGINTYPEN, margin, type);
}

    
void CScintilla::SetMarginWidth(const int margin, const int pixelWidth) {
    this->SendMessage(SCI_SETMARGINWIDTHN, margin, pixelWidth);
}


int CScintilla::TextWidth(const int style, const std::string &text) {
    return (int) this->SendMessage(SCI_TEXTWIDTH, style, (LPARAM)text.c_str());
}


void CScintilla::ApplyConfig(const ScintillaConfig &config) {
    this->SendMessage(SCI_SETLEXER, config.lexer);
    this->SendMessage(SCI_SETKEYWORDS, 0, (LPARAM)(config.keywords.c_str()));
    this->SendMessage(SCI_SETUSETABS, config.useTabs?1:0);
    this->SendMessage(SCI_SETTABWIDTH, config.tabWidth);

    for (const auto &style : config.styles) {
        this->SetStyle(style);
    }

    for (const auto &pair : config.colors) {
        this->SetStyle(pair.first, pair.second);
    }
}
