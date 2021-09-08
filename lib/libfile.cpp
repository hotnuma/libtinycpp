#include "libfile.h"
#include <stdio.h>
#include <sys/stat.h>

bool dirExists(const char *fileName)
{
    struct stat buffer;
    int result = stat(fileName, &buffer);

    return (result == 0 && (buffer.st_mode & S_IFDIR));
}

bool fileExists(const char *fileName)
{
    struct stat buffer;
    int result = stat(fileName, &buffer);

    return (result == 0 && (buffer.st_mode & S_IFREG));
}

bool fileRemove(const char *fileName)
{
    return (remove(fileName) == 0);
}

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


#if 0
bool fileRead(const char *fileName, CString &result)
{
    wchar_t* wbuff = utf8ToWchar(fileName);
    FILE *fp = _wfopen(wbuff, L"rb");
    free(wbuff);

    if (!fp)
        return false;

    fseek(fp, 0, SEEK_END);
    unsigned long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    result.resize(size + 1);

    if (fread(result.data(), 1, size, fp) != size)
    {
        result.clear();
        fclose(fp);
        return false;
    }

    fclose(fp);

    result.terminate(size);

    return true;
}

bool fileWrite(const char *fileName, const CString &buffer)
{
    wchar_t* wbuff = utf8ToWchar(fileName);
    FILE *fp = _wfopen(wbuff, L"wb");
    free(wbuff);

    if (!fp)
        return false;

    const char *buff = buffer.c_str();
    size_t size = buffer.size();

    size_t ret = fwrite(buff, 1, size, fp);

    //print("size = %d", ret);

    if (ret != size)
    {
        fclose(fp);
        return false;
    }

    fflush(fp);
    fclose(fp);

    return true;
}

#endif


