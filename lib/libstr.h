#ifndef LIBSTR_H
#define LIBSTR_H

#include "CString.h"

#define STREOL_NONE 0
#define STREOL_LF 1
#define STREOL_CRLF 2
#define STREOL_CR 3

CString strCurrentTime(const char *fmt);
bool strGetPart(char **start, char **result, int *length);

char* stristr(const char *haystack, const char *needle);
char* strrstr(const char *haystack, const char *needle);
int streol(const char *str, int *pos = nullptr);

int utf8len(const char *str);
CString utf8wrap(const char *str, int num);

#endif // LIBSTR_H


