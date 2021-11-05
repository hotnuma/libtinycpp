#if 0

//-------------------------------------------------------------------

const char* pathExt(const char *path)
{
    const char *sep = pathSep(path);

    if (sep)
    {
        path = ++sep;

        if (*path == '\0')
            return nullptr;
    }

    // hidden file.
    if (*path == '.')
        ++path;

    while (*path)
    {
        if (*path == '.')
            return path;

        ++path;
    }

    return nullptr;
}

CString argsToCString(int argc, char **argv)
{
    CString result(64);
    result.terminate(1);
    int size = 0;

    for (int i = 0; i < argc; ++i)
    {
        char *arg = argv[i];
        int len = strlen(arg);

        if (len < 1)
            continue;

        result.resize(size + len + 2);
        char *p = result.data() + size;
        strcpy(p, arg);
        size += len + 1;
    }

    if (size < 1)
        return result;

    result.resize(size + 1);
    result.terminate(size);

    return result;
}

//-------------------------------------------------------------------

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

CString getApplicationDir()
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

#endif


