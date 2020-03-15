
#include "CMainWindow.hpp"
#include "MainWindowPresenter.hpp"

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    CWinApp myApp;
	
    MainWindowPresenter presenter;
    CMainWindow mainWindow(&presenter);
    mainWindow.Create();

    return myApp.Run();
}
