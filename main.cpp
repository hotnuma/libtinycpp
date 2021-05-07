#include "CDirParser.h"
#include "CFile.h"
#include "libpath.h"
#include <string.h>

#include "print.h"

int main()
{
    const char *filepath = "D:\\Downloads\\test.py";

    CFile file;

    if (!file.read(filepath))
        return false;

    CString line;
    while (file.getLine(line))
    {
        print(line);
    }

    return 0;
}


