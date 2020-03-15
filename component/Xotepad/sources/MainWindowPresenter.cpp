
#include "MainWindowPresenter.hpp"
#include "MainWindow.hpp"
#include "FileService.hpp"


void MainWindowPresenter::attachView(MainWindow *view) {
    this->view = view;

    documentDirty = false;
    this->updateTitle();
}


void MainWindowPresenter::handleContentModified() {
    documentDirty = true;
    this->updateTitle();
}


MainWindowPresenter::AfterCheckAction MainWindowPresenter::checkDocumentChanges() {
    if (documentDirty) {
        auto result = view->showMessageBoxModal(
            appTitle.c_str(), 
            "Current file was modified. Do you want to save it?", 
            MainWindow::DialogButtons::YesNoCancel, 
            MainWindow::DialogIcon::Question
        );

        if (result == MainWindow::DialogResult::Cancel) {
            return AfterCheckAction::Stop;
        }

        this->handleFileSave();
    }

    return AfterCheckAction::Continue;
}


void MainWindowPresenter::handleFileNew() {
    if (auto action = checkDocumentChanges(); action == AfterCheckAction::Stop) {
        return;
    }

    view->clearContent();

    documentFileName.reset();
    documentDirty = false;
    documentCount ++;

    this->updateTitle();
}


void MainWindowPresenter::handleFileOpen() {
    if (auto action = checkDocumentChanges(); action == AfterCheckAction::Stop) {
        return;
    }

    if (auto fileName = view->showFilePickModal(appTitle)) {
        this->loadFile(*fileName);
    }
}


std::string MainWindowPresenter::getDocumentName() const {
    std::string documentName;

    if (documentFileName) {
        documentName = *documentFileName;
    } else {
        documentName = untitledTitle + " " + std::to_string(documentCount);
    }

    return documentName + (documentDirty ? "*" : "");
}


std::string MainWindowPresenter::computeTitle(const std::string &documentName) const {
    return appTitle + " - " + documentName;
}


void MainWindowPresenter::updateTitle() {
    view->displayTitle(computeTitle(getDocumentName()).c_str());
}


void MainWindowPresenter::loadFile(const std::string &fileName) {
    const FileService fileService;
    const std::string content = fileService.loadFile(fileName.c_str());

    this->documentFileName = fileName;
    this->documentDirty = false;
    
    view->displayContent(content);
    this->updateTitle();
}
