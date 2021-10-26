#if 0

int _strdirlen(const char *str)
{
    if (!str)
        return 0;

    const char *p = str;
    const char *last = nullptr;

    while (*p)
    {
        if (*p != '/')
            last = p;

        ++p;
    }

    if (!last)
        return 0;

    return (last + 1) - str;
}

const char* _strskipsep(const char *str)
{
    if (!str)
        return nullptr;

    while (*str)
    {
        if (*str != '/')
            return str;

        ++str;
    }

    return nullptr;
}

char _strgetsep(const char *str)
{
    char sep = PATHSEP;

    if (!str)
        return sep;

    while (*str)
    {
        if (*str == '/')
            return *str;

        ++str;
    }

    return sep;
}

// Path separator.
bool pathIsSep(char c)
{
#ifdef _WIN32
    return c == '/' || c == '\\';
#else
    return c == '/';
#endif
}

const char* pathLastSep(const char *str, int len)
{
    if (!str)
        return nullptr;

    if (len < 0)
        len = strlen(str);

    if (len < 1)
        return nullptr;

    const char *last = str + len - 1;

    while (last > str)
    {
        if (pathIsSep(*last))
            return last;

        --last;
    }

    return nullptr;
}

CString pathDirName(const char *path)
{
    int length = 0;
    const char *last = pathLastSep(path);

    if (last)
        length = last - path;

    return CString(path, length);
}

CString getApplicationDir_old()
{
    CString path = getApplicationPath();
    int len = path.size();

    if (len < 1)
    {
        path.clear();
        return path;
    }

    char *str = path.data();
    const char *last = pathLastSep(str, len);

    if (last)
        path.terminate(last - str);
    else
        path.clear();

    return path;
}

CString pathFileName(const char *path)
{
    int length = strlen(path);
    const char *str = path + length;

    const char *last = pathLastSep(path);

    if (last && last < str)
    {
        ++last;
        length = strlen(last);
        str = last;
    }

    return CString(str, length);
}

void closeHandlePtr(void **ptr)
{
    if (!ptr || !*ptr)
        return;

    ::CloseHandle(*ptr);
    *ptr = nullptr;
}

static int _readPipe(void *handle, CString &outBuff)
{
    if (!handle)
        return -1;

    DWORD avail;
    if (!::PeekNamedPipe(handle, 0, 0, 0, &avail, 0))
    {
        //print("peek broken");
        return 0;
    }

    if (!avail)
        return 1;

    //print("peek = %i", avail);

    int length = outBuff.size();
    outBuff.resize(length + avail + 1);

    char *buff = outBuff.data() + length;
    DWORD numRead;

    if (!::ReadFile(handle, buff, avail, &numRead, 0))
    {
        //print("read broken");
        return 0;
    }

    int num = (numRead < avail) ? numRead : avail;
    outBuff.terminate(length + num);

    //print("read = %i", numRead);

    return 1;
}


#endif


