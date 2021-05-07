#ifndef LIBCONV_H
#define LIBCONV_H

#include "CString.h"

wchar_t* utf8ToWchar(const char *str);
char* wcharToUtf8(const wchar_t *wstr);
CString wcharToCString(const wchar_t *wstr);
CString strconv(const char *str, int from, int to);

#endif // LIBCONV_H


