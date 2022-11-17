#ifndef LIBSTR_H
#define LIBSTR_H

#include <stdlib.h>

#define STREOL_NONE 0
#define STREOL_LF 1
#define STREOL_CRLF 2
#define STREOL_CR 3

inline char* stralloc(int size)
{
    return (char*) malloc(size * sizeof(char));
}

inline wchar_t* wcsalloc(int size)
{
    return (wchar_t*) malloc(size * sizeof(wchar_t));
}

bool strGetPart(char **start, char **result, int *length);
bool strGetLinePtr(char **start, char **result, int *length);

char* stristr(const char *haystack, const char *needle);
char* strrstr(const char *haystack, const char *needle);
int streol(const char *str, int *pos = nullptr);

int utf8len(const char *str);

#endif // LIBSTR_H


