
#pragma once 

#include <string>

class MainWindow {
public:
    virtual ~MainWindow();

    virtual void displayTitle(const std::string &title) = 0;

    virtual void displayContent(const std::string &title) = 0;
};
