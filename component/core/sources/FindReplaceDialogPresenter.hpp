
#pragma once 

#include <string>

class FindReplaceDialog;
class FindReplaceDialogPresenter {
public:
    void attachView(FindReplaceDialog *view);

    void handleFindWhatTextBox_Change(const std::string &value);

    void handleReplaceWithCheckBox_Click(const bool checked);

    void handleReplaceWithTextBox_Change(const std::string &value);

    void handleMatchCaseCheckBox_Click(const bool checked);

    void handleMatchWholeWordCheckBox_Click(const bool checked);

    void handleSelectionScopeOptionBox_Click();

    void handleCurrentDocumentScopeOptionBox_Click();

    void handleFindNextButton_Click();

    void handleReplaceNextButton_Click();

    void handleReplaceAllButton_Click();

    void handleCloseButton_Click();

private:
    FindReplaceDialog *view = nullptr;
    std::string findWhat;
    std::string replaceWith;
    bool replaceInsteadOfFind = false;
    bool matchCase = false;
    bool matchWholeWord = false;

    enum Scope {
        Selection, CurrentDocument
    } scope = CurrentDocument;
};
