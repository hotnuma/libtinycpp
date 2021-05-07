#include "libconv.h"
#include <stdlib.h>
#include <stringapiset.h>

wchar_t* utf8ToWchar(const char *str)
{
    if (!str)
        return nullptr;

    int wsize = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    wchar_t* wbuff = (wchar_t*) malloc(wsize * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wbuff, wsize);

    return wbuff;
}

char* wcharToUtf8(const wchar_t *wstr)
{
    if (!wstr)
        return nullptr;

    int size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* buff = (char*) malloc(size * sizeof(char));
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, buff, size, NULL, NULL);

    return buff;
}

CString wcharToCString(const wchar_t *wstr)
{
    CString buff;
    if (!wstr)
        return buff;

    int size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);

    if (size < 1)
        return buff;

    buff.resize(size);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, buff.data(), buff.capacity(), NULL, NULL);
    buff.terminate(size - 1);

    return buff;
}

CString strconv(const char *str, int from, int to)
{
    CString buff;
    if (!str)
        return buff;

    // from -> wchar.

    int size = MultiByteToWideChar(from, 0, str, -1, NULL, 0);

    if (size < 1)
        return buff;

    wchar_t* wstr = (wchar_t*) malloc(size * sizeof(wchar_t));
    MultiByteToWideChar(from, 0, str, -1, wstr, size);

    // wchar -> to.

    size = WideCharToMultiByte(to, 0, wstr, -1, NULL, 0, NULL, NULL);

    if (size < 1)
    {
        free(wstr);
        return buff;
    }

    buff.resize(size);
    WideCharToMultiByte(to, 0, wstr, -1, buff.data(), buff.capacity(), NULL, NULL);
    buff.terminate(size - 1);

    free(wstr);

    return buff;
}


