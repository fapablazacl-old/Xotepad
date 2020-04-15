
#include "FindReplaceDialogPresenter.hpp"
#include "Document.hpp"

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
    std::size_t offset = content.find(findWhat, currentOffset);

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
