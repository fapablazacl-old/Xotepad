
#pragma once

#include <wxx_wincore.h>

class CXotepadApp : public CWinApp {
public:
    CXotepadApp();

    virtual ~CXotepadApp();

private:
    HINSTANCE hScintilla = NULL;
};
