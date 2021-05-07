#include "CDirParser.h"
#include "libtest.h"

#include "print.h"

// untested
//CDirIterator(const char *directory, int flags = DF_DIRS | DF_FILES);
//void close();

extern char g_testroot[];

void test_CDirParser()
{
    CDirParser dir;
    CString filepath;

    bool ret = dir.open(g_testroot, CDP_SUBDIRS | CDP_DIRS);
    ASSERT(ret);

    int count = 0;
    while (dir.read(filepath))
    {
        //print(filepath.c_str());
        ++count;
    }
    ASSERT(count == 3);

    ret = dir.open(g_testroot, CDP_SUBDIRS | CDP_FILES);
    ASSERT(ret);

    count = 0;
    while (dir.read(filepath))
    {
        //print(filepath.c_str());
        ++count;
    }
    ASSERT(count == 7);

}


