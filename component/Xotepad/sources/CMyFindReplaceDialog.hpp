
#pragma once 

#include <wxx_dialog.h>

class CMyFindReplaceDialog : public CDialog {
public:
    CMyFindReplaceDialog();

    virtual ~CMyFindReplaceDialog();

protected:
    virtual void OnDestroy() override;
    virtual BOOL OnInitDialog() override;
    virtual INT_PTR DialogProc(UINT msg, WPARAM wparam, LPARAM lparam) override;
    virtual BOOL OnCommand(WPARAM wparam, LPARAM lparam) override;
    virtual void OnOK() override;
};


/*
#pragma once 

#include <wxx_wincore.h>
#include <wxx_controls.h>

class CMyFindReplaceDialog : public CDialog {
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
*/
