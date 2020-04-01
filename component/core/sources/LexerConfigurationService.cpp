
#include "LexerConfigurationService.hpp"


LexerConfiguration LexerConfigurationService::getConfiguration(const std::string &languageId) const {
    if (languageId == "c++") {
        LexerConfiguration config;

        config.lexer = Lexer::Clike;

        config.keywords = {
            "alignas", "alignof", "and", "and_eq", "asm", "atomic_cancel", "atomic_commit", 
            "atomic_noexcept", "auto", "bitand", "bitor", "bool", "break", "case", "catch", "char",
            "char16_t", "char32_t", "class", "compl", "concept", "const", "constexpr", "const_cast", 
            "continue", "decltype", "default", "delete", "do",
            "double", "dynamic_cast", "else", "enum", "explicit", "export", "extern", "false", "float", 
            "for", "friend", "goto", "if", "inline", "int", "import", "long",
            "module", "mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr", "operator", 
            "or", "or_eq", "private", "protected", "public",
            "register", "reinterpret_cast", "requires", "return", "short", "signed", "sizeof", "static", 
            "static_assert", "static_cast", "struct",
            "switch", "synchronized", "template", "this", "thread_local", 
            "throw", "true", "try", "typedef", "typeid", "typename", "union", "unsigned",
            "using", "virtual", "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
        };

        config.tokenStyle = {
            {CLIKE_COMMENT, Color{0, 125, 0}}, 
            {CLIKE_COMMENTLINE, Color{0, 125, 0}}, 
            {CLIKE_COMMENTDOC, Color{0, 125, 0}}, 
            {CLIKE_NUMBER, Color{0, 0, 0}}, 
            {CLIKE_WORD, Color{0, 0, 255}},
            {CLIKE_STRING, {125, 0, 0}}, 
            {CLIKE_CHARACTER, {125, 0, 0}}, 
            {CLIKE_UUID, {0, 0, 0}}, 
            {CLIKE_PREPROCESSOR, {160, 0, 255}}, 
            {CLIKE_OPERATOR, {0, 0, 0}}, 
            {CLIKE_IDENTIFIER, {0, 0, 0}}, 
            {CLIKE_STRINGEOL, {0, 0, 0}}, 
            {CLIKE_VERBATIM, {0, 0, 0}}, 
            {CLIKE_REGEX, {0, 0, 0}}, 
            {CLIKE_COMMENTLINEDOC, {0, 0, 0}}, 
            {CLIKE_WORD2, {0, 0, 0}}, 
            {CLIKE_COMMENTDOCKEYWORD, {0, 0, 0}}, 
            {CLIKE_COMMENTDOCKEYWORDERROR, {0, 0, 0}}, 
            {CLIKE_GLOBALCLASS, {0, 0, 0}}, 
            {CLIKE_STRINGRAW, {0, 0, 0}}, 
            {CLIKE_TRIPLEVERBATIM, {0, 0, 0}}, 
            {CLIKE_HASHQUOTEDSTRING, {0, 0, 0}}, 
            {CLIKE_PREPROCESSORCOMMENT, {0, 0, 0}}, 
            {CLIKE_PREPROCESSORCOMMENTDOC, {0, 0, 0}}, 
            {CLIKE_USERLITERAL, {0, 0, 0}}, 
            {CLIKE_TASKMARKER, {0, 0, 0}}, 
            {CLIKE_ESCAPESEQUENCE, {0, 0, 0}}
        };

        return config;
    }

    return {
        Lexer::Text, {""}, {}
    };
}
