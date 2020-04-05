
#pragma once

#include <Windows.h>

class CXotepadApp {
public:
    CXotepadApp();

    virtual ~CXotepadApp();

private:
    HINSTANCE hScintilla = NULL;
};
