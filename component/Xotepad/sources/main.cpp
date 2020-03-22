
#include "CMainWindow.hpp"
#include "MainWindowPresenter.hpp"
#include "CXotepadApp.hpp"

#include <Scintilla.h>

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    CXotepadApp myApp;
	
    MainWindowPresenter presenter;
    CMainWindow mainWindow(&presenter);
    mainWindow.Create();

    return myApp.Run();
}
