#include "libfile.h"

#include <stdio.h>
#include <sys/stat.h>

bool dirExists(const char *fileName)
{
    struct stat st;
    int result = stat(fileName, &st);

    return (result == 0 && (st.st_mode & S_IFDIR));
}

bool fileExists(const char *fileName)
{
    struct stat st;
    int result = stat(fileName, &st);

    return (result == 0 && (st.st_mode & S_IFREG));
}

bool fileRemove(const char *fileName)
{
    return (remove(fileName) == 0);
}


