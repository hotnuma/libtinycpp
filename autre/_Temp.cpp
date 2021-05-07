CString ...
operator bool() const {return (_length > 0);}
bool operator!() const {return (_length == 0);}

int CString::indexOf(const char *str, int from, bool sensitive) const
{
    if (!str || from < 0 || from >= _length)
        return -1;

    int len = strlen(str);

    const char *p = _buffer + from;

    while (*p)
    {
        if (sensitive)
        {
            if (strncmp(p, str, len) == 0)
                return p - _buffer;
        }
        else
        {
            if (strnicmp(p, str, len) == 0)
                return p - _buffer;
        }

        ++p;
    }

    return -1;
}

int CString::lastIndexOf(const char *str, int from, bool sensitive) const
{
    if (from == -1)
        from = _length - 1;

    if (!str || from < 0 || from >= _length)
        return -1;

    int len = strlen(str);

    const char *p = _buffer + from;

    while (p >= _buffer)
    {
        if (sensitive)
        {
            if (strncmp(p, str, len) == 0)
                return p - _buffer;
        }
        else
        {
            if (strnicmp(p, str, len) == 0)
                return p - _buffer;
        }

        --p;
    }

    return -1;
}

CString& CString::operator+=(const CString& s)
{
    append(s.data(), s.size());

    return *this;
}

int CString::compare(const CString &str, bool sensitive) const
{
    if (!_buffer || str.size() < 1)
        return -1;

    if (sensitive)
        return strcmp(_buffer, str.c_str());
    else
        return stricmp(_buffer, str.c_str());
}
CString CString::toLower() const
{
    CString result(_length + 1);

    for (int i = 0; i < _length; ++i)
    {
        char c = tolower(_buffer[i]);
        result.append(c);
    }

    result.terminate(_length);

    return result;
}

CString CString::toUpper() const
{
    CString result(_length + 1);

    for (int i = 0; i < _length; ++i)
    {
        char c = toupper(_buffer[i]);
        result.append(c);
    }

    result.terminate(_length);

    return result;
}

print("%" PRIu64, file.mtime());


BOOL DirectoryExists(LPCTSTR szPath)
{
  DWORD dwAttrib = GetFileAttributes(szPath);

  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
         (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

#include <io.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <tchar.h>

BOOL directory_exists( LPCTSTR absolutePath )
{
  if( _taccess_s( absolutePath, 0 ) == 0 )
  {
    struct _stat status;
    _tstat( absolutePath, &status );
    return (status.st_mode & S_IFDIR) != 0;
  }

  return FALSE;
}

tap = dependency('tap')
utests_src = files(
    'tests/test1_cstring.cpp',
    'utests.cpp',
)
utests = executable(
    'utests',
    sources : utests_src,
    gui_app : false,
    include_directories : ['lib', 'tests'],
    dependencies : tap,
    cpp_args : cpp_args,
    link_args : link_args,
    link_with : [stdmin, tinycpp],
)
test('utests', utests)

// contains is useless
bool CStringList::contains(const CString &str, bool sensitive) const
{
    for (int i = 0; i < _size; ++i)
    {
        CString *current = _data[i];
        if (current->compare(str, sensitive) == 0)
            return true;
    }

    return false;
}

// join bug : remove copy constructor
CStringList::CStringList(const CStringList &list)
{
    int size = list.size();
    _capacity = (size > 0 ? size : 1);
    _data = (CString**) malloc(_capacity * sizeof(void*));

    for (int i = 0; i < size; ++i)
    {
        const CString &str = list.at(i);
        append(str.c_str());
    }
}

// join bug : try to return to &list
void CString::split_try(CStringList &list, const char *sep, bool keepEmptyParts, bool sensitive) const
{
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
            if (strnicmp(c, sep, slen) == 0)
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
}

CString getLinkTarget(const char *filepath)
{
    CString result;

    if (!filepath || !*filepath)
        return result;

    wchar_t *wfilepath = utf8ToWchar(filepath);
    wchar_t *wpath = getLinkTargetW(wfilepath);

    result = wcharToCString(wpath);

    if (wfilepath)
        free(wfilepath);

    if (wpath)
        free(wpath);

    return result;
}

wchar_t* getLinkTargetW(const wchar_t *filepath)
{
    if (!filepath)
        return nullptr;

    // Open file for querying only (no read/write access).
    HANDLE hFile = ::CreateFileW(filepath,
                                 0,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                 nullptr,
                                 OPEN_EXISTING,
                                 FILE_ATTRIBUTE_NORMAL,
                                 nullptr);

    if (hFile == INVALID_HANDLE_VALUE)
        return nullptr;

    int len = ::GetFinalPathNameByHandleW(hFile,
                                          nullptr,
                                          0,
                                          FILE_NAME_NORMALIZED);
    if (len < 1)
    {
        ::CloseHandle(hFile);
        return nullptr;
    }

    wchar_t *result = (wchar_t*) malloc((len + 1) * sizeof(wchar_t));

    ::GetFinalPathNameByHandleW(hFile,
                                result,
                                len,
                                FILE_NAME_NORMALIZED);
    ::CloseHandle(hFile);

    return result;
}

inline bool isHeap(void *ptr)
{
    int dummy;
    return ptr > &dummy;
}

// https://stackoverflow.com/questions/36543301/detecting-windows-10-version
// https://stackoverflow.com/questions/54472278/problem-getting-full-version-number-for-windows-10-with-getfileversioninfo-and-v

typedef LONG NTSTATUS, *PNTSTATUS;
#define STATUS_SUCCESS (0x00000000)

typedef NTSTATUS (WINAPI* RtlGetVersionPtr)(PRTL_OSVERSIONINFOW);

RTL_OSVERSIONINFOW getOSVersion()
{
    HMODULE hMod = ::GetModuleHandleW(L"ntdll.dll");
    if (hMod)
    {
        RtlGetVersionPtr fxPtr = (RtlGetVersionPtr)::GetProcAddress(hMod, "RtlGetVersion");
        if (fxPtr != nullptr)
        {
            RTL_OSVERSIONINFOW rovi = {0};
            rovi.dwOSVersionInfoSize = sizeof(rovi);

            if (STATUS_SUCCESS == fxPtr(&rovi))
            {
                return rovi;
            }
        }
    }

    RTL_OSVERSIONINFOW rovi = {0};

    return rovi;
}




int CString::indexOf(const char *str, int from, bool sensitive) const
{
    if (!str || from < 0 || from >= _length)
        return -1;

    int len = strlen(str);

    int last = _length - len + 1;

    for (int i = 0; i < last; ++i)
    {
        if (sensitive)
        {
            if (strncmp(_buffer + i, str, len) == 0)
                return i;
        }
        else
        {
            if (strnicmp(_buffer + i, str, len) == 0)
                return i;
        }
    }

    return -1;
}

int CString::indexOf(const char *str, int from, bool sensitive) const
{
    if (from < 0 || from >= _length)
        return -1;

    const char *found = nullptr;

    if (sensitive)
        found = strstr(_buffer + from, str);
    else
        found = stristr(_buffer + from, str);

    return found ? found - _buffer : -1;
}

// Text wrap to num chars.
char* strwarp(const char *str, int num)
{
    int len;
    if (!str || (len = strlen(str)) < 1)
        return nullptr;

    char *result = (char*) malloc((len + 1) * sizeof(char));
    char *out = result;

    const char *start = str;
    const char *p = start;

    const char *inspace = nullptr;
    char *outspace = nullptr;

    while (*p)
    {
        if (*p == ' ')
        {
            inspace = p;
            outspace = out;

            *out++ = *p++;

            while (*p == ' ')
                ++p;

            continue;
        }
        else if (p - start > num && inspace)
        {
            p = inspace;
            while (*p == ' ')
                ++p;
            start = p;

            out = outspace;

            *out++ = '\n';

            continue;
        }
        else if (*p == '\r')
        {
            ++p;
            continue;
        }
        else if (*p == '\n')
        {
            *out++ = *p++;
            start = p;

            continue;
        }

        *out++ = *p++;
    }

    *out = '\0';

    return result;
}

//============================================================================

// Text wrap to num chars.
CString strwrap(const char *str, int num)
{
    int len;
    if (!str || (len = strlen(str)) < 1)
        return CString("");

    CString result(len + 1);
    const char *start = str;
    const char *end = 0;

    while (*str)
    {
        if (isspace((unsigned char) *str))
        {
            int count = str - start;
            if (count > num)
            {
                if (end)
                {
                    print("count = %i, total = %i", count, end - start);
                    result.append(start, end - start);

                    start = end;
                    while (isspace((unsigned char) *start))
                        ++start;
                    end = 0;
                }
                else
                {
                    print("count = %i", count);
                    result.append(start, count);

                    start = str;
                    while (isspace((unsigned char) *start))
                        ++start;
                    end = 0;
                }

                result.append("\n");

                continue;
            }

            end = str;

            while (isspace((unsigned char) *str))
                ++str;

            continue;
        }

        ++str;
    }

    result.append(start, str - start);

    return result;
}

// Text wrap to num chars.
CString strwrap8(const char *str, int num)
{
    int len;
    if (!str || (len = strlen(str)) < 1)
        return CString("");

    CString result(len + 1);
    const char *start = str;
    int total = 0;
    int ucount = 0;

    while (*str)
    {
        if (isspace((unsigned char) *str))
        {
            int count = str - start;
            int temp = ucount;

            while (isspace((unsigned char) *str))
                _increment(&str, &ucount);

            if (temp > num)
            {
                if (total > 0)
                {
                    print("ucount = %i, total = %i", temp, total);
                    result.append(start, total);

                    start = start + total;
                    while (isspace((unsigned char) *start))
                        ++start;
                }
                else
                {
                    print("ucount = %i, count = %i", temp, count);
                    result.append(start, count);

                    start = str;
                }

                result.append("\n");

                total = 0;
                ucount = 0;
                continue;
            }

            total = count;
            continue;
        }

        _increment(&str, &ucount);
    }

    result.append(start, str - start);

    return result;
}

// Text wrap to num chars.
CString strwrap(const char *str, int num)
{
    int len;
    if (!str || (len = strlen(str)) < 1)
        return CString("");

    CString result(len + 1);
    const char *start = str;
    int total = 0;

    while (*str)
    {
        if (isspace((unsigned char) *str))
        {
            int count = str - start;

            while (isspace((unsigned char) *str))
                ++str;

            if (count > num)
            {
                if (total)
                {
                    print("count = %i, total = %i", count, total);
                    result.append(start, total);
                    start = start + total;
                    while (isspace((unsigned char) *start))
                        ++start;
                }
                else
                {
                    print("count = %i", count);
                    result.append(start, count);
                    start = str;
                }

                result.append("\n");

                total = 0;
                continue;
            }

            total = count;
            continue;
        }

        ++str;
    }

    result.append(start, str - start);

    return result;
}

// Text wrap to num chars.
CString strwrap(const char *str, int num)
{
    int len;
    if (!str || (len = strlen(str)) < 1)
        return CString("");

    CString result(len + 1);
    const char *start = str;
    int total = 0;

    while (*str)
    {
        if (isspace((unsigned char) *str))
        {
            int count = str - start;

            while (isspace((unsigned char) *str))
                ++str;

            if (count > num)
            {
                if (total)
                {
                    result.append(start, total);
                    start = start + total;
                    while (isspace((unsigned char) *start))
                        ++start;
                }
                else
                {
                    result.append(start, count);
                    start = str;
                }

                result.append("\n");

                total = 0;
                continue;
            }

            total = count;
            continue;
        }
        else if (*str == '\n')
        {
            ++str;
            result.append(start, str - start);
            start = str;
            total = 0;

            continue;
        }

        ++str;
    }

    result.append(start, str - start);

    return result;
}


// Text wrap to num chars.
CString strwrap(const char *str, int num)
{
    int len;
    if (!str || (len = strlen(str)) < 1)
        return CString("");

    CString result(len + 1);
    const char *start = str;
    int total = 0;

    while (*str)
    {
        if (*str == ' ')
        {
            int count = str - start;

            while (*str == ' ')
                ++str;

            if (count > num)
            {
                if (total)
                {
                    result.append(start, total);
                    start = start + total;
                    while (*start == ' ')
                        ++start;
                }
                else
                {
                    result.append(start, count);
                    start = str;
                }

                result.append("\n");

                total = 0;
                continue;
            }

            total = count;
            continue;
        }
        else if (*str == '\n')
        {
            ++str;
            result.append(start, str - start);
            start = str;
            total = 0;

            continue;
        }

        ++str;
    }

    result.append(start, str - start);

    return result;
}

void CString::trim()
{
    char *src = _buffer;
    char *dest = src;
    int skip = 0;
    int total = 0;

    while (*src)
    {
        unsigned char c = *src;

        if (isspace(c))
        {
            if (dest == _buffer)
            {
                ++skip;
                ++src;
                continue;
            }
        }
        else
        {
            total = src + 1 - _buffer;
        }

        *dest++ = *src++;
    }

    terminate(total - skip);

    return;
}

CString CString::trimmed() const
{
    const char *first = nullptr;
    const char *last = nullptr;
    const char *c = _buffer;

    while (*c)
    {
        if (!isspace(*c))
        {
            if (!first)
                first = c;

            last = c + 1;
        }

        ++c;
    }

    int len = last - first;

    if (!first || !last || len < 1)
    {
        first = _buffer;
        len = 0;
    }

    CString result(len + 1);
    result.append(first, len);

    return result;
}

void CString::wrap(int len)
{
    char *temp = strwarp(_buffer, len);
    if (!temp)
        return;

    if (_buffer)
        free(_buffer);

    _buffer = temp;
    _length = strlen(temp);
    _capacity = _length + 1;
}

void CString::format(const char *fmt, ...)
{
    va_list va;
    va_start(va, fmt);

    int size = _vscprintf(fmt, va);

    if (size > 0)
    {
        resize(size + 1);
        size = vsnprintf(_buffer, size + 1, fmt, va);
        terminate(size);
    }

    va_end(va);
}

bool pathCanonicalize(char *path, int *len)
{
    if (*len == 0)
        return false;

    const int maxParts = 60;
    char *parts[maxParts];
    int component_count = 0;

    char* start = path;
    char* dst = start;
    const char* src = start;
    const char* end = start + *len;

    if (isPathSep(*src))
    {
#ifdef _WIN32

        // network path starts with //
        if (*len > 1 && isPathSep(*(src + 1)))
        {
            src += 2;
            dst += 2;
        }
        else
        {
            ++src;
            ++dst;
        }
#else
        ++src;
        ++dst;
#endif
    }

    while (src < end)
    {
        if (*src == '.')
        {
            if (src + 1 == end || isPathSep(src[1]))
            {
                // '.' component; eliminate.
                src += 2;
                continue;
            }
            else if (src[1] == '.' && (src + 2 == end || isPathSep(src[2])))
            {
                // '..' component.  Back up if possible.
                if (component_count > 0)
                {
                    dst = parts[component_count - 1];
                    src += 3;
                    --component_count;
                }
                else
                {
                    *dst++ = *src++;
                    *dst++ = *src++;
                    *dst++ = *src++;
                }
                continue;
            }
        }

        if (isPathSep(*src))
        {
            src++;
            continue;
        }

        if (component_count == maxParts)
            return false;

        parts[component_count] = dst;
        ++component_count;

        while (src != end && !isPathSep(*src))
            *dst++ = *src++;

        *dst++ = *src++;  // Copy '/' or final \0 character as well.
    }

    if (dst == start)
    {
        *dst++ = '.';
        *dst++ = '\0';
    }

    *len = dst - start - 1;

    //#ifdef _WIN32
    //    uint64_t bits = 0;
    //    uint64_t bits_mask = 1;

    //    for (char* c = start; c < start + *len; ++c)
    //    {
    //        switch (*c)
    //        {
    //        case '\\':
    //            bits |= bits_mask;
    //            *c = '/';
    //            //NINJA_FALLTHROUGH;
    //        case '/':
    //            bits_mask <<= 1;
    //        }
    //    }

    //    *slash_bits = bits;
    //#else
    //    *slash_bits = 0;
    //#endif

    return true;
}

//===========================================================================
wchar_t* _ansiToWchar(const char *str)
{
    int wsize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
    wchar_t* wbuff = (wchar_t*) malloc(wsize * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, str, -1, wbuff, wsize);

    return wbuff;
}

CString ansiToCString(const char *str)
{
    wchar_t *wstr = _ansiToWchar(str);

    CString buff = wcharToCString(wstr);

    free(wstr);

    return buff;
}

//--------------------------------------------------------------
#include <stdio.h>
char* ansiToUtf8(const char *str)
{
    wchar_t *wstr = _ansiToWchar(str);

    int size = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char* buff = (char*) malloc(size * sizeof(char));
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, buff, size, NULL, NULL);

    free(wstr);

    return buff;
}

void CString::grow(int length)
{
    resize(_length + length + 1);
}

void CString::added(int length)
{
    if (_length + length + 1 > _capacity)
        return;

    _length += length;
    _buffer[_length] = '\0';
}

bool _readPipe2(void *handle, CString &outBuff)
{
    if (!handle)
        return false;

    DWORD avail;
    DWORD numRead;
    if (!PeekNamedPipe(handle, 0, 0, 0, &avail, 0))
    {
        print("peek error");
        return false;
    }

    if (avail)
    {
        print("peek = %i", avail);

        print("size = %i capacity = %i", outBuff.size(), outBuff.capacity());

        char *data = outBuff.data();
        int size = outBuff.size();
        outBuff.resize(size + avail + 1);
        print("size = %i capacity = %i", outBuff.size(), outBuff.capacity());

        if (!ReadFile(handle, data + size, avail+1, &numRead, 0))
        {
            print("read error");
            return false;
        }

        outBuff.added(avail);

        print("read = %i", numRead);
        print(outBuff);
    }

    return true;
}

//----------------------------------------------------------------------------
#define BUFSIZE 4096
bool _readPipe2(void *handle, CString &outBuff)
{
    if (!handle)
        return false;

    char _g_buffer[BUFSIZE];

    DWORD avail;
    DWORD numRead;
    if (!PeekNamedPipe(handle, 0, 0, 0, &avail, 0))
    {
        print("peek error");
        return false;
    }

    if (avail)
    {
        print("peek = %i", avail);

        if (!ReadFile(handle, _g_buffer, BUFSIZE, &numRead, 0))
        {
            print("read error");
            return false;
        }

        if (numRead)
            outBuff.append(_g_buffer, numRead);

        print("read = %i", numRead);
        print(outBuff);
    }

    return true;
}

//----------------------------------------------------------------------------
if (_capacity <= _size + 1)
{
    //int old_capacity = _capacity;
    _capacity *= 2;

    void *old_ptr = _data;
    _data = (void**) malloc(_capacity * sizeof(void*));
    int num = _size - index;
    if (num > 0)
        memcpy(_data, old_ptr, num * sizeof(void*));
    free(old_ptr);
}

//----------------------------------------------------------------------------

CString CString::operator+(const CString& s) const
{
    char *tmp = new char[capacity() + s.capacity() + 1];
    //assert(tmp);
    strcpy(tmp, _data);
    strcat(tmp, s._data);
    CString retval = tmp;
    delete[] tmp;
    return retval;
}

//----------------------------------------------------------------------------

size_t newlen = s.length();
if (newlen + 1 > _size)
{
    if (_buffer)
        free(_buffer);

    _size = newlen + 1;
    _buffer = (char*) malloc(_size * sizeof(char));
    _length = newlen;
}

strcpy(_buffer, s._buffer);

//----------------------------------------------------------------------------

size_t newlen = strlen(s);
if (newlen + 1 > _size)
{
    if (_buffer)
        free(_buffer);

    _size = newlen + 1;
    _buffer = (char*) malloc(_size * sizeof(char));
    _length = newlen;
}

strcpy(_buffer, s);

//----------------------------------------------------------------------------

#include <assert.h>
#include <ctype.h>

typedef const char* CSTR;

const int MXSTRING_LOCATENOTFOUND = -1;

    // type conversion
    operator CSTR() const;
    // duplication
    // user is responsible for deleting the returned pointer
    // just like ANSI C strdup() function
    char *strDup() const;
    // substring member functions/operators
    char& operator[](unsigned int index);
    // remember BASIC?
    CString left(unsigned int len) const; // return first len characters
    CString mid(unsigned int start, unsigned int len) const;
                               // return len characters from offset start
    CString right(unsigned int len) const; // return last len characters
    // substring/character functions return MXSTRING_LOCATENOTFOUND for
        // error. offset is 0 based
    virtual int locate(const CString&) const;
    virtual int locate(const char c) const;
    // comparison operators
    //      > and < are used for alphabetical sorting operators
    virtual bool operator>(const CString&) const;
    virtual bool operator>(CSTR) const;
    virtual bool operator>=(const CString&) const;
    virtual bool operator>=(CSTR) const;
    virtual bool operator<(const CString&) const;
    virtual bool operator<(CSTR) const;
    virtual bool operator<=(const CString&) const;
    virtual bool operator<=(CSTR) const;
    virtual bool operator==(const CString&) const;
    virtual bool operator==(CSTR) const;
    virtual bool operator!=(const CString&) const;
    virtual bool operator!=(CSTR) const;
    virtual int cmp(const CString&) const;
    // case conversion member functions
    virtual void toUpper();             // converts instance to uppercase
    virtual void toLower();             // converts instance to lowercase

    // check/toggle sensitivity setting for all MXStrings
    //static void sensitivity(bool b);
    //static bool sensitivity();
    // insertion; deletion members functions
    CString& insert(unsigned int start, CString&);
    CString& erase(unsigned int start, unsigned int len);
    // handy printf formatting-type function;
    CString& sprintf(CSTR fmt, ...);
    // returns length of zero terminated string
    // not length of allocated buffer

    // return TRUE if string is empty
    bool isEmpty() const;
    bool operator!() const;
    // fills string with single character
    void fill(unsigned int len, const char c = '\0');
//
    CString ncpy(unsigned int start, unsigned int len) const;

inline CString::operator CSTR() const
{
    return _data;
}
inline CString CString::left(unsigned int len) const
{
    return ncpy(0, len);
}
inline CString CString::mid(unsigned int start, unsigned int len) const
{
    return ncpy(start, len);
}
inline unsigned int CString::length() const
{
    return strlen(_data);
}
inline CString CString::right(unsigned int len) const
{
    return ncpy(length() - len, len);
}
inline bool CString::isEmpty() const
{
    return (*_data == '\0') ? true : false;
}
inline bool CString::operator !() const
{
    return isEmpty();
}
//inline void CString::sensitivity(bool b)
//{
//    sensitive = b;
//}
//inline bool CString::sensitivity()
//{
//    return sensitive;
//}

//class ostream;
//ostream& operator<<(ostream& s, CString& m);

//----------------------------------------------------------------------------

#ifdef  sunos
int stricmp(const char *s1, const char *s2)
{
    while(toupper(*s1++) == toupper(*s2++))
        if(*s1 == \0 && *s2 == \0)
            return 0;
    if(toupper(*s1) < toupper(*s2))
        return -1;
    else
        return 1;
}
#endif  // portable stricmp()

// As for all operators and functions that require possible reassigning to the
// *rep pointer, a test is first made to verify that the existing string
// buffer is larger than the incoming string. If so, make a straightforward
// copy. Buffer space is freed only if incoming string requires extra space.
char *CString::strDup() const
{
    char *tmp = new char[length() + 1];
    assert(tmp);
    strcpy(tmp, _data);
    return tmp;
}
CString CString::ncpy(unsigned int start, unsigned int len) const
{
    if(start > (length() - 1))
    {
        CString emptyString;
        return emptyString;
    }

    if(len > strlen(&_data[start]))
        len = strlen(&_data[start]);

    char *tmp = new char[len + 1];
    assert(tmp);
    strncpy(tmp, &_data[start], len);
    tmp[len] = '\0';
    CString retval = tmp;
    delete[] tmp;

    return retval;
}
char& CString::operator[](unsigned int index)
{
    // return \0 if the index value is out of bounds
    if(index < 0 || index > length())
        return _data[length()];
    return _data[index];
}
int CString::locate(const CString& s) const
{
    char *p;
    int off;
    if(_sensitive) {
        p = strstr(_data, s._data);
        off = p ? (int)(p - _data) : MXSTRING_LOCATENOTFOUND;
        }
    else    {
        CString src = *this;
        src.toUpper();
        CString tmp(s);
        tmp.toUpper();
        p = strstr(src._data, tmp._data);
        off = p ? (int)(p - src._data) : MXSTRING_LOCATENOTFOUND;
        }
    return off;
}
int CString::locate(const char c) const
{
    char *p;
    int off;
    if(_sensitive) {
        p = strchr(_data, c);
        off = p ? (int)(p - _data) : MXSTRING_LOCATENOTFOUND;
        }
    else    {
        CString src = *this;
        src.toUpper();
        char tmp = toupper(c);
        p = strchr(src._data, tmp);
        off = p ? (int)(p - src._data) : MXSTRING_LOCATENOTFOUND;
        }
    return off;
}
bool CString::operator>(const CString& s) const
{
    if(_sensitive)
        return strcmp(_data, s._data) > 0 ? true : false;
    else
        return stricmp(_data, s._data) > 0 ? true : false;
}
bool CString::operator>(CSTR s) const
{
    CString str = s;
    return (*this > str);
}
bool CString::operator>=(const CString& s) const
{
    return (s < *this);
}
bool CString::operator>=(CSTR s) const
{
    CString str = s;
    return (str < *this);
}
bool CString::operator<(const CString& s) const
{
    if(_sensitive)
        return strcmp(_data, s._data) < 0 ? true : false;
    else
        return stricmp(_data, s._data) < 0 ? true : false;
}
bool CString::operator<(CSTR s) const
{
    CString str = s;
    return (*this < str);
}
bool CString::operator<=(const CString& s) const
{
    return (s > *this);
}
bool CString::operator<=(CSTR s) const
{
    CString str = s;
    return (str > *this);
}
bool CString::operator==(const CString& s) const
{
    if(_sensitive)
        return strcmp(_data, s._data) == 0 ? true : false;
    else
        return stricmp(_data, s._data) == 0 ? true : false;
}
bool CString::operator==(CSTR s) const
{
    CString str = s;
    return (*this == str);
}
bool CString::operator!=(const CString& s) const
{
    return (*this == s) ? false : true;
}
bool CString::operator!=(CSTR s) const
{
    return (*this == s) ? false : true;
}
int CString::cmp(const CString& s) const
{
    if(_sensitive)
        return strcmp(_data, s._data);
    else
        return stricmp(_data, s._data);
}
void CString::toUpper()
{
    for(unsigned int i = 0; i < length(); i++)
        _data[i] = toupper(_data[i]);
}
void CString::toLower()
{
    for(unsigned int i = 0; i < length(); i++)
        _data[i] = tolower(_data[i]);
}
CString& CString::insert(unsigned int start, CString& s)
{
    if(start < (length() + 1))       {
        CString strStart = ncpy(0, start);
        CString strEnd = ncpy(start, length() - start);
        *this = strStart + s + strEnd;
        }
    return *this;
}
CString& CString::erase(unsigned int start, unsigned int len)
{
    if(start < (length() + 1) && len <= strlen(&_data[start]))       {
        CString strStart = ncpy(0, start);
        CString strEnd = ncpy(start + len, length() - (start + len));
        *this = strStart + strEnd;
        }
    return *this;
}
void CString::fill(unsigned int len, const char c)
{
    if(len > length())    {
        delete[] _data;
        _data = new char[len + 1];
        assert(_data);
        }
    memset(_data, c, len);
    *(_data + len) = '\0';
}
#include <stdio.h>
#include <stdarg.h>
CString& CString::sprintf(const char *fmt, ...)
{
    char *szBuf = new char[_capacity];
    assert(szBuf);
    va_list args;
    va_start(args, fmt);
    size_t val = ::vsprintf(szBuf, fmt, args);
    va_end(args);
    // if retval >= MAX_VARGS_BUFLEN then
    // we have written past the end of the buffer
    // memory is probably trashed; an exception should be thrown here
    assert(val < _capacity);
    *this = szBuf;
    delete[] szBuf;
    return *this;
}

//#include <iostream.h>
//ostream& operator<<(ostream& s, CString& m)
//{
//    s << (CSTR)m;
//    return s;
//}


