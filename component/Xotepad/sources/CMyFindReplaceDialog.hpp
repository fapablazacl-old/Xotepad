
#pragma once 

#include <atlbase.h>
#include <atlapp.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atluser.h>
#include <atlcrack.h>
#include <atlsplit.h>
#include <atlmisc.h>

#include "FindReplaceDialog.hpp"
#include "FindReplaceDialogPresenter.hpp"

class CFindReplaceDialog: public CWindowImpl<CFindReplaceDialog>, public FindReplaceDialog {
public:
    DECLARE_WND_CLASS(L"CFindReplaceDialog")

    BEGIN_MSG_MAP(CMainWindow)
        MSG_WM_CREATE(OnCreate)
        MSG_WM_ERASEBKGND(OnEraseBkgnd)
        MSG_WM_COMMAND(OnCommand)
    END_MSG_MAP()

public:
    template<typename T>
    HWND CreateChild(T &child, int left, int top, int w, int h, wchar_t *windowName, const DWORD style, const DWORD exStyle = 0) {
        RECT rect = {
            left, top,
            left + w, top + h
        };

        HWND hWnd = child.Create(*this, rect, windowName, style | WS_CHILD, exStyle);

        child.SetFont((HFONT)GetStockObject(DEFAULT_GUI_FONT));

        return hWnd;
    }

    int OnCreate(LPCREATESTRUCT lpCreateStruct);
    
    void OnCommand(UINT uNotifyCode, int nID, CWindow wndCtl);
    
    virtual BOOL OnEraseBkgnd(CDCHandle hdc);

private:
    CButton findReplaceGroupBox;
    CStatic findWhatLabel;
    CEdit findWhatEdit;
    CButton replaceWithCheckBox;
    CEdit replaceWithEdit;

    CButton matchGroupBox;
    CButton matchCaseCheckBox;
    CButton matchWholeWordCheckBox;

    CButton scopeGroupBox;
    CButton scopeSelectionRadio;
    CButton scopeCurrentDocumentRadio;

    CButton findNextButton;
    CButton replaceNextButton;
    CButton replaceAllButton;
    CButton closeButton;

    FindReplaceDialogPresenter presenter;

public:
    virtual void show(const ViewData &viewData) override;

    virtual void hide() override;

    virtual void toggleReplaceControls(const bool status) override;
};
