
#include "WindowsUtils.hpp"

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
