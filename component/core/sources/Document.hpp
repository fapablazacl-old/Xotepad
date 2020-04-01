
#pragma once 

#include <vector>
#include <string>

enum ClikeToken {
    CLIKE_COMMENT,
    CLIKE_COMMENTLINE,
    CLIKE_COMMENTDOC,
    CLIKE_NUMBER,
    CLIKE_WORD,
    CLIKE_STRING,
    CLIKE_CHARACTER,
    CLIKE_UUID,
    CLIKE_PREPROCESSOR,
    CLIKE_OPERATOR,
    CLIKE_IDENTIFIER,
    CLIKE_STRINGEOL,
    CLIKE_VERBATIM,
    CLIKE_REGEX,
    CLIKE_COMMENTLINEDOC,
    CLIKE_WORD2,
    CLIKE_COMMENTDOCKEYWORD,
    CLIKE_COMMENTDOCKEYWORDERROR,
    CLIKE_GLOBALCLASS,
    CLIKE_STRINGRAW,
    CLIKE_TRIPLEVERBATIM,
    CLIKE_HASHQUOTEDSTRING,
    CLIKE_PREPROCESSORCOMMENT,
    CLIKE_PREPROCESSORCOMMENTDOC,
    CLIKE_USERLITERAL,
    CLIKE_TASKMARKER,
    CLIKE_ESCAPESEQUENCE
};


struct Color {
    unsigned char r = 0, g = 0, b = 0;
};


struct TokenStylingInformation {
    int tokenCode;
    Color color;
};


enum class Lexer {
    Text,
    Clike,
    CMake
};


struct LexerConfiguration {
    Lexer lexer;
    std::vector<std::string> keywords;
    std::vector<TokenStylingInformation> tokenStyle;
};
