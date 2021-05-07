#ifndef CFILEINFO_H
#define CFILEINFO_H

#include <inttypes.h>

class CFileInfo
{
public:

    CFileInfo(const char *filepath);
    CFileInfo();
    ~CFileInfo();
    void close();

    bool read(const char *filepath);

    const char* path() {return _filepath;}
    bool exists() {return _valid;}

    uint64_t size();
    uint64_t mtime();

private:

    char *_filepath = nullptr;
    void *_handle = (void*) -1;
    bool _valid = false;

};

#endif // CFILEINFO_H


