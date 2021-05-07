#include "libpath.h"
#include "libtest.h"
#include <string.h>

#include "print.h"

// untested
//bool pathCanonicalize(char *path, int *len)

extern char g_testroot[];

void test_libpath()
{
    CString filepath(30);
    const char *part = nullptr;

    filepath = "C:\\dot.trap\\bla";
    part = pathLastSep(filepath);
    ASSERT(strcmp(part+1, "bla") == 0);

    part = pathExt(filepath);
    ASSERT(!part);

    filepath = "C:\\a\\b\\c\\fileV1.0.txt";
    part = pathExt(filepath);
    ASSERT(strcmp(part, ".txt") == 0);

    CString result;

    result = pathDirName(filepath);
    ASSERT(result.compare("C:\\a\\b\\c") == 0);

    result = pathBaseName(filepath);
    ASSERT(result.compare("C:\\a\\b\\c\\fileV1.0") == 0);

    result = pathFileName(filepath);
    ASSERT(result.compare("fileV1.0.txt") == 0);

}


