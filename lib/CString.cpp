#include "CString.h"
#include "CStringList.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include <assert.h>

#define CSTR_INITSIZE 16

// edit -----------------------------------------------------------------------

// https://stackoverflow.com/questions/4785381/replacement-for-ms-vscprintf-on-macos-linux

int _vscprintf (const char * format, va_list pargs)
{
    int retval;
    va_list argcopy;
    va_copy(argcopy, pargs);
    retval = vsnprintf(NULL, 0, format, argcopy);
    va_end(argcopy);
    return retval;
}

CString strFmt(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    int size = _vscprintf(fmt, va);

    CString result(size + 1);

    if (size > 0)
    {
        //resize(size + 1);
        size = vsnprintf(result.data(), size + 1, fmt, va);
        result.terminate(size);
    }

    va_end(va);

    return result;
}

CString strRepeat(const char *str, int count)
{
    if (!str || count < 1)
        return CString("");

    int len = strlen(str);

    CString result((len * count) + 1);

    while (count > 0)
    {
        result.append(str, len);
        --count;
    }

    return result;
}

CString enquote(const char *str)
{
    CString result;
    if (!str || !*str)
        return result;

    if (*str == '\'' || *str == '"')
    {
        result = str;
        return result;
    }

    result = strFmt("\"%s\"", str);
    return result;
}

CString unquote(const char *str)
{
    int len = strlen(str);

    CString result(len + 1);

    if (len > 1)
    {
        char first = str[0];
        if ((first == '\'' || first == '"')
            && str[len-1] == first)
        {
            result.append(str + 1, len - 2);
            return result;
        }
    }

    result.append(str, len);
    return result;
}

// convert --------------------------------------------------------------------

CString intToStr(int num)
{
    int length = snprintf(nullptr, 0, "%d", num);
    CString result(length + 1);
    snprintf(result.data(), length + 1, "%d", num);
    result.terminate(length);
    return result;
}

CString uint64ToStr(uint64_t num)
{
    int length = snprintf(nullptr, 0, "%" PRIu64, num);
    CString result(length + 1);
    snprintf(result.data(), length + 1, "%" PRIu64, num);
    result.terminate(length);
    return result;
}

// class ----------------------------------------------------------------------

CString::CString()
{
    _length = 0;
    _capacity = CSTR_INITSIZE;
    _buffer = (char*) malloc(_capacity * sizeof(char));
    _buffer[0] = '\0';
}

CString::CString(int capacity)
{
    _length = 0;
    _capacity = capacity > 0 ? capacity : CSTR_INITSIZE;
    _buffer = (char*) malloc(_capacity * sizeof(char));
    _buffer[0] = '\0';
}

CString::CString(const CString &str)
{
    _length = str.size();
    _capacity = _length + 1;
    _buffer = (char*) malloc(_capacity * sizeof(char));
    memcpy(_buffer, str.data(), _capacity);
}

CString::CString(const char *str, int length)
{
    if (length < 0)
        length = strlen(str);

    _length = length;
    _capacity = _length + 1;
    _buffer = (char*) malloc(_capacity * sizeof(char));

    if (_length > 0)
        memcpy(_buffer, str, _length);

    _buffer[_length] = '\0';
}

CString& CString::operator=(const CString &s)
{
    assert(_buffer);

    _length = 0;
    _buffer[0] = '\0';

    append(s.data(), s.size());

    return *this;
}

CString& CString::operator=(const char *s)
{
    assert(_buffer);

    _length = 0;
    _buffer[0] = '\0';

    append(s, strlen(s));

    return *this;
}

void CString::swap(CString &other)
{
    char *str = _buffer;
    int cap = _capacity;
    int len = _length;

    _buffer = other._buffer;
    _capacity = other._capacity;
    _length = other._length;

    other._buffer = str;
    other._capacity = cap;
    other._length = len;
}

CString::~CString()
{
    if (_buffer)
        free(_buffer);
}

// resize ---------------------------------------------------------------------

void CString::clear()
{
    _length = 0;
    _buffer[0] = '\0';
}

void CString::resize(int capacity)
{
    if (capacity < 1 || capacity <= _capacity)
        return;

    if (_capacity < 1)
    {
        _capacity = capacity;
    }
    else
    {
        while (_capacity < capacity)
            _capacity *= 2;
    }

    _buffer = (char*) realloc(_buffer, _capacity * sizeof(char));
}

void CString::terminate(int length)
{
    if (length == -1)
        length = strlen(_buffer);

    if (length < 0 || length + 1 > _capacity)
        return;

    _length = length;
    _buffer[_length] = '\0';
}

// tests ----------------------------------------------------------------------

bool CString::contains(const char *str, bool sensitive) const
{
    if (!str)
        return false;

    int len = strlen(str);

    const char *p = _buffer;

    while (*p)
    {
        if (sensitive)
        {
            if (strncmp(p, str, len) == 0)
                return true;
        }
        else
        {
            if (strncasecmp(p, str, len) == 0)
                return true;
        }

        ++p;
    }

    return false;
}

bool CString::startsWith(const char *str, bool sensitive) const
{
    int len = strlen(str);
    if (sensitive)
        return (strncmp(_buffer, str, len) == 0);
    else
        return (strncasecmp(_buffer, str, len) == 0);
}

bool CString::endsWith(const char *str, bool sensitive) const
{
    int len = strlen(str);
    if (len < 1 || len > _length)
        return false;

    const char *part = _buffer + _length - len;
    if (sensitive)
        return (strncmp(part, str, len) == 0);
    else
        return (strncasecmp(part, str, len) == 0);
}

int CString::compare(const char *str, bool sensitive) const
{
    assert(_buffer);

    if (!str)
        return -1;

    if (sensitive)
        return strcmp(_buffer, str);
    else
        return strcasecmp(_buffer, str);
}

bool CString::operator==(const char *str) const
{
    assert(_buffer);

    if (!str)
        return false;

    return (strcmp(_buffer, str) == 0);
}

bool CString::operator!=(const char *str) const
{
    assert(_buffer);

    if (!str)
        return false;

    return (strcmp(_buffer, str) != 0);
}

// append ---------------------------------------------------------------------

void CString::append(const char *str, int length)
{
    if (!str || !length)
        return;

    if (length < 0)
    {
        if ((length = strlen(str)) == 0)
            return;
    }

    if (_length + length + 1 > _capacity)
        resize(_length + length + 1);

    memcpy(_buffer + _length, str, length);

    _length += length;
    _buffer[_length] = '\0';
}

void CString::append(char c)
{
    append(&c, 1);
}

void CString::operator+=(const char *s)
{
    append(s, strlen(s));
}

// edit -----------------------------------------------------------------------

void CString::replace(const char *before, const char *after, bool sensitive)
{
    int blen = strlen(before);
    int alen = strlen(after);

    if (blen < 1 /*|| alen < 1*/)
        return;

    CString result(_length + 1);
    const char *p = _buffer;

    bool found = false;

    while (*p)
    {
        if (sensitive)
        {
            found = (strncmp(p, before, blen) == 0);
        }
        else
        {
            found = (strncasecmp(p, before, blen) == 0);
        }

        if (found)
        {
            if (alen > 0)
                result.append(after, alen);

            p += blen;
        }
        else
        {
            result.append(*p);

            ++p;
        }
    }

    free(_buffer);

    _buffer = result._buffer;
    _length = result._length;
    _capacity = result._capacity;

    result._buffer = nullptr;
}

void CString::chop(int n)
{
    if (n < 1)
        return;

    int len = _length - n;

    if (len < 0)
        len = 0;

    terminate(len);
}

CString CString::trimmed() const
{
    char *src = _buffer;
    bool start = true;
    int skip = 0;
    int total = 0;

    CString result(_length + 1);

    while (*src)
    {
        unsigned char c = *src;

        if (isspace(c))
        {
            if (start)
            {
                ++skip;
                ++src;
                continue;
            }
        }
        else
        {
            start = false;
            total = src + 1 - _buffer;
        }

        ++src;
    }

    result.append(_buffer + skip, total - skip);

    return result;
}

CStringList CString::split(const char *sep, bool keepEmptyParts,
                           bool sensitive) const
{
    CStringList list;

    int slen = strlen(sep);

    const char *start = _buffer;
    const char *c = start;
    int len = 0;

    while (1)
    {
        if (*c == '\0')
        {
            len = c - start;
            if (len || keepEmptyParts)
                list.append(start, len);

            break;
        }

        if (sensitive)
        {
            if (strncmp(c, sep, slen) == 0)
            {
                len = c - start;
                if (len > 0 || keepEmptyParts)
                    list.append(start, len);
                c += slen;
                start = c;

                continue;
            }
        }
        else
        {
            if (strncasecmp(c, sep, slen) == 0)
            {
                len = c - start;
                if (len > 0 || keepEmptyParts)
                    list.append(start, len);
                c += slen;
                start = c;

                continue;
            }
        }

        ++c;
    }

    return list;
}

void CString::remove(int position, int n)
{
    if (position < 0 || position >= _length || n < 1)
        return;

    int endpos = position + n;
    if (endpos >= _length)
    {
        terminate(position);
        return;
    }

    char *src = _buffer + endpos;
    char *dest = _buffer + position;
    int num = _length - endpos;

    memmove(dest, src, num);
    terminate(_length - n);

    return;
}

// convert --------------------------------------------------------------------

int CString::toInt() const
{
    return atoi(_buffer);
}

void CString::toLower()
{
    for (int i = 0; i < _length; ++i)
        _buffer[i] = tolower(_buffer[i]);
}

void CString::toUpper()
{
    for (int i = 0; i < _length; ++i)
        _buffer[i] = toupper(_buffer[i]);
}

// read -----------------------------------------------------------------------

char CString::operator[](int index) const
{
    if (index < 0 || index >= _length)
        return 0;

    return _buffer[index];
}

CString CString::left(int length) const
{
    if (length < 0)
        length = 0;
    else if (length > _length)
        length = _length;

    return CString(_buffer, length);
}

CString CString::mid(int index, int length) const
{
    if (index < 0 || index > _length)
        index = _length;

    if (length < 0)
        length = _length - index;

    CString result(length + 1);

    if ((index + length) > _length)
        length = -1;

    result.append(_buffer + index, length);

    return result;
}

char CString::first()
{
    if (_length < 1)
        return '\0';

    return _buffer[0];
}

char CString::last()
{
    if (_length < 1)
        return '\0';

    return _buffer[_length - 1];
}


