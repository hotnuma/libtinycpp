#include "CFile.h"
#include "libtest.h"
#include "libfile.h"

extern char g_testroot[];

//~CFile();

void test_CFile()
{
    CString filepath = strFmt("%s\\%s", g_testroot, "\\file.txt");
    fileRemove(filepath);

    CFile file;
    file.open(filepath, "wb");

    file << "bla";
    file << "\n";
    file << "ble";
    file << "\n";
    file << "blie";
    file << "\n";

    file.flush();
    file.close();

    file.read(filepath);
    ASSERT(file.buffer().compare("bla\nble\nblie\n") == 0);

    fileRemove(filepath);

    return;
}


