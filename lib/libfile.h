#ifndef FILE_H
#define FILE_H

#include "CStringList.h"

bool dirExists(const char *fileName);
bool fileExists(const char *fileName);
bool fileRemove(const char *fileName);

#if 0
bool fileGetLine(char **start, CString &result);
bool fileGetLinePtr(char **start, char **result, int *length);
#endif

#endif // FILE_H


