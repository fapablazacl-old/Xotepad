
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


bool wildcard_match(const char * wildcard, char * const name) {
    const size_t len = std::strlen(wildcard);

    char *ch = name;

    for (size_t i=0; i<len; i++) {
        const char wc_token = wildcard[i];

        switch (wc_token) {
        case '?':
            if (*ch == '\0') {
                return false;
            }
            ++ch;

            break;

        case '*':

            break;

        default:
            if (*ch != wc_token) {
                return false;
            }
            ++ch;

            break;
        }
    }

    return *ch == '\0';
}
