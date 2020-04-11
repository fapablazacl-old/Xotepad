
#include "CMyFindReplaceDialog.hpp"


int CFindReplaceDialog::OnCreate(LPCREATESTRUCT lpCreateStruct) {
    this->CreateChild(findReplaceGroupBox,  10, 10, 270, 80, L"Find/Replace parameters", WS_VISIBLE | BS_GROUPBOX);
    this->CreateChild(findWhatLabel,        30, 30, 100, 20, L"Find what", WS_VISIBLE);
    this->CreateChild(findWhatEdit,         150, 30, 100, 20, L"", WS_VISIBLE | WS_TABSTOP, WS_EX_CLIENTEDGE);
    this->CreateChild(replaceWithCheckBox,  30, 55, 100, 20, L"Replace with", WS_VISIBLE | BS_AUTOCHECKBOX);
    this->CreateChild(replaceWithEdit,      150, 55, 100, 20, L"", WS_VISIBLE | WS_TABSTOP, WS_EX_CLIENTEDGE);

    this->CreateChild(matchGroupBox,        10, 100, 270, 80, L"Match options", WS_VISIBLE | BS_GROUPBOX);
    this->CreateChild(matchCaseRadio,       30, 125, 125, 20, L"Replace with", WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON | WS_GROUP);
    this->CreateChild(matchWholeWordRadio,  30, 145, 125, 20, L"Match whole word", WS_VISIBLE | WS_TABSTOP | BS_AUTORADIOBUTTON);

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
