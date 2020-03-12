
#include <wxx_wincore.h>
#include <wxx_frame.h>
#include <wxx_menubar.h>
#include <wxx_menu.h>

#include <string>
#include <fstream>
#include <optional>

class CEditorView : public CEdit {
public:
    virtual void PreCreate(CREATESTRUCT& cs) override {
        cs.style = cs.style | WS_VSCROLL | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_WANTRETURN;
    }
};


class CMainWindow : public CFrame {
private:
    enum  {
        IDM_FILE_NEW = 1000, 
        IDM_FILE_OPEN, 
        IDM_FILE_SAVE, 
        IDM_FILE_SAVEAS, 
        IDM_FILE_EXIT, 

        IDM_EDIT_UNDO = 2000, 
        IDM_EDIT_REDO, 
        IDM_EDIT_CUT, 
        IDM_EDIT_COPY, 
        IDM_EDIT_PASTE, 
        IDM_EDIT_SELECTALL, 
        IDM_EDIT_FINDREPLACE,

        IDM_HELP_ABOUT = 3000,

        IDC_EDITOR_CONTROL = 10000
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

        documentDirty = false;

        this->updateTitle();

        return 0;
    }

    virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam) override {
        const UINT id = LOWORD(wparam);
        const UINT nc = HIWORD(wparam);

        switch (id) {
            case IDM_FILE_NEW: handleFileNew(); return FALSE;
            case IDM_FILE_OPEN: handleFileOpen(); return FALSE;
            case IDM_FILE_SAVE: handleFileSave(); return FALSE;
            case IDM_FILE_SAVEAS: handleFileSaveAs(); return FALSE;
            case IDM_FILE_EXIT: handleFileExit(); return FALSE;
            case IDM_EDIT_UNDO: handleEditUndo(); return FALSE;
            case IDM_EDIT_REDO: handleEditRedo(); return FALSE;
            case IDM_EDIT_CUT: handleEditCut(); return FALSE;
            case IDM_EDIT_COPY: handleEditCopy(); return FALSE;
            case IDM_EDIT_PASTE: handleEditPaste(); return FALSE;
            case IDM_EDIT_SELECTALL: handleEditSelectAll(); return FALSE;
            case IDM_EDIT_FINDREPLACE: handleEditFindReplace(); return FALSE;
            case IDM_HELP_ABOUT: handleHelpAbout(); return FALSE;
        }

        if (lparam == (LPARAM)editControl.GetHwnd()) {
            documentDirty = true;
            updateTitle();
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
        ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_NEW, "New");
        ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_OPEN, "Open");
        ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVE, "Save");
        ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_SAVEAS, "Save As");
        ::AppendMenu(hFileMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hFileMenu, MF_STRING, IDM_FILE_EXIT, "Exit");

        HMENU hEditMenu = CreateMenu();
        ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_UNDO, "Undo");
        ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_REDO, "Redo");
        ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_CUT, "Cut");
        ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_COPY, "Copy");
        ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_PASTE, "Paste");
        ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_SELECTALL, "Select All");
        ::AppendMenu(hEditMenu, MF_SEPARATOR, 0, "");
        ::AppendMenu(hEditMenu, MF_STRING, IDM_EDIT_FINDREPLACE, "Find/Replace ...");

        HMENU hHelpMenu = CreateMenu();
        ::AppendMenu(hHelpMenu, MF_STRING, 0, "About ...");

        HMENU hMenuBar = CreateMenu();
        ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hFileMenu, "File");
        ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hEditMenu, "Edit");
        ::AppendMenu(hMenuBar, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");

        this->SetMenu(hMenuBar);
    }


    std::string getDocumentName() const {
        std::string documentName;

        if (documentFileName) {
            documentName = *documentFileName;
        } else {
            documentName = "Untitled " + std::to_string(documentCount);
        }

        return documentName + (documentDirty ? "*" : "");
    }


    std::string computeTitle(const std::string &documentName) const {
        return "Xotacode - " + getDocumentName();
    }


    void updateTitle() {
        SetTitle(computeTitle(getDocumentName()).c_str());
    }

private:
    CEditorView editControl;
    std::optional<std::string> documentFileName;
    bool documentDirty = false;
    int documentCount = 1;
};


int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    CWinApp myApp;
	
    CMainWindow mainWindow;
    mainWindow.Create();

    return myApp.Run();
}
