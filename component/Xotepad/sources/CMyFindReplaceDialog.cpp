
#if 0

#include "CMyFindReplaceDialog.hpp"
#include "resource.h"


CMyFindReplaceDialog::CMyFindReplaceDialog() : CDialog(IDD_FORMVIEW) {

}


CMyFindReplaceDialog::~CMyFindReplaceDialog() {
}


void CMyFindReplaceDialog::OnDestroy() {

}


BOOL CMyFindReplaceDialog::OnInitDialog() {
    return TRUE;
}


INT_PTR CMyFindReplaceDialog::DialogProc(UINT msg, WPARAM wparam, LPARAM lparam) {
    
    return DialogProcDefault(msg, wparam, lparam);
}


BOOL CMyFindReplaceDialog::OnCommand(WPARAM wparam, LPARAM lparam) {
    return TRUE;
}


void CMyFindReplaceDialog::OnOK() {

}


/*
#include "CMyFindReplaceDialog.hpp"

CMyFindReplaceDialog::CMyFindReplaceDialog() {
    // controlFont.CreatePointFont(32, L"MS Shell Dlg");
    controlFont.CreateFont(13,0,0,0,400,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,CLEARTYPE_NATURAL_QUALITY, VARIABLE_PITCH,TEXT("MS Shell Dlg"));
}


CMyFindReplaceDialog::~CMyFindReplaceDialog() {}


void CMyFindReplaceDialog::PreCreate(CREATESTRUCT &cs) {
    cs.cx = 400;
    cs.cy = 400;
    cs.style = WS_OVERLAPPEDWINDOW;
}


int CMyFindReplaceDialog::OnCreate(CREATESTRUCT& cs) {
    findWhatLabel.CreateEx(
        NULL, 
        L"Static", 
        L"Find what", 
        WS_CHILD, 
        26, 30 ,64 ,16 , 
        this->GetHwnd(), 
        0,
        nullptr
    );

    findWhatLabel.SetFont(controlFont, TRUE);
    findWhatLabel.ShowWindow();
    findWhatLabel.UpdateWindow();

    // findWhatEdit
    // replaceWithLabel
    // replaceWithEdit
    // matchCaseCheckbox
    // matchWholeWordCheckbox

    return CWnd::OnCreate(cs);
}
*/

#endif
