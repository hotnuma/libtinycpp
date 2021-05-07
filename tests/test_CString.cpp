#include "CString.h"
#include "libtest.h"
#include "string.h"

#include "print.h"

//CString enquote(const char *str);
//int	indexOf(const char *str, int from = 0, bool sensitive = true) const;
//int lastIndexOf(const char *str, int from = -1, bool sensitive = true) const;
//CString left(int length) const;
//CString mid(int index, int length = -1) const;
//CString(const CString &str);
//CString(const char *str, int length = -1);
//~CString();
//void resize(int capacity);
//void terminate(int length = -1);
//CString trimmed() const;

void test_CString()
{
    int array[10];
    ASSERT(ARRAY_SIZE(array) == 10);

    ASSERT(MIN(2, 10) == 2);
    ASSERT(MAX(2, 10) == 10);

    char *buff = stralloc(4);
    strcpy(buff, "abc");
    ASSERT(strcmp(buff, "abc") == 0);

    wchar_t *wbuff = wcsalloc(4);
    wcscpy(wbuff, L"abc");
    ASSERT(wcscmp(wbuff, L"abc") == 0);

    CString strA(10);
    ASSERT(strA.isEmpty());
    ASSERT(strA.size() == 0);
    ASSERT(strA.capacity() == 10);
    ASSERT(strcmp(strA.c_str(), "") == 0);
    ASSERT(strcmp(strA.data(), "") == 0);

    strA = strFmt("%s%c %d", "bl", 'a', 666);
    ASSERT(!strA.isEmpty());
    ASSERT(strcmp(strA, "bla 666") == 0);

    strA = strRepeat("bla", 3);
    ASSERT(strcmp(strA, "blablabla") == 0);

    strA = "a";
    strA += CString("XX");
    strA += ",BB";
    strA.chop(1);
    strA.append(',');
    strA.append("c,DDD,eeeee", 7);
    strA.replace("c,DDD", "c,D");
    strA.remove(1, 2);
    strA.toLower();
    ASSERT(strA == "a,b,c,d,e");
    strA.toUpper();
    ASSERT(strA == "A,B,C,D,E");
    ASSERT(strA != "a,b,c,d,e");
    ASSERT(strcmp(strA, "A,B,C,D,E") == 0);
    ASSERT(strA.contains(",c,", false));
    ASSERT(strA.startsWith("A"));
    ASSERT(strA.endsWith("e", false));
    ASSERT(strA.compare("a,B,c,D,e", false) == 0);
    ASSERT(strA.first() == 'A');
    ASSERT(strA.last() == 'E');
    ASSERT(strA[4] == 'C');

    CString strB;
    strB = uint64ToStr(666);
    ASSERT(strB == "666");
    strB = intToStr(42);
    ASSERT(strB == "42");
    ASSERT(strB.toInt() == 42);
    strB = unquote("'abc'");
    ASSERT(strB == "abc");

    strB.swap(strA);
    ASSERT(strB == "A,B,C,D,E");
    ASSERT(strA == "abc");
    strA.clear();
    ASSERT(strA.isEmpty());

}


