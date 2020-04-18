
#include "FindReplaceDialogPresenter.hpp"
#include "Document.hpp"
#include "WindowsUtils.hpp"

#include <iostream>


void FindReplaceDialogPresenter::attachView(FindReplaceDialog *view, Document *documentView) {
    this->view = view;
    this->documentView = documentView;
}


void FindReplaceDialogPresenter::handleFindWhatTextBox_Change(const std::string &value) {
    findWhat = value;
}


void FindReplaceDialogPresenter::handleReplaceWithCheckBox_Click(const bool checked) {
    replaceInsteadOfFind = checked;
}


void FindReplaceDialogPresenter::handleReplaceWithTextBox_Change(const std::string &value) {
    replaceWith = value;
}


void FindReplaceDialogPresenter::handleMatchCaseCheckBox_Click(const bool checked) {
    matchCase = checked;
}


void FindReplaceDialogPresenter::handleMatchWholeWordCheckBox_Click(const bool checked) {
    matchWholeWord = checked;
}


void FindReplaceDialogPresenter::handleSelectionScopeOptionBox_Click() {
    scope = Selection;
}


void FindReplaceDialogPresenter::handleCurrentDocumentScopeOptionBox_Click() {
    scope = CurrentDocument;
}


void FindReplaceDialogPresenter::handleFindNextButton_Click() {
    const std::string content = this->documentView->getModel()->getContent();
    const auto flags = FIND_FLAGS((matchCase ? FF_MATCH_CASE : FF_DEFAULT) | (matchWholeWord ? FF_MATCH_WHOLE_WORD : FF_DEFAULT));

    const std::size_t offset = find(content.c_str(), currentOffset, findWhat.c_str(), flags);

    if (offset == std::string::npos) {
        currentOffset = 0;
    }

    const std::size_t length = findWhat.size();

    documentView->setSelection({(int)offset, (int)(offset + length)});

    currentOffset = offset + length;
}


void FindReplaceDialogPresenter::handleReplaceNextButton_Click() {
    // TODO: Add implementation
    std::cout << "asdad" << std::endl;
}


void FindReplaceDialogPresenter::handleReplaceAllButton_Click() {
    // TODO: Add implementation
    std::cout << "asdad" << std::endl;
}


void FindReplaceDialogPresenter::handleCloseButton_Click() {
    // TODO: Add implementation
    std::cout << "asdad" << std::endl;
}
