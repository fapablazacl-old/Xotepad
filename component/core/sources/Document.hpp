
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


enum CMakeToken {
    CMAKE_DEFAULT,
    CMAKE_COMMENT,
    CMAKE_STRINGDQ,
    CMAKE_STRINGLQ,
    CMAKE_STRINGRQ,
    CMAKE_COMMANDS,
    CMAKE_PARAMETERS,
    CMAKE_VARIABLE,
    CMAKE_USERDEFINED,
    CMAKE_WHILEDEF,
    CMAKE_FOREACHDEF,
    CMAKE_IFDEFINEDEF,
    CMAKE_MACRODEF,
    CMAKE_STRINGVAR,
    CMAKE_NUMBER
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


struct TextSelection {
    int start;
    int end;

    static TextSelection all() {
        return {-1, -1};
    }
};


struct Font {
    const std::string &family;
    const int size;
};


class Document {
public:
    virtual ~Document();

    virtual void setContent(const std::string &content) = 0;

    virtual std::string getContent() const = 0;

    virtual void clearContent() = 0;

    virtual void setSelection(const TextSelection &selection) = 0;

    virtual void selectAll() = 0;

    virtual void clearSelection() = 0;

    virtual void undo() = 0;

    virtual void redo() = 0;

    virtual void cut() = 0;

    virtual void copy() = 0;

    virtual void paste() = 0;

    virtual TextSelection getSelection() const = 0;

    virtual void setFont(const Font &font) = 0;

    virtual Font getFont() const = 0;

    virtual void applyLexer(const LexerConfiguration &value) = 0;
};
