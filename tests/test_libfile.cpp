#include "libfile.h"
#include "libtest.h"

//#include "print.h"

extern char g_testroot[];

#define LIBFILECONTENT "bla\nble\nblie\n"

void test_libfile()
{
    ASSERT(dirExists(g_testroot));

    CString filepath = strFmt("%s\\%s", g_testroot, "\\libfile.txt");
    fileRemove(filepath);
    ASSERT(!fileExists(filepath));

#if 0
    fileWrite(filepath, LIBFILECONTENT);
    ASSERT(fileExists(filepath));

    CString buffer;
    fileRead(filepath, buffer);
    ASSERT(buffer.compare(LIBFILECONTENT) == 0);

    CString buff;
    char *ptr = buffer.data();
    char *result = nullptr;
    int length = 0;
    while (fileGetLinePtr(&ptr, &result, &length))
    {
        buff.append(result, length);
        buff.append("\n");
    }
    ASSERT(buff.compare(LIBFILECONTENT) == 0);

    //buff.clear();
    //CStringList list;
    //fileRead(filepath, list);
    //int count = list.size();
    //for (int i = 0; i < count; ++i)
    //{
    //    const CString &item = list.at(i);
    //    buff.append(item.c_str());
    //    buff.append("\n");
    //}
    //ASSERT(buff.compare(LIBFILECONTENT) == 0);

    ASSERT(fileExists(filepath));

    fileRemove(filepath);
    ASSERT(!fileExists(filepath));

#endif

}


