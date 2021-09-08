#include "libfile.h"
#include "libtest.h"
#include <fcntl.h>
#include <unistd.h>

void test_libfile()
{
    ASSERT(dirExists("/tmp"));

    CString filepath = "/tmp/tinycpp_test.txt";

    int fd = open(filepath, O_RDWR|O_CREAT, 0777);
    if (fd != -1)
        close(fd);

    ASSERT(fileExists(filepath));

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


