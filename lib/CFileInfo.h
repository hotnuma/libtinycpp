#ifndef CFILEINFO_H
#define CFILEINFO_H

#include <inttypes.h>
#include <sys/stat.h>

class CFileInfo
{
public:

    CFileInfo(const char *filepath);
    CFileInfo();
    ~CFileInfo();
    //void close();

    bool read(const char *filepath);

    //const char* path() {return _filepath;}
    bool exists() {return _valid;}

    long size();
    uint64_t mtime();

private:

    //char *_filepath = nullptr;
    //int _fd = -1;

    struct stat _sb;
    bool _valid = false;

};

#endif // CFILEINFO_H


