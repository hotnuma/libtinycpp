#include "CDirent.h"
#include "libconv.h"
#include "libpath.h"

CDirent::CDirent()
{
}

CDirent::CDirent(const char *basedir)
{
    open(basedir);
}

CDirent::~CDirent()
{
    close();
}

bool CDirent::open(const char *basedir)
{
    if (_dir)
        close();

    _basedir = basedir;

    if (pathIsSep(_basedir.last()))
        _basedir.chop(1);

    wchar_t *tmp = utf8ToWchar(basedir);
    _dir = _wopendir(tmp);
    free(tmp);

    if (!_dir)
        return false;

    return true;
}

void CDirent::close()
{
    if (_dir)
    {
        _wclosedir((_WDIR*) _dir);
        _dir = nullptr;
    }
}

bool CDirent::read(CString &result, int *type)
{
    if (!_dir)
        return false;

    readnext:
    struct _wdirent *nextp = _wreaddir((_WDIR*) _dir);

    if (!nextp)
        return false;

    if (_skipdot
        && (wcscmp(nextp->d_name, L".") == 0
            || wcscmp(nextp->d_name, L"..") == 0))
        goto readnext;

    char *tmp = wcharToUtf8(nextp->d_name);
    result = tmp;
    free(tmp);

    if (type)
        *type = nextp->d_type;

    return true;
}


