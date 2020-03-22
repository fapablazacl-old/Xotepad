
#include "CXotepadApp.hpp"

CXotepadApp::CXotepadApp() {
    hScintilla = ::LoadLibrary("SciLexer.DLL");

    if (!hScintilla) {
        MessageBox(NULL, "Couldn't load the Scintilla DLL Component", "Xotepad", MB_OK | MB_ICONERROR);
    }
}


CXotepadApp::~CXotepadApp() {
    if (hScintilla) {
        ::FreeLibrary(hScintilla);
        hScintilla = NULL;
    }
}
