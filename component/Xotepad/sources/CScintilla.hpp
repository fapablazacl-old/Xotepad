
#pragma once

#include <wxx_wincore.h>
#include <wxx_controls.h>
#include <Scintilla.h>
#include <SciLexer.h>


enum ScintillaColors {
    Black = RGB(0x00, 0x00, 0x00),
    White = RGB(0xFF, 0xFF, 0xFF),
    Red = RGB(0xFF, 0x00, 0x00),
    Green = RGB(0x00, 0xFF, 0x00),
    Blue = RGB(0x00, 0x00, 0xFF)
};


struct ScintillaStyle {
    int style = 0;
    COLORREF fore;
    COLORREF back = White;
    int size = 0;
    std::string face = "";

    ScintillaStyle(int style_, COLORREF fore_) : style(style_), fore(fore_) {}
    ScintillaStyle(int style_, COLORREF fore_, COLORREF back_) : style(style_), fore(fore_), back(back_) {}
    ScintillaStyle(int style_, COLORREF fore_, COLORREF back_, int size_) : style(style_), fore(fore_), back(back_), size(size_) {}
    ScintillaStyle(int style_, COLORREF fore_, COLORREF back_, int size_, const std::string &face_) : style(style_), fore(fore_), back(back_), size(size_), face(face_) {}
};


struct ScintillaConfig {
    int lexer = 0;
    std::string keywords;
    std::map<int, COLORREF> colors;
    std::vector<ScintillaStyle> styles;
    int styleBits = 7;
    bool useTabs = false;
    int tabWidth = 4;
};


class CScintilla : public CWnd {
public:
    CScintilla() {}
    virtual ~CScintilla() {}

    CScintilla(const CScintilla&) = delete;

    CScintilla& operator= (const CScintilla&) = delete;

    virtual void PreCreate(CREATESTRUCT& cs) override;

    virtual HWND Create(HWND parent) override;

    LRESULT SendCommand(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0);

    LRESULT SendCommand(UINT Msg, WPARAM wParam = 0, LPARAM lParam = 0) const;

    void SetStyle(int style, COLORREF fore, COLORREF back=White, int size=0, const char *face=nullptr);
    
    void SetStyle(const ScintillaStyle &style);

    void SetSavePoint();
    void EmptyUndoBuffer();
    void ClearAll();
        
    void SetFont(const std::string &name, const int size);
    void SetTabWidth(const int spaces);
        
    void Undo();
    void Redo();

    void Cut();
    void Copy();
    void Paste();

    void SetText(const std::string &text);
    std::string GetText() const;

    void SetMarginType(const int margin, const int type);
    void SetMarginWidth(const int margin, const int pixelWidth);
        
    int TextWidth(const int style, const std::string &text);

    void ApplyConfig(const ScintillaConfig &config);

    void SetSel(int start, int end, BOOL _);
    void GetSel(int &start, int &end) const;
};
