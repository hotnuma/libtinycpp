#include "libapp.h"
#include "libtest.h"
#include <string.h>

//#include "print.h"

// untested
//CStringList getArguments(const wchar_t *cmdLine = nullptr);
//bool isFirstInstance(const wchar_t *guid);
//int uchdir(const char *directory);
//int pexec(const char *cmd);

extern char g_testroot[];

void test_libapp()
{
    CString path = getApplicationPath();
    ASSERT(path.endsWith("tinytest.exe"));

    path = getApplicationDir();
    ASSERT(strncmp(g_testroot, path.c_str(), path.size() - 6) == 0);

    path = getWindowsDirectory();
    ASSERT(path.endsWith("Windows"));

    CStringList list = getLogicalDrives();
    ASSERT(list.size() > 1);
    ASSERT(list.at(0).compare("C:\\") == 0);

}


