
#include "CFindReplaceDialog.hpp"

#include "CDocument.hpp"
#include "WindowsUtils.hpp"
#include <cassert>

#include "FormDSL.h"


CFindReplaceDialog::CFindReplaceDialog() { }


int CFindReplaceDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    /*
    auto builder = dsl::WindowBuilder{"CFindReplaceDialog"};

    builder
        .child(dsl::WindowBuilder::groupBox()
            .caption("Find/Replace parameters")
            .position(10, 10)
            .size(270, 80)
        )
        .child(dsl::WindowBuilder::label()
            .caption("Find what")
            .position(30, 30)
        )
        .build();

    */
    // auto findReplaceUI = Window{};

    /*
    findReplaceUI
        .groupBox()
            .caption("Find/Replace parameters")
            .left(10).width(10)
            .top(10).height(270);
    */
    UINT dpi = GetDpiForWindow(this->m_hWnd);
    this->uiScale = (static_cast<float>(dpi) / 96.0f) * 0.9f;

    this->CreateChild(findReplaceGroupBox,  10, 10, 270, 80, L"Find/Replace parameters", WS_VISIBLE | BS_GROUPBOX);
    this->CreateChild(findWhatLabel,        30, 30, 100, 20, L"Find what", WS_VISIBLE);
    this->CreateChild(findWhatEdit,         150, 30, 100, 20, L"", WS_VISIBLE | WS_TABSTOP, WS_EX_CLIENTEDGE);
    this->CreateChild(replaceWithCheckBox,  30, 55, 100, 20, L"Replace with", WS_VISIBLE | BS_AUTOCHECKBOX);
    this->CreateChild(replaceWithEdit,      150, 55, 100, 20, L"", WS_VISIBLE | WS_TABSTOP, WS_EX_CLIENTEDGE);

    this->CreateChild(matchGroupBox,        10, 100, 270, 80, L"Match options", WS_VISIBLE | BS_GROUPBOX);
    this->CreateChild(matchCaseCheckBox,       30, 125, 125, 20, L"Match case", WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX);
    this->CreateChild(matchWholeWordCheckBox,  30, 145, 125, 20, L"Match whole word", WS_VISIBLE | WS_TABSTOP | BS_AUTOCHECKBOX);

    this->CreateChild(scopeGroupBox,                10, 190, 270, 80, L"Scope", WS_VISIBLE | BS_GROUPBOX);
    this->CreateChild(scopeSelectionRadio,          30, 210, 125, 20, L"Selection", WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON | WS_GROUP);
    this->CreateChild(scopeCurrentDocumentRadio,    30, 230, 125, 20, L"Current Document", WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON);

    this->CreateChild(findNextButton,       10, 280, 120, 30, L"Find Next", WS_VISIBLE);
    this->CreateChild(closeButton,          140, 280, 120, 30, L"Close", WS_VISIBLE);
    this->CreateChild(replaceNextButton,    10, 320, 120, 30, L"Replace Next", WS_VISIBLE);
    this->CreateChild(replaceAllButton,     140, 320, 120, 30, L"Replace All", WS_VISIBLE);
    
    return 0;
}


BOOL CFindReplaceDialog::OnEraseBkgnd(CDCHandle hdc) {
    RECT rect;

    this->GetClientRect(&rect);
    ::FillRect(hdc, &rect, (HBRUSH)COLOR_3DSHADOW);

    return TRUE;
}


void CFindReplaceDialog::AttachDocument(CDocument* document) {
    assert(presenter);

    presenter->attachView(this, document);
}


void CFindReplaceDialog::OnCommand(UINT uNotifyCode, int nID, CWindow wndCtl) {
    assert(presenter);

    if (wndCtl == findNextButton) {
        presenter->handleFindNextButton_Click();
    }

    if (wndCtl == replaceNextButton) {
        presenter->handleReplaceNextButton_Click();
    }

    if (wndCtl == replaceAllButton) {
        presenter->handleReplaceAllButton_Click();
    }

    if (wndCtl == closeButton) {
        presenter->handleCloseButton_Click();
    }

    if (wndCtl == replaceWithCheckBox) {
        LRESULT state = replaceWithCheckBox.SendMessageW(BM_GETCHECK);

        if (state == BST_CHECKED) {
            presenter->handleReplaceWithCheckBox_Click(true);
        } else if (state == BST_UNCHECKED) {
            presenter->handleReplaceWithCheckBox_Click(false);
        }
    }

    if (wndCtl == matchCaseCheckBox) {
        LRESULT state = matchCaseCheckBox.SendMessageW(BM_GETCHECK);

        if (state == BST_CHECKED) {
            presenter->handleMatchCaseCheckBox_Click(true);
        } else if (state == BST_UNCHECKED) {
            presenter->handleMatchCaseCheckBox_Click(false);
        }
    }

    if (wndCtl == matchWholeWordCheckBox) {
        LRESULT state = matchWholeWordCheckBox.SendMessageW(BM_GETCHECK);

        if (state == BST_CHECKED) {
            presenter->handleMatchWholeWordCheckBox_Click(true);
        } else if (state == BST_UNCHECKED) {
            presenter->handleMatchWholeWordCheckBox_Click(false);
        }
    }

    if (wndCtl == scopeSelectionRadio) {
        presenter->handleSelectionScopeOptionBox_Click();
    }
    
    if (wndCtl == scopeCurrentDocumentRadio) {
        presenter->handleCurrentDocumentScopeOptionBox_Click();
    }

    if (wndCtl == findWhatEdit) {
        switch (uNotifyCode) {
            case EN_CHANGE: {
                CString str;
                findWhatEdit.GetWindowTextW(str);
                presenter->handleFindWhatTextBox_Change(narrow(str));
            }
        }
    }

    if (wndCtl == replaceWithEdit) {
        switch (uNotifyCode) {
            case EN_CHANGE: {
                CString str;
                replaceWithEdit.GetWindowTextW(str);
                presenter->handleReplaceWithTextBox_Change(narrow(str));
            }
        }
    }
}


void CFindReplaceDialog::show(const ViewData &viewData) {
    this->SetWindowTextW(widen(viewData.title).c_str());

    matchCaseCheckBox.SetCheck(viewData.matchCase ? BST_CHECKED : BST_UNCHECKED);
    matchWholeWordCheckBox.SetCheck(viewData.matchWholeWorld ? BST_CHECKED : BST_UNCHECKED);

    switch (viewData.scope) {
    case FindReplaceDialog::SearchScope::Selection: 
        scopeSelectionRadio.SetCheck(BST_CHECKED);
        break;

    case FindReplaceDialog::SearchScope::CurrentDocument:
        scopeCurrentDocumentRadio.SetCheck(BST_CHECKED);
        break;
    }

    if (viewData.replaceWith) {
        replaceWithEdit.SetWindowTextW(widen(*viewData.replaceWith).c_str());
    } else {
        replaceWithEdit.SetWindowTextW(L"");
    }

    this->ShowWindow(SW_SHOW);
}


void CFindReplaceDialog::hide() {
    this->ShowWindow(SW_HIDE);
}


void CFindReplaceDialog::toggleReplaceControls(const bool status) {
    replaceAllButton.EnableWindow(status ? TRUE : FALSE);
    replaceWithEdit.EnableWindow(status ? TRUE : FALSE);
    replaceNextButton.EnableWindow(status ? TRUE : FALSE);
}


void CFindReplaceDialog::attachPresenter(FindReplaceDialogPresenter *presenter) {
    this->presenter = presenter;
}
