
#include "MainWindowPresenter.hpp"
#include "MainWindow.hpp"

#include <fstream>

void MainWindowPresenter::attachView(MainWindow *view) {
    this->view = view;

    documentDirty = false;
    this->updateTitle();
}


void MainWindowPresenter::handleContentModified() {
    documentDirty = true;
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
        const std::string content = loadFile(fileName->c_str());
        view->displayContent(content);
        updateTitle();
    }

    /*
    const CString filter = _T("All Files (*.*)|*.*||");
    const DWORD flags = OFN_LONGNAMES | OFN_PATHMUSTEXIST  | OFN_HIDEREADONLY | OFN_SHOWHELP | OFN_EXPLORER | OFN_ENABLESIZING;
        
    CFileDialog fileDlg(TRUE, NULL, 0, flags, filter);

    if (fileDlg.DoModal(*this) == IDCANCEL) {
        return;
    }

    CString fileName = fileDlg.GetPathName();
    std::string content = loadFile(fileName.c_str());
    */
}


std::string MainWindowPresenter::loadFile(const char *fileName) const {
    std::fstream fs;
    fs.open(fileName, std::ios_base::in);

    if (!fs.is_open()) {
        // TODO: handle error
    }

    std::string content, line;
    while(! fs.eof()) {
        std::getline(fs, line);
        content += line;
        content += "\r\n";
    }

    return content;
}


void MainWindowPresenter::saveFile(const char *fileName, const char *content) {
    std::fstream fs;
    fs.open(fileName, std::ios_base::out);

    if (!fs.is_open()) {
        // TODO: handle error
    }

    fs << content;
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
    return appTitle + " - " + getDocumentName();
}


void MainWindowPresenter::updateTitle() {
    view->displayTitle(computeTitle(getDocumentName()).c_str());
}