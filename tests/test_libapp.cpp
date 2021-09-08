#include "libapp.h"

#include "libtest.h"
#include "CString.h"

#include <string.h>

// untested
//CStringList getArguments(const wchar_t *cmdLine = nullptr);
//bool isFirstInstance(const wchar_t *guid);
//int uchdir(const char *directory);
//int pexec(const char *cmd);

void test_libapp()
{
    CString path = getApplicationPath();
    ASSERT(path.endsWith("/tinytest"));

//    path = getApplicationDir();
//    ASSERT(strncmp(_testroot, path.c_str(), path.size() - 6) == 0);

    //path = getWindowsDirectory();
    //ASSERT(path.endsWith("Windows"));

    //CStringList list = getLogicalDrives();
    //ASSERT(list.size() > 1);
    //ASSERT(list.at(0).compare("C:\\") == 0);

}


