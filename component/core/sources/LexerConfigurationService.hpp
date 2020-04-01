
#pragma once 

#include <string>

#include "Document.hpp"

class LexerConfigurationService {
public:
    LexerConfiguration getConfiguration(const std::string &languageId) const;
};
