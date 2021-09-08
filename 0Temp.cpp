#if 0

void CStringList::append(const CString &str)
{
    resize(_size+1);

    _data[_size++] = new CString(str);
}

void CStringList::insert(int index, const CString &str)
{
    int length = str.size();

    if (!_data || _size < 1 || index < 0 || index >= length)
    {
        append(str, length);
        return;
    }

    resize(_size + 1);

    memmove(_data + index + 1, _data + index,
            (_size - index) * sizeof(CString*));

    _data[index] = new CString(str, length);

    ++_size;
}

bool fileRead(const char *fileName, CStringList &result,
              bool keepBlank = true);

bool fileRead(const char *fileName, CStringList &list, bool keepBlank)
{
    CString buffer;

    if (!fileRead(fileName, buffer))
        return false;

    list.clear();

    char *ptr = buffer.data();
    char *result = nullptr;
    int length = 0;

    while (getLine(&ptr, &result, &length))
    {
        if (!keepBlank && length == 0)
            continue;

        list.append(result, length);
    }

    return true;
}

bool getLine(char **start, char **result, int *length)
{
    // start of line.
    char *first = *start;

    // end of buffer ?
    if (*first == '\0')
        return false;

    // set result.
    *result = first;

    // search end of line.
    char *p = first;

    while (true)
    {
        if (*p == '\r')
        {
            // eol.
            if (length)
                *length = p - first;

            *p = '\0';

            // skip.
            if (*(p + 1) == '\n')
                ++p;

            // move to next line.
            *start = ++p;

            return true;
        }
        else if (*p == '\n')
        {
            // eol.
            if (length)
                *length = p - first;

            *p = '\0';

            // move to next line.
            *start = ++p;

            return true;
        }
        else if (*p == '\0')
        {
            // end of buffer.
            if (length)
                *length = p - first;

            // move to the end.
            *start = p;

            return true;
        }

        ++p;
    }
}

typedef bool (*LineProcessFunc) (const char *line, int length,
                                 CString &result);

bool fileEdit(LineProcessFunc func,
              const char *inpath, const char *outpath = nullptr);

bool fileEdit(LineProcessFunc func, const char *inpath, const char *outpath)
{
    if (!func || !inpath)
        return false;

    if (!outpath)
        outpath = inpath;

    CString buffer;

    if (!fileRead(inpath, buffer))
        return false;

    char *p = buffer.data();
    char *line = nullptr;
    int length = 0;

    CFile outfile;
    if (!outfile.open(outpath, "wb"))
        return false;

    CString result;

    while (getLine(&p, &line, &length))
    {
        result.clear();

        if (func(line, length, result))
        {
            outfile << result;
            outfile << "\n";
        }
    }

    return true;
}

#endif


