
#include "CXotepadApp.hpp"

CXotepadApp::CXotepadApp() {
    hScintilla = ::LoadLibrary(L"SciLexer.DLL");

    if (!hScintilla) {
        MessageBox(NULL, L"Couldn't load the Scintilla DLL Component", L"Xotepad", MB_OK | MB_ICONERROR);
    }
}


CXotepadApp::~CXotepadApp() {
    if (hScintilla) {
        ::FreeLibrary(hScintilla);
        hScintilla = NULL;
    }
}
