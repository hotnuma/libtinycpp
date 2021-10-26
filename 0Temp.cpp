#if 0

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


