
#pragma once 

#include <string>

extern std::wstring widen(const std::string &src);

extern std::wstring widen(const char *src);

extern std::string narrow(const std::wstring &src);

extern std::string narrow(const wchar_t *src);
