#include "libconv.h"
#include "libtest.h"
#include "CFile.h"
#include <string.h>
#include <stringapiset.h>

extern char g_testroot[];

#define TESTSTR "éèà"

void test_strconv()
{
    wchar_t *wstr = utf8ToWchar(TESTSTR);
    ASSERT(wcscmp(wstr, L"éèà") == 0);

    char *str = wcharToUtf8(wstr);
    ASSERT(strcmp(str, TESTSTR) == 0);

    CString buff = wcharToCString(wstr);
    ASSERT(buff.compare(TESTSTR) == 0);

    CString filepath = strFmt("%s\\strconv.txt", g_testroot);
    CFile file;
    file.read(filepath);
    CString buff2 = strconv(file, CP_ACP, CP_UTF8);
    ASSERT(buff2.compare(TESTSTR) == 0);

    free(wstr);
    free(str);
}


