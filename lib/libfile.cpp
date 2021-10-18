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



#if 0
bool fileGetLine(char **start, CString &result)
{
    // start of line.
    char *first = *start;

    // end of buffer ?
    if (*first == '\0')
        return false;

    // search end of line.
    char *p = first;

    while (1)
    {
        if (*p == '\r')
        {
            result.clear();
            result.append(first, p - first);
            //*result = first;
            //*length = p - first;

            // skip.
            if (*(p + 1) == '\n')
                ++p;

            // move to next line.
            *start = ++p;

            return true;
        }
        else if (*p == '\n')
        {
            result.clear();
            result.append(first, p - first);
            //*result = first;
            //*length = p - first;

            // move to next line.
            *start = ++p;

            return true;
        }
        else if (*p == '\0')
        {
            result.clear();
            result.append(first, p - first);
            //*result = first;
            //*length = p - first;

            // move to the end.
            *start = p;

            return true;
        }

        ++p;
    }
}

bool fileGetLinePtr(char **start, char **result, int *length)
{
    // start of line.
    char *first = *start;

    // end of buffer ?
    if (*first == '\0')
        return false;

    // search end of line.
    char *p = first;

    while (1)
    {
        if (*p == '\r')
        {
            *result = first;
            *length = p - first;

            // skip.
            if (*(p + 1) == '\n')
                ++p;

            // move to next line.
            *start = ++p;

            return true;
        }
        else if (*p == '\n')
        {
            *result = first;
            *length = p - first;

            // move to next line.
            *start = ++p;

            return true;
        }
        else if (*p == '\0')
        {
            *result = first;
            *length = p - first;

            // move to the end.
            *start = p;

            return true;
        }

        ++p;
    }
}

#endif


