#ifndef LIBAPP_H
#define LIBAPP_H

#include "CStringList.h"

bool isFirstInstance(const wchar_t *guid);
CStringList getArguments(const wchar_t *cmdLine = nullptr);
CString getApplicationPath();
CString getApplicationDir();

CString getWindowsDirectory();
CStringList getLogicalDrives();

int uchdir(const char *directory);
int pexec(const char *cmd);

#endif // LIBAPP_H


