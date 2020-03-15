
#include "FileService.hpp"

#include <fstream>

std::string FileService::loadFile(const char *fileName) const {
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


void FileService::saveFile(const char *fileName, const char *content) {
    std::fstream fs;
    fs.open(fileName, std::ios_base::out);

    if (!fs.is_open()) {
        // TODO: handle error
    }

    fs << content;
}

