#ifndef LIBAPP_H
#define LIBAPP_H

#include "CString.h"

CString getApplicationPath();
CString getApplicationDir();
CString getHomeDirectory();
CString getUserName();

int pexec(const char *cmd);

#if 0
#include "CStringList.h"

bool isFirstInstance(const wchar_t *guid);
CStringList getArguments(const wchar_t *cmdLine = nullptr);

CString getWindowsDirectory();
CStringList getLogicalDrives();

//int uchdir(const char *directory);
#endif

#endif // LIBAPP_H


