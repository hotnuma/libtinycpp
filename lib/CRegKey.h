#ifndef CREGKEY_H
#define CREGKEY_H

#include "CStringList.h"
#include <wtypes.h>
#include <winreg.h>

class CRegKey
{
public:

    CRegKey();
    ~CRegKey();

    bool open(HKEY root, const char *subkey, REGSAM flags = KEY_READ);
    void close();

    int getSubKeys(CStringList &result);
    bool getString(const char *valueName, CString &result);
    bool getDWord(const char *valueName, DWORD *result);

private:

    HKEY _hkey = 0;
    REGSAM _flags = 0;

};

#endif // CREGKEY_H


