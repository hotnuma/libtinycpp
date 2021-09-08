#include "libstr.h"
#include "libtest.h"

#include "CFile.h"
#include "print.h"

//CString utf8wrap(const char *str, int num);

void test_strfuncs()
{
    CString time = strCurrentTime("%Y");
    ASSERT(time.compare("1980") > 0);

//    CString filepath = strFmt("%s\\%s", _testroot, "\\streol.txt");
//    CFile file;
//    file.read(filepath);
//    int eol = streol(file);
//    ASSERT(eol == STREOL_CR);

    int len = utf8len("éèà");
    ASSERT(len == 3);

}


