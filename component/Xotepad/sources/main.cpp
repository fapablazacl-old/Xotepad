
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
private:
    enum  {
        ID_FILE_NEW = 1000, 
        ID_FILE_OPEN, 
        ID_FILE_SAVE, 
        ID_FILE_SAVEAS, 
        ID_FILE_EXIT, 

        ID_EDIT_UNDO = 2000, 
        ID_EDIT_REDO, 
        ID_EDIT_CUT, 
        ID_EDIT_COPY, 
        ID_EDIT_PASTE, 
        ID_EDIT_SELECTALL, 
        ID_EDIT_FINDREPLACE,

        ID_HELP_ABOUT 
    };

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

    virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam) override {
        const UINT id = LOWORD(wparam);

        switch (id) {
            case ID_FILE_NEW: handleFileNew(); return FALSE;
            case ID_FILE_OPEN: handleFileOpen(); return FALSE;
            case ID_FILE_SAVE: handleFileSave(); return FALSE;
            case ID_FILE_SAVEAS: handleFileSaveAs(); return FALSE;
            case ID_FILE_EXIT: handleFileExit(); return FALSE;
            case ID_EDIT_UNDO: handleEditUndo(); return FALSE;
            case ID_EDIT_REDO: handleEditRedo(); return FALSE;
            case ID_EDIT_CUT: handleEditCut(); return FALSE;
            case ID_EDIT_COPY: handleEditCopy(); return FALSE;
            case ID_EDIT_PASTE: handleEditPaste(); return FALSE;
            case ID_EDIT_SELECTALL: handleEditSelectAll(); return FALSE;
            case ID_EDIT_FINDREPLACE: handleEditFindReplace(); return FALSE;
            case ID_HELP_ABOUT: handleHelpAbout(); return FALSE;
        }

        return FALSE;
    }

private:
    void handleFileNew() {
    }

    void handleFileOpen() {
    }

    void handleFileSave() {
    }

    void handleFileSaveAs() {
    }

    void handleFileExit() {
    }

    void handleEditUndo() {
    }

    void handleEditRedo() {
    }

    void handleEditCut() {
    }

    void handleEditCopy() {
    }

    void handleEditPaste() {
    }

    void handleEditSelectAll() {
    }

    void handleEditFindReplace() {
    }

    void handleHelpAbout() {
    }


    void setupMenuBar() {
        HMENU hFileMenu = CreateMenu();
        ::AppendMenu(hFileMenu, MF_STRING, ID_FILE_NEW, "New");
        ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hFileMenu, MF_STRING, ID_FILE_OPEN, "Open");
        ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVE, "Save");
        ::AppendMenu(hFileMenu, MF_STRING, ID_FILE_SAVEAS, "Save As");
        ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hFileMenu, MF_STRING, ID_FILE_EXIT, "Exit");

        HMENU hEditMenu = CreateMenu();
        ::AppendMenu(hEditMenu, MF_STRING, ID_EDIT_UNDO, "Undo");
        ::AppendMenu(hEditMenu, MF_STRING, ID_EDIT_REDO, "Redo");
        ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hEditMenu, MF_STRING, ID_EDIT_CUT, "Cut");
        ::AppendMenu(hEditMenu, MF_STRING, ID_EDIT_COPY, "Copy");
        ::AppendMenu(hEditMenu, MF_STRING, ID_EDIT_PASTE, "Paste");
        ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hEditMenu, MF_STRING, ID_EDIT_SELECTALL, "Select All");
        ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hEditMenu, MF_STRING, ID_EDIT_FINDREPLACE, "Find/Replace ...");

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
