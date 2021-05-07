#ifndef CSTRING_H
#define CSTRING_H

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include <stdlib.h>

class CString;
class CStringList;

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(0[arr]))

#define MIN(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

#define MAX(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

inline char* stralloc(int size)
{
    return (char*) malloc(size * sizeof(char));
}

inline wchar_t* wcsalloc(int size)
{
    return (wchar_t*) malloc(size * sizeof(wchar_t));
}

// edit
CString strFmt(const char *fmt, ...);
CString strRepeat(const char *str, int count);
CString enquote(const char *str);
CString unquote(const char *str);

// convert
CString intToStr(int num);
CString uint64ToStr(uint64_t num);

class CString
{
public:

    CString();
    CString(int capacity);
    CString(const CString &str);
    CString(const char *str, int length = -1);
    CString& operator=(const CString &s);
    CString& operator=(const char *s);
    void swap(CString &other);
    ~CString();

    // resize
    void clear();
    void resize(int capacity);
    void terminate(int length = -1);

    // tests
    bool isEmpty() const {return (_length == 0);}
    bool contains(const char *str, bool sensitive = true) const;
    bool startsWith(const char *str, bool sensitive = true) const;
    bool endsWith(const char *str, bool sensitive = true) const;
    int compare(const char *str, bool sensitive = true) const;
    bool operator==(const char *str) const;
    bool operator!=(const char *str) const;

    // append
    void append(const char *str, int length = -1);
    void append(char c);
    void operator+=(const char *s);

    // edit
    void replace(const char *before, const char *after, bool sensitive = true);
    void chop(int n);
    CString trimmed() const;
    CStringList	split(const char *sep, bool keepEmptyParts = true,
                      bool sensitive = true) const;
    void remove(int position, int n);

    // convert
    int	toInt() const;
    void toLower();
    void toUpper();

    // read
    CString left(int length) const;
    CString mid(int index, int length = -1) const;
    char first();
    char last();
    char operator[](int index) const;
    operator const char*() const {return _buffer;}
    const char* c_str() const {return _buffer;}
    char* data() const {return _buffer;}
    const int size() const {return _length;}
    const int capacity() const {return _capacity;}

private:

    char *_buffer = nullptr;
    int _capacity = 0;
    int _length = 0;

};

#endif // CSTRING_H


