#include "libtest.h"
#include <stdio.h>
#include <wtypes.h>

extern char g_testroot[];

void test_CString();
void test_CList();
void test_CStringList();

void test_CDirent();
void test_CDirParser();
void test_CFile();
void test_CFileInfo();
void test_CIniFile();
void test_CProcess();
void test_CRegKey();
void test_fnmatch();
void test_libapp();
void test_libfile();
void test_libpath();
void test_strconv();
void test_strfuncs();

void _setDirectory()
{
    int len = strlen(g_testroot);
    char *p = g_testroot + len;

    while (p > g_testroot)
    {
        if (*p == '\\')
        {
            ++p;
            break;
        }
        --p;
    }

    if (strcmp(p, "build") != 0)
        return;

    strcpy(p, "tests\\test_dir");
}

int main()
{
    testInit();

    _setDirectory();

    // core objects
    RUN(test_CString);
    RUN(test_CList);
    RUN(test_CStringList);

    RUN(test_fnmatch);
    RUN(test_libapp);
    RUN(test_libfile);
    RUN(test_libpath);
    RUN(test_strconv);
    RUN(test_strfuncs);

    RUN(test_CDirent);
    RUN(test_CDirParser);
    RUN(test_CFile);
    RUN(test_CFileInfo);
    RUN(test_CIniFile);
    RUN(test_CProcess);
    RUN(test_CRegKey);

    int ret = TEST_REPORT();

    testRelease();

    return ret;
}


