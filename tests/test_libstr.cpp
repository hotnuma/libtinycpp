#include "libstr.h"
#include "libtest.h"

#include "CFile.h"
#include "print.h"

void test_libstr()
{
    const char *str1 = "bla\r\nble\r\nblie\r\n";
    int eol = streol(str1);
    ASSERT(eol == STREOL_CRLF);

    int len = utf8len("éèà");
    ASSERT(len == 3);

}


