#ifndef STRPATH_H
#define STRPATH_H

#include "CString.h"

#define PATHSEP '/'

bool pathIsSep(char c);

const char* pathLastSep(const char *str, int len = -1);
const char* pathExt(const char *str);

int pathCmp(const char *s1, const char *s2);

CString pathDirName(const char *path);
CString pathBaseName(const char *path);
CString pathJoin(const char *dir, const char *file);

bool pathCanonicalize(char *path, int *len);

#endif // STRPATH_H


