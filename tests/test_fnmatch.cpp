#include "fnmatch.h"
#include "libtest.h"

void test_fnmatch()
{
    const char *path = "C:\\file.txt";

    int ret = fnmatch("*.txt", path, 0);
    ASSERT(ret == 0);

    ret = fnmatch("*.bat", path, 0);
    ASSERT(ret != 0);

}


