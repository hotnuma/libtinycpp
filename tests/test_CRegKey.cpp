#include "CRegKey.h"
#include "libtest.h"

#include "print.h"

void test_CRegKey()
{
    CRegKey key;

    key.open(HKEY_CLASSES_ROOT,
             "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");
    CString result;
    key.getString("SystemRoot", result);
    ASSERT(result.compare("C:\\Windows") == 0);

    key.open(HKEY_LOCAL_MACHINE, "SYSTEM\\CurrentControlSet");
    CStringList list;
    key.getSubKeys(list);
    ASSERT(list.at(0).compare("Control") == 0);

}


