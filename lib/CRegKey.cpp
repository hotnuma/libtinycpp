#include "CRegKey.h"
#include "libconv.h"

//#include "print.h"

CRegKey::CRegKey()
{
}

CRegKey::~CRegKey()
{
    close();
}

void CRegKey::close()
{
    if (!_hkey)
        return;

    RegCloseKey(_hkey);
    _hkey = 0;
}

bool CRegKey::open(HKEY root, const char *subkey, REGSAM flags)
{
    close();

    _flags = flags;

    wchar_t *wsubkey = utf8ToWchar(subkey);
    LONG result = RegOpenKeyExW(HKEY_LOCAL_MACHINE, wsubkey, 0, flags, &_hkey);
    free(wsubkey);

    return (result == ERROR_SUCCESS);
}

int CRegKey::getSubKeys(CStringList &result)
{
    result.clear();

    if (!_hkey)
        return 0;

    DWORD count = 0;
    DWORD maxlen = 0;

    LONG ret = RegQueryInfoKeyW(
        _hkey,
        nullptr,
        nullptr,
        0,
        &count,
        &maxlen,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        nullptr);

    if (ret != ERROR_SUCCESS)
        return 0;

    wchar_t *wbuff = (wchar_t*) malloc((maxlen + 1) * sizeof(wchar_t));

    for (DWORD i = 0; i < count; ++i)
    {
        DWORD cbName = maxlen + sizeof(wchar_t);

        ret = RegEnumKeyExW(
            _hkey,
            i,
            wbuff,
            &cbName,
            nullptr,
            nullptr,
            nullptr,
            nullptr);

        if (ret != ERROR_SUCCESS)
        {
            free(wbuff);
            return 0;
        }

        CString keyname = wcharToCString(wbuff);
        result.append(keyname);
    }

    free(wbuff);

    return count;
}

bool CRegKey::getString(const char *valueName, CString &result)
{
    if (!_hkey)
        return false;

    wchar_t *wname = utf8ToWchar(valueName);

    DWORD needsize = 0;
    DWORD type = REG_NONE;

    LONG status = RegQueryValueExW(_hkey, wname, 0, &type, nullptr, &needsize);

    if (status != ERROR_SUCCESS
        || (type != REG_EXPAND_SZ
            && type != REG_SZ))
    {
        free(wname);
        return false;
    }

    //print("%i", type);

    wchar_t *wbuff = (wchar_t*) malloc(needsize + sizeof(wchar_t));

    status = RegQueryValueExW(_hkey, wname, 0, nullptr, (LPBYTE) wbuff, &needsize);

    free(wname);

    if (status != ERROR_SUCCESS)
    {
        free(wbuff);
        return false;
    }

    //print("%i", needsize);

    int length = (needsize / 2) - 1;
    if (length < 0)
    {
        free(wbuff);
        return false;
    }

    if (wbuff[length] != '\0')
    {
        //print("error length = %i", length);

        wbuff[length + 1] = '\0';
    }

    CString conv = wcharToCString(wbuff);
    free(wbuff);

    result.swap(conv);

    return (status == ERROR_SUCCESS);
}

bool CRegKey::getDWord(const char *valueName, DWORD *result)
{
    if (!_hkey)
        return false;

    wchar_t *wname = utf8ToWchar(valueName);

    DWORD type = REG_NONE;

    LONG status = RegQueryValueExW(_hkey, wname, 0, &type, nullptr, nullptr);

    if (status != ERROR_SUCCESS
        || (type != REG_DWORD))
    {
        free(wname);
        return false;
    }

    DWORD needsize = sizeof(DWORD);
    status = RegQueryValueExW(_hkey, wname, 0, nullptr, (LPBYTE) result, &needsize);

    free(wname);

    if (status != ERROR_SUCCESS)
        return false;

    return (status == ERROR_SUCCESS);
}


