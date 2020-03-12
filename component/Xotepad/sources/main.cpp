
#include <wxx_wincore.h>
#include <wxx_frame.h>
#include <wxx_menubar.h>
#include <wxx_menu.h>

class CEditorView : public CEdit {
public:
    virtual void PreCreate(CREATESTRUCT& cs) override {
        cs.style = cs.style | WS_VSCROLL | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN;
    }
};

class CMainWindow : public CFrame {
public:
    CMainWindow() {
        this->SetView(editControl);
    }


    virtual ~CMainWindow() {}


    virtual void OnDestroy() { 
        PostQuitMessage(0); 
    }


    virtual int OnCreate(CREATESTRUCT& cs) override {
        UseIndicatorStatus(FALSE);   // Don't show keyboard indicators in the StatusBar
        UseMenuStatus(FALSE);        // Don't show menu descriptions in the StatusBar
        UseReBar(FALSE);             // Don't use a ReBar
        UseStatusBar(FALSE);         // Don't use a StatusBar
        UseThemes(FALSE);            // Don't use themes
        UseToolBar(FALSE);           // Don't use a ToolBar

        CFrame::OnCreate(cs);

        this->setupMenuBar();

        return 0;
    }

private:
    void setupEditor() {
        // editControl.Create(this->GetHwnd());

        // editControl.SetStyle(editControl.GetStyle() | WS_VSCROLL | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN);
        editControl.SetStyle(editControl.GetStyle() | ES_MULTILINE | ES_WANTRETURN);
        // editControl.SetWindowPos(NULL, 0, 0, 100, 100, 0);
    }


    void setupMenuBar() {
        HMENU hFileMenu = CreateMenu();
        ::AppendMenu(hFileMenu, MF_STRING, 0, "New");
        ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hFileMenu, MF_STRING, 0, "Open");
        ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hFileMenu, MF_STRING, 0, "Save");
        ::AppendMenu(hFileMenu, MF_STRING, 0, "Save As");
        ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hFileMenu, MF_STRING, 0, "Exit");

        HMENU hEditMenu = CreateMenu();
        ::AppendMenu(hEditMenu, MF_STRING, 0, "Undo");
        ::AppendMenu(hEditMenu, MF_STRING, 0, "Redo");
        ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hEditMenu, MF_STRING, 0, "Cut");
        ::AppendMenu(hEditMenu, MF_STRING, 0, "Copy");
        ::AppendMenu(hEditMenu, MF_STRING, 0, "Paste");
        ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hEditMenu, MF_STRING, 0, "Select All");
        ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hEditMenu, MF_STRING, 0, "Find/Replace ...");

        HMENU hHelpMenu = CreateMenu();
        ::AppendMenu(hHelpMenu, MF_STRING, 0, "About ...");

        HMENU hMenuBar = CreateMenu();
        ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, "File");
        ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEditMenu, "Edit");
        ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");

        this->SetMenu(hMenuBar);
    }

private:
    CEditorView editControl;
};


int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    CWinApp myApp;
	
    CMainWindow mainWindow;
    mainWindow.Create();

    return myApp.Run();
}
