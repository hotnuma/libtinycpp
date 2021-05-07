#include "CFile.h"

#include <stdlib.h>
#include <string.h>
#include "libconv.h"

CFile::CFile()
{
}

CFile::~CFile()
{
    close();

//    if (_buffer)
//        delete _buffer;
}

void CFile::flush()
{
    if (_fp)
        fflush(_fp);
}

void CFile::close()
{
    if (_fp)
        fclose(_fp);

    _fp = nullptr;
    _curr = nullptr;
}

bool CFile::open(const char *filepath, const char *mode)
{
    close();

    //_mode = mode;

    wchar_t* wfname = utf8ToWchar(filepath);
    wchar_t* wmode = utf8ToWchar(mode);

    _fp = _wfopen(wfname, wmode);

    free(wfname);
    free(wmode);

    return (_fp != nullptr);
}

bool CFile::read(const char *filepath)
{
    if (!open(filepath, "rb"))
        return false;

    fseek(_fp, 0, SEEK_END);
    unsigned long size = ftell(_fp);
    fseek(_fp, 0, SEEK_SET);

    _buffer.resize(size + 1);

    if (fread(_buffer.data(), 1, size, _fp) != size)
    {
        close();

        _buffer.clear();
        _curr = nullptr;

        return false;
    }

    close();

    _buffer.terminate(size);
    _curr = _buffer.data();

    return true;
}

bool CFile::write(const char *filepath, const CString &buffer)
{
    wchar_t* wbuff = utf8ToWchar(filepath);
    FILE *fp = _wfopen(wbuff, L"wb");
    free(wbuff);

    if (!fp)
        return false;

    const char *buff = buffer.c_str();
    size_t size = buffer.size();

    size_t ret = fwrite(buff, 1, size, fp);

    //print("size = %d", ret);

    if (ret != size)
    {
        fclose(fp);
        return false;
    }

    fflush(fp);
    fclose(fp);

    return true;
}

void CFile::write(const char *str)
{
    if (!_fp || !str)
        return;

    fwrite(str, strlen(str), 1, _fp);
}

void CFile::operator<<(const char *str)
{
    if (!_fp || !str)
        return;

    fwrite(str, strlen(str), 1, _fp);
}

bool CFile::getLinePtr(char **result, int *length)
{
    if (!_curr)
        return false;

    // start of line.
    char *first = _curr;

    // end of buffer ?
    if (*first == '\0')
        return false;

    // search end of line.
    char *p = first;

    while (1)
    {
        if (*p == '\r')
        {
            *result = first;
            *length = p - first;

            // skip.
            if (p[1] == '\n')
                ++p;

            // move to next line.
            _curr = ++p;

            return true;
        }
        else if (*p == '\n')
        {
            *result = first;
            *length = p - first;

            // move to next line.
            _curr = ++p;

            return true;
        }
        else if (*p == '\0')
        {
            *result = first;
            *length = p - first;

            // move to the end.
            _curr = p;

            return true;
        }

        ++p;
    }
}

bool CFile::getLine(CString &result)
{
    if (!_curr)
        return false;

    // start of line.
    char *first = _curr;

    // end of buffer ?
    if (*first == '\0')
        return false;

    // search end of line.
    char *p = first;

    while (1)
    {
        if (*p == '\r')
        {
            result.clear();
            result.append(first, p - first);

            // skip.
            if (p[1] == '\n')
                ++p;

            // move to next line.
            _curr = ++p;

            return true;
        }
        else if (*p == '\n')
        {
            result.clear();
            result.append(first, p - first);

            // move to next line.
            _curr = ++p;

            return true;
        }
        else if (*p == '\0')
        {
            result.clear();
            result.append(first, p - first);

            // move to the end.
            _curr = p;

            return true;
        }

        ++p;
    }
}


