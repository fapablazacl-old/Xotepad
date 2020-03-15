
#pragma once 

#include <string>

class FileService {
public:
    std::string loadFile(const char *fileName) const;

    void saveFile(const char *fileName, const char *content);
};
