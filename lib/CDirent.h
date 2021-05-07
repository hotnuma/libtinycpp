#ifndef CDIRENT_H
#define CDIRENT_H

#include "CString.h"
#include "wdirent.h"

class CDirent
{
public:

    CDirent();
    CDirent(const char *basedir);
    ~CDirent();

    bool open(const char *basedir);
    void close();
    bool read(CString &result, int *type = nullptr);
    const CString& directory() {return _basedir;}

    //const char* directoryPtr() {return _basedir.c_str();}

private:

    void *_dir = nullptr;
    bool _skipdot = true;

    CString _basedir;

};

#endif // CDIRENT_H


