
#include "CXotepadApp.hpp"
#include "CMainWindow.hpp"
#include "MainWindowPresenter.hpp"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

CAppModule _Module;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    ::CoInitialize(NULL);

    AtlInitCommonControls(ICC_COOL_CLASSES | ICC_TREEVIEW_CLASSES | ICC_BAR_CLASSES);

    _Module.Init(NULL, hInstance);

    CXotepadApp app;

    MainWindowPresenter presenter;
    CMainWindow mainWindow(&presenter);

    MSG msg;

    if (NULL == mainWindow.Create(NULL, CWindow::rcDefault, _T("Xotepad"))) {
        return 1;
    }

    mainWindow.ShowWindow(nCmdShow);
    mainWindow.UpdateWindow();

    while (::GetMessage(&msg, NULL, 0, 0) > 0) {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    mainWindow.DestroyWindow();

    _Module.Term();

    ::CoUninitialize();

    return static_cast<int>(msg.wParam);
}
