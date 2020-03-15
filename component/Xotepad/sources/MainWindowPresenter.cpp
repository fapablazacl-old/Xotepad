
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
    if (auto action = this->checkDocumentChanges(); action == AfterCheckAction::Stop) {
        return;
    }

    this->newFile();
}


MainWindowPresenter::DialogResult MainWindowPresenter::handleFileSave() {
    if (documentFileName) {
        this->saveFile(*documentFileName, view->getContent());

        return MainWindowPresenter::DialogResult::Accept;
    }

    return this->handleFileSaveAs();
}


MainWindowPresenter::DialogResult MainWindowPresenter::handleFileSaveAs() {
    if (auto result = view->showFilePickModal(MainWindow::FileDialog::Save, "Save File ..."); result) {
        const std::string fileName = *result;
        const std::string content = view->getContent();

        this->saveFile(fileName, content);

        return MainWindowPresenter::DialogResult::Accept;
    }

    MainWindowPresenter::DialogResult::Cancel;
}


void MainWindowPresenter::newFile() {
    view->clearContent();

    documentFileName.reset();
    documentDirty = false;
    documentCount ++;

    this->updateTitle();
}


void MainWindowPresenter::handleFileOpen() {
    if (auto action = this->checkDocumentChanges(); action == AfterCheckAction::Stop) {
        return;
    }

    if (auto fileName = view->showFilePickModal(MainWindow::FileDialog::Open, appTitle)) {
        this->loadFile(*fileName);
    }
}


std::string MainWindowPresenter::getDocumentTitle() const {
    std::string title;

    if (documentFileName) {
        title = *documentFileName;
    } else {
        title = untitledTitle + " " + std::to_string(documentCount);
    }

    return title + (documentDirty ? "*" : "");
}


std::string MainWindowPresenter::computeTitle(const std::string &documentTitle) const {
    return appTitle + " - " + documentTitle;
}


void MainWindowPresenter::updateTitle() {
    view->setTitle(computeTitle(getDocumentTitle()).c_str());
}


void MainWindowPresenter::loadFile(const std::string &fileName) {
    const FileService fileService;
    const std::string content = fileService.loadFile(fileName.c_str());

    this->documentFileName = fileName;
    this->documentDirty = false;
    
    view->setContent(content);
    this->updateTitle();
}


void MainWindowPresenter::saveFile(const std::string &fileName, const std::string &content) {
    FileService fileService;
    fileService.saveFile(fileName.c_str(), content.c_str());

    this->documentFileName = fileName;
    this->documentDirty = false;
    
    this->updateTitle();
}
