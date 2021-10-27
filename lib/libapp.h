#ifndef LIBAPP_H
#define LIBAPP_H

#include "CString.h"

CString getApplicationPath();
CString getApplicationDir();
CString getHomeDirectory();
CString getUserName();

bool dirExists(const char *fileName);
bool fileExists(const char *fileName);
bool fileRemove(const char *fileName);

int pexec(const char *cmd);

#endif // LIBAPP_H


