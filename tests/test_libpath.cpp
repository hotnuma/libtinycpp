#include "libtest.h"
#include "libpath.h"

#include <string.h>

// untested
//bool pathCanonicalize(char *path, int *len)

void test_libpath()
{
    CString filepath(64);
    const char *part = nullptr;

    filepath = "/a/b.c/file";

    part = pathExt(filepath);
    ASSERT(!part);

    filepath = "/a/b.c/file.tar.gz";

    part = pathExt(filepath);
    ASSERT(strcmp(part, ".tar.gz") == 0);

    part = pathSep(filepath);
    ASSERT(strcmp(part, "/file.tar.gz") == 0);

    CString result;

    result = pathDirName(filepath);
    ASSERT(result.compare("/a/b.c") == 0);

    result = pathBaseName(filepath);
    ASSERT(result.compare("file.tar.gz") == 0);

    result = pathJoin("/", "bla");
    ASSERT(result.compare("/bla") == 0);

    result = pathJoin("", "bla");
    ASSERT(result.compare("bla") == 0);

    result = pathJoin("/bla", "blie");
    ASSERT(result.compare("/bla/blie") == 0);

    result = pathJoin("/bla///", "///blie");
    ASSERT(result.compare("/bla/blie") == 0);

}


