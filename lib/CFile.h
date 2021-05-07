#ifndef CFILE_H
#define CFILE_H

#include "CString.h"
#include <stdio.h>

class CFile
{
public:

    CFile();
    ~CFile();

    bool open(const char *filepath, const char *mode = "rb");

    bool read(const char *filepath);
    void write(const char *str);
    void operator<<(const char *str);

    bool getLinePtr(char **result, int *length);
    bool getLine(CString &result);

    void flush();
    void close();

    operator const char*() const {return _buffer.c_str();}
    CString& buffer() {return _buffer;}

    //const char* c_str() const {return _buffer;}
    //char* data() const {return _buffer;}
    //const int size() const {return _length;}

    static bool write(const char *filepath, const CString &buffer);

private:

    CString _buffer;
    //bool _read();

    FILE *_fp = nullptr;
    char *_curr = nullptr;

};

#endif // CFILE_H


