
#include "WindowsUtils.hpp"

#include <locale>
#include <codecvt>


std::wstring widen(const std::string &src) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring result = converter.from_bytes(src);

    return result;
}


std::wstring widen(const char *src) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring result = converter.from_bytes(src);

    return result;
}


std::string narrow(const std::wstring &src) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string result = converter.to_bytes(src);

    return result;
}


std::string narrow(const wchar_t *src) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string result = converter.to_bytes(src);

    return result;
}


bool wildcard_match(const char *pattern, const char *text) {
    const size_t pattern_len = std::strlen(pattern);
    const char *text_ptr = text;

    for (size_t i=0; i<pattern_len; i++) {
        const char pattern_char = pattern[i];

        switch (pattern_char) {
        case '?':
            if (*text_ptr == '\0') {
                return false;
            }
            ++text_ptr;

            break;

        case '*': {
            const char pattern_next_char = pattern[i + 1];

            if (pattern_next_char == '\0') {
                return true;
            }

            if (pattern_next_char == *(text_ptr + 1)) {
                return wildcard_match( &pattern[i + 1], (text_ptr + 1) );
            } else {
                return wildcard_match( &pattern[i], (text_ptr + 1) );
            }

            return false;
        }

        default:
            if (*text_ptr != pattern_char) {
                return false;
            }
            ++text_ptr;

            break;
        }
    }

    return *text_ptr == '\0';
}
