#ifndef FILE_H
#define FILE_H

#include "CStringList.h"

bool dirExists(const char *fileName);
bool fileExists(const char *fileName);
bool fileRemove(const char *fileName);

bool fileGetLine(char **start, CString &result);
bool fileGetLinePtr(char **start, char **result, int *length);

#if 0
bool fileRead(const char *fileName, CString &result);
bool fileWrite(const char *fileName, const CString &buffer);
#endif

#endif // FILE_H


