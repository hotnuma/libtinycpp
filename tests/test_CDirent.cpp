#include "CDirent.h"
#include "libtest.h"
#include <wtypes.h>

#include "print.h"

extern char g_testroot[];

// untested
// ~CDirent();
// const char* directory() {return _basedir.c_str();}

void test_CDirent()
{
    CString result;

    CDirent dirA(g_testroot);
    bool found = false;
    int count = 0;
    int numdirs = 0;
    int type = 0;
    while (dirA.read(result, &type))
    {
        if (S_ISDIR(type))
        {
            if (result == "dirB")
                found = true;
            ++numdirs;
        }
        ++count;
    }

    ASSERT(found);
    ASSERT(numdirs == 3);
    ASSERT(count == 7);

    CDirent dirB;
    ASSERT(dirB.open(g_testroot));

    found = false;
    count = 0;
    int numfiles = 0;
    while (dirB.read(result, &type))
    {
        if (S_ISREG(type))
        {
            if (result == "abc.txt")
                found = true;
            ++numfiles;
        }
        ++count;
    }

    ASSERT(found);
    ASSERT(numfiles == 4);
    ASSERT(count == 7);

    dirB.close();

}


