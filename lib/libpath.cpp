#include "libpath.h"

#include "libstr.h"
#include <string.h>

// Path separator.
bool pathIsSep(char c)
{
#ifdef _WIN32
    return c == '/' || c == '\\';
#else
    return c == '/';
#endif
}

const char* pathLastSep(const char *str, int len)
{
    if (!str)
        return nullptr;

    if (len < 0)
        len = strlen(str);

    if (len < 1)
        return nullptr;

    const char *last = str + len - 1;

    while (last > str)
    {
        if (pathIsSep(*last))
            return last;

        --last;
    }

    return nullptr;
}

// File names extensions.
const char* pathExt(const char *str)
{
    if (!str)
        return nullptr;

    const char *dot = nullptr;
    while (*str)
    {
        if (pathIsSep(*str))
        {
            dot = nullptr;
        }
        else if (*str == '.' /*&& !dot*/)
        {
            dot = str;
        }

        ++str;
    }

    return dot;
}

CString pathDirName(const char *path)
{
    int length = 0;
    const char *last = pathLastSep(path);

    if (last)
        length = last - path;

    return CString(path, length);
}

CString pathBaseName(const char *path)
{
    CString result(64);

    if (!path || !*path)
        return result;

    const char *p = path;

    while (1)
    {
        if (*p == '/')
        {
            path = ++p;
            continue;
        }
        else if (*p == '\0')
        {
            int length = p - path;
            result.append(path, length);

            return result;
        }

        ++p;
    }
}

int _strdirlen(const char *str)
{
    if (!str)
        return 0;

    const char *end = nullptr;
    const char *c = str;

    while (*c)
    {
        if (!pathIsSep(*c))
            end = c;

        ++c;
    }

    if (!end)
        return 0;

    return end + 1 - str;
}

const char* _strskipsep(const char *str)
{
    if (!str)
        return nullptr;

    const char *c = str;

    while (*c)
    {
        if (!pathIsSep(*c))
            return c;

        ++c;
    }

    return nullptr;
}

char _strgetsep(const char *str)
{
    char sep = PATHSEP;

    if (!str)
        return sep;

    while (*str)
    {
        if (pathIsSep(*str))
            return *str;

        ++str;
    }

    return sep;
}

CString pathJoin(const char *dir, const char *file)
{
    CString result(100);

    int dirlen = _strdirlen(dir);

    if (!dirlen)
    {
        result = file;
        return result;
    }

    const char *fstart = _strskipsep(file);
    int filelen = 0;

    if (fstart)
        filelen = strlen(fstart);

    char sep = _strgetsep(dir);

    int length = dirlen + 1 + filelen;

    result.resize(length + 1);
    result.append(dir, dirlen);

    if (fstart && filelen > 0)
    {
        result.append(sep);
        result.append(fstart);
    }

    return result;
}

int _count(const char *str)
{
    int ret = 0;

    while (*str)
    {
        if (pathIsSep(*str))
            ++ret;

        ++str;
    }

    return ret;
}

int pathCmp(const char *s1, const char *s2)
{
    int n1 = _count(s1);
    int n2 = _count(s2);

    if (n1 != n2)
        return n2 - n1;

    return strcasecmp(s1, s2);
}

bool pathCanonicalize(char *path, int *len)
{
    if (*len == 0)
        return false;

    const int maxParts = 60;
    char *parts[maxParts];
    int count = 0;

    char *start = path;
    char *dst = start;
    const char *src = start;
    const char *end = start + *len;

    if (pathIsSep(*src))
    {
#ifdef _WIN32

        // network path starts with //
        if (*len > 1 && pathIsSep(*(src + 1)))
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
            if (src + 1 == end || pathIsSep(src[1]))
            {
                // '.' component; eliminate.
                src += 2;
                continue;
            }
            else if (src[1] == '.' && (src + 2 == end || pathIsSep(src[2])))
            {
                // '..' component.  Back up if possible.
                if (count > 0)
                {
                    dst = parts[count - 1];
                    src += 3;
                    --count;
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

        if (pathIsSep(*src))
        {
            src++;
            continue;
        }

        if (count == maxParts)
            return false;

        parts[count] = dst;
        ++count;

        while (src != end && !pathIsSep(*src))
            *dst++ = *src++;

        *dst++ = *src++;  // Copy '/' or final \0 character as well.
    }

    if (dst == start)
    {
        *dst++ = '.';
        *dst++ = '\0';
    }

    *len = dst - start - 1;

    return true;
}


