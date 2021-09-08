#include <libapp.h>

#include "print.h"

int main(int argc, char *argv[])
{
    CString name = getUserName();

    print(name.c_str());

    return 0;
}


