#include "CIniFile.h"
#include "libtest.h"
#include <ctype.h>
#include "CString.h"

#include "print.h"

extern char g_testroot[];

void test_CIniFile()
{
    CString fullpath = g_testroot;
    fullpath += "\\inifile.ini";

    CIniFile file;
    bool ret = file.open(fullpath);
    ASSERT(ret);

    CString value;
    int count = file.size();
    ASSERT(count == 2);

    CIniSection *section = file.sectionAt(0);
    ASSERT(section);

    value = section->value("key2", "-1");
    ASSERT(value.compare("b") == 0);

    section = file.section("Section2");
    ASSERT(section);

    value = section->value("key2", "-1");
    ASSERT(value.compare("e") == 0);

}


