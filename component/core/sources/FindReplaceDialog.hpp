
#pragma once 

#include <string>
#include <optional>

class FindReplaceDialogPresenter;
class FindReplaceDialog {
public:
    enum SearchScope {
        Selection = 0,
        CurrentDocument = 1
    };

    struct ViewData {
        std::string title;
        std::string findWhat;
        std::optional<std::string> replaceWith;

        bool matchCase = false;
        bool matchWholeWorld = false;

        SearchScope scope = CurrentDocument;
    };

public:
    virtual ~FindReplaceDialog();

    virtual void attachPresenter(FindReplaceDialogPresenter *presenter) = 0;

    virtual void show(const ViewData &viewData) = 0;

    virtual void hide() = 0;

    virtual void toggleReplaceControls(const bool status) = 0;
};
