#include "libstr.h"

#include <ctype.h>
#include <string.h>

bool strGetPart(char **start, char **result, int *length)
{
    // start of line.
    char *first = *start;

    while(isspace(*first)) ++first;

    // end of buffer ?
    if (*first == '\0')
        return false;

    // search end of line.
    char *p = first;

    while (1)
    {
        if (isspace(*p))
        {
            *result = first;
            *length = p - first;

            // move to the end.
            *start = ++p;

            return true;
        }
        else if (*p == '\0')
        {
            *result = first;
            *length = p - first;

            // move to the end.
            *start = p;

            return true;
        }

        ++p;
    }
}

CString strBaseName(const char *path)
{
    CString result(64);

    if (!path)
        return result;

    const char *p = path;

    while (1)
    {
        if (*p == '/')
        {
            path = ++p;
            continue;
        }
        else if (*p == ' ' || *p == '\0')
        {
            int length = p - path;
            result.append(path, length);

            return result;
        }

        ++p;
    }
}

char* stristr(const char *haystack, const char *needle)
{
    char *pptr  = (char *) needle;   /* Pattern to search for    */
    char *start = (char *) haystack; /* Start with a bowl of hay */
    char *sptr;                      /* Substring pointer        */
    int   slen  = strlen (haystack); /* Total size of haystack   */
    int   plen  = strlen (needle);   /* Length of our needle     */

    /* while string length not shorter than pattern length */
    for (; slen >= plen; start++, slen--)
    {
        /* find start of pattern in string */
        while (toupper (*start) != toupper (*needle))
        {
            start++;
            slen--;

            /* if pattern longer than string */
            if (slen < plen)
            {
                return NULL;
            }
        }

        sptr = start;
        pptr = (char *) needle;
        while (toupper (*sptr) == toupper (*pptr))
        {
            sptr++;
            pptr++;

            /* if end of pattern then pattern was found */
            if ('\0' == *pptr)
            {
                return start;
            }
        }
    }

    return NULL;
}

/*
 * The strrstr() function finds the last occurrence of the substring needle
 * in the string haystack. The terminating nul characters are not compared.
 */
char* strrstr(const char *haystack, const char *needle)
{
    char *r = nullptr;

    if (!needle[0])
        return (char*)haystack + strlen(haystack);

    while (1)
    {
        char *p = (char*) strstr(haystack, needle);
        if (!p)
            return r;

        r = p;
        haystack = p + 1;
    }
}

// Detect eol.
int streol(const char *str, int *pos)
{
    if (!str)
        return STREOL_NONE;

    const char *p = str;
    while (*p)
    {
        if (*p == '\r')
        {
            if (*(p + 1) == '\n')
            {
                if (pos)
                    *pos = (p - str);

                return STREOL_CRLF;
            }
            else
            {
                if (pos)
                    *pos = (p - str);

                return STREOL_CR;
            }
        }
        else if (*p == '\n')
        {
            if (pos)
                *pos = (p - str);

            return STREOL_LF;
        }

        ++p;
    }

    if (pos)
        *pos = -1;

    return STREOL_NONE;
}

void _utf8inc(const char **str, int *count)
{
    if ((**str & 0xC0) != 0x80)
        ++*count;
    ++*str;
}

int utf8len(const char *str)
{
    int count = 0;

    while (*str)
    {
        if ((*str & 0xC0) != 0x80)
            ++count;
        ++str;
    }

    return count;
}

CString utf8wrap(const char *str, int num)
{
    CString buffer(100);

    int len = strlen(str);
    if (len < 1)
        return buffer;

    buffer = str;
    //if (buffer[len-1] != '\n')
    buffer.append('\n');

    CString result(len + 2);

    char *pp = buffer.data();

    while (*pp)
    {
        if (*pp == ' ')
        {
            char n = *(pp + 1);
            if (n == '?' || n == '!')
                *pp = 0x01;
        }
        ++pp;
    }

    const char *p = buffer.data();
    const char *start = p;
    const char *end = 0;
    int ucount = 0;

    while (*p)
    {
        if (isspace((unsigned char) *p))
        {
            if (ucount > num)
            {
                if (!end)
                    end = p;

                result.append(start, end - start);

                while (isspace((unsigned char) *end))
                    ++end;

                start = end;
                end = 0;
                ucount = 0;

                p = start;

                result.append("\n");

                continue;
            }

            end = p;

            while (isspace((unsigned char) *p))
                _utf8inc(&p, &ucount);

            continue;
        }

        _utf8inc(&p, &ucount);
    }

    result.append(start, p - start);

    pp = result.data();

    while (*pp)
    {
        if (*pp == 0x01)
            *pp = ' ';

        ++pp;
    }

    if (result.last() == '\n')
        result.chop(1);

    return result;
}


