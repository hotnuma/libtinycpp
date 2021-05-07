#include "libapp.h"
#include <direct.h>
#include <wtypes.h>
#include <shellapi.h>
#include <libloaderapi.h>
#include "libconv.h"
#include "libpath.h"

bool isFirstInstance(const wchar_t *guid)
{
    ::SetLastError(NO_ERROR);

    ::CreateMutexW(NULL, false, guid);

    if (::GetLastError() == ERROR_ALREADY_EXISTS)
        return false;

    return true;
}

CStringList getArguments(const wchar_t *cmdLine)
{
    if (!cmdLine)
        cmdLine = ::GetCommandLineW();

    CStringList result;

    LPWSTR *wargs;
    int num;

    wargs = ::CommandLineToArgvW(cmdLine, &num);
    if (!wargs)
       return result;

    for (int i = 0; i < num; ++i)
    {
        CString arg = wcharToCString(wargs[i]);
        result.append(arg);
    }

    ::LocalFree(wargs);

    return result;
}

CString getApplicationPath()
{
    CString result(100);

    int buffsize = MAX_PATH;
    wchar_t *wbuff = (wchar_t*) malloc(buffsize * sizeof(wchar_t));

    int size = ::GetModuleFileNameW(0, wbuff, buffsize);

    if (size == 0)
        return result;

    result = wcharToCString(wbuff);

    free(wbuff);

    return result;
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

CString getWindowsDirectory()
{
    CString result(100);

    int buffsize = MAX_PATH;
    wchar_t *wbuff = (wchar_t*) malloc(buffsize * sizeof(wchar_t));

    UINT ret = ::GetWindowsDirectoryW(wbuff, MAX_PATH);
    if (ret == 0 || ret > MAX_PATH)
        return result;

    result = wcharToCString(wbuff);

    free(wbuff);

    return result;
}

CStringList getLogicalDrives()
{
    CStringList result;

    DWORD bits = ::GetLogicalDrives();
    char drive[] = "A:\\";

    for (int i = 0; i < 26; ++i)
    {
        if (bits & (1 << i))
        {
            drive[0] = 'A' + i;
            result.append(drive, 3);
        }
    }

    return result;
}

int uchdir(const char *directory)
{
    if (!directory)
        return -1;

    wchar_t *wdir = utf8ToWchar(directory);
    int ret = _wchdir(wdir);
    if (wdir)
        free(wdir);

    return ret;
}

int pexec(const char *cmd)
{
    STARTUPINFOW si = {0};
    PROCESS_INFORMATION pi = {0};

    wchar_t *wcmd = utf8ToWchar(cmd);

    bool ret = ::CreateProcessW(nullptr,
                                wcmd,
                                nullptr,
                                nullptr,
                                true,
                                0,
                                nullptr,
                                nullptr,
                                &si,
                                &pi);
    if (ret)
    {
        ::CloseHandle(pi.hProcess);
        ::CloseHandle(pi.hThread);
    }

    if (wcmd)
        free(wcmd);

    return ret;
}


