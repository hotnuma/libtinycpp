#include "libtest.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define _testroot "/tmp/tinycpp_tests"

void test_CString();
void test_CList();
void test_CStringList();

void test_CDirent();
void test_CDirParser();
void test_CFile();
void test_CFileInfo();
void test_CIniFile();
void test_CProcess();
void test_libapp();
void test_libpath();
void test_strfuncs();

void _createFile(const char *filepath)
{
    int fd2 = creat(filepath, 0777);

    if (fd2 != -1)
        close(fd2);
}

int main()
{
    struct stat st;

    if (stat(_testroot, &st) == -1)
    {
        mkdir(_testroot, 0700);
        _createFile(_testroot"/file.txt");

        mkdir(_testroot"/dirAA", 0700);
        mkdir(_testroot"/dirAA/dirA", 0700);
        _createFile(_testroot"/dirAA/dirA/fileA.txt");

        mkdir(_testroot"/dirBB", 0700);
        mkdir(_testroot"/dirBB/dirB", 0700);
        _createFile(_testroot"/dirBB/dirB/fileB.txt");

        mkdir(_testroot"/dirCC", 0700);
        mkdir(_testroot"/dirCC/dirC", 0700);
        _createFile(_testroot"/dirCC/dirC/fileC.txt");
    }

    // core objects
    RUN(test_CString);
    RUN(test_CList);
    RUN(test_CStringList);

    RUN(test_libapp);
    RUN(test_libpath);
    RUN(test_strfuncs);

    RUN(test_CDirent);
    RUN(test_CDirParser);
    RUN(test_CFile);
    RUN(test_CFileInfo);
    RUN(test_CIniFile);
    RUN(test_CProcess);

    return TEST_REPORT();
}


