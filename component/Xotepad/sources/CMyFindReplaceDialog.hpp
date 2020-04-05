
#pragma once 

#include <wxx_wincore.h>
#include <wxx_controls.h>

class CMyFindReplaceDialog : public CWnd {
public:
    CMyFindReplaceDialog();

    ~CMyFindReplaceDialog();

    virtual void PreCreate(CREATESTRUCT &cs) override;

    virtual int OnCreate(CREATESTRUCT& cs) override;

private:    
    CFont controlFont;

    CStatic findWhatLabel;
    CEdit findWhatEdit;

    CStatic replaceWithLabel;
    CEdit replaceWithEdit;

    CButton matchCaseCheckbox;
    CButton matchWholeWordCheckbox;
};
