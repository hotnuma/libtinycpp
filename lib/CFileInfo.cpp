#define __STDC_FORMAT_MACROS
#include "CFileInfo.h"
#include <wtypes.h>
#include <fileapi.h>
#include "libconv.h"

#define TICKS_PER_MSECOND 10000
#define EPOCH_DIFFERENCE 11644473600000LL

uint64_t fileTimeToMilliseconds(const FILETIME *ft)
{
    uint64_t result = ((uint64_t) ft->dwHighDateTime << 32
                       | ft->dwLowDateTime) / TICKS_PER_MSECOND;
    return result - EPOCH_DIFFERENCE;
}

CFileInfo::CFileInfo()
{
}

CFileInfo::CFileInfo(const char *filepath)
{
    read(filepath);
}

CFileInfo::~CFileInfo()
{
    close();
}

void CFileInfo::close()
{
    if (_filepath)
        free(_filepath);

    _filepath = nullptr;

    if (_handle != INVALID_HANDLE_VALUE)
        CloseHandle(_handle);

    _handle = INVALID_HANDLE_VALUE;
}

bool CFileInfo::read(const char *filepath)
{
    close();

    _valid = false;

    _filepath = strdup(filepath);

    wchar_t* wbuff = utf8ToWchar(_filepath);

    _handle = CreateFileW(wbuff, GENERIC_READ, FILE_SHARE_READ, NULL,
                          OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (_handle == INVALID_HANDLE_VALUE)
        return false;

    _valid = true;

    return true;
}

uint64_t CFileInfo::size()
{
    LARGE_INTEGER li;
    if (!GetFileSizeEx(_handle, &li))
        return 0;

    return (uint64_t) li.QuadPart;
}

uint64_t CFileInfo::mtime()
{
    FILETIME ftime;
    if (!GetFileTime(_handle, NULL, NULL, &ftime))
        return 0;

    return fileTimeToMilliseconds(&ftime);
}


