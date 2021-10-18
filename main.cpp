#include <CRegExp.h>
#include <string.h>

#include <print.h>

int main()
{
    const char *str = "01,bla,02,blé,03,blie";

    CRegExp rx("(\\w+)");

    CString output = str;
    int pos = 0;

    while ((pos = rx.indexIn(str, pos)) != -1)
    {
        CString part = rx.cap(0);

        //print("count = %i", rx.captureCount());

        print(part);

        output += part;
        output += "\n";

        if (strcmp(part.c_str(), "blé") == 0)
        {
            print("found");
        }

        pos += rx.matchedLength();
    }

    return 0;
}


