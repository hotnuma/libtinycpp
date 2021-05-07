#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include "CFileInfo.h"
#include "libtest.h"
#include <string.h>
#include "CString.h"

#include "print.h"

//CFileInfo(const char *filepath);
//~CFileInfo();
//void close();

extern char g_testroot[];

void test_CFileInfo()
{
    CString fullpath = g_testroot;
    fullpath += "\\abc.txt";

    CFileInfo file;
    bool ret = file.read(fullpath);
    ASSERT(ret);
    ASSERT(file.exists());
    ASSERT(strcmp(fullpath.c_str(), file.path()) == 0);

    size_t size = file.size();
    ASSERT(size == 3);

    uint64_t time = file.mtime();
    ASSERT(time > 1514761200000);

}


