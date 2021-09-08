#include "CStringList.h"
#include <stdlib.h>
#include <string.h>

#define CSTRLIST_INITSIZE 16

CString g_default = "";

// construct

CStringList::CStringList()
{
    _capacity = CSTRLIST_INITSIZE;
    _data = (CString**) malloc(_capacity * sizeof(void*));
}

// move constructor
CStringList::CStringList(CStringList &&list)
{
    _capacity = list._capacity;
    _size = list._size;
    _data = list._data;

    list._capacity = 0;
    list._size = 0;
    list._data = nullptr;
}

// move assignment
CStringList& CStringList::operator=(CStringList &&list)
{
    if (&list == this)
        return *this;

    clear();

    if (_data)
        free(_data);

    _capacity = list._capacity;
    _size = list._size;
    _data = list._data;

    list._capacity = 0;
    list._size = 0;
    list._data = nullptr;

    return *this;
}

CStringList::CStringList(int size)
{
    _capacity = size;
    _data = (CString**) malloc(_capacity * sizeof(void*));
}

CStringList::~CStringList()
{
    clear();

    if (_data)
        free(_data);
}

// size.

void CStringList::clear()
{
    if (_data)
    {
        for (int i = 0; i < _size; ++i)
            delete _data[i];
    }

    _size = 0;
}

int CStringList::capacity() const
{
    return _capacity;
}

int CStringList::size() const
{
    return _size;
}

bool CStringList::isEmpty() const
{
    return (_size < 1);
}

void CStringList::resize(int capacity)
{
    if (capacity < 1 || capacity <= _capacity)
        return;

    if (_capacity < 1)
    {
        _capacity = capacity;
    }
    else
    {
        //while (_capacity <= capacity)
        //    _capacity *= 2;

        while (_capacity < capacity)
            _capacity *= 2;
    }

    _data = (CString**) realloc(_data, _capacity * sizeof(void*));
}

// modify.

void CStringList::append(const char *str, int length)
{
    if (!str)
        return;

    resize(_size + 1);

    _data[_size++] = new CString(str, length);
}

void CStringList::insert(int index, const char *str, int length)
{
    if (!_data || _size < 1 || index < 0 || index >= _size)
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

void CStringList::move(int from, int index)
{
    if (!_data || _size < 2)
        return;

    if (index < 0)
        index = 0;

    CString *str = (CString*) takeAt(from);
    if (!str)
        return;

    if (index >= _size)
    {
        // append.
        resize(_size + 1);
        _data[_size++] = str;

        return;
    }

    resize(_size + 1);

    memmove(_data + index + 1, _data + index,
            (_size - index) * sizeof(CString*));

    _data[index] = str;

    ++_size;
}

CString* CStringList::takeAt(int index)
{
    if (!_data || _size < 1 || index < 0 || index >= _size)
        return nullptr;

    CString *ptr = _data[index];

    --_size;

    int num = _size - index;

    if (num > 0)
    {
        memmove(_data + index, _data + index + 1,
                num * sizeof(void*));
    }

    return ptr;
}

CString* CStringList::takeFirst()
{
    return takeAt(0);
}

CString* CStringList::takeLast()
{
    return takeAt(_size - 1);
}

void CStringList::removeAt(int index)
{
    if (!_data || _size < 1 || index < 0 || index >= _size)
        return;

    CString *str = _data[index];
    if (str)
        delete str;

    --_size;

    int num = _size - index;

    if (num > 0)
    {
        memmove(_data + index, _data + index + 1,
                num * sizeof(void*));
    }
}

void CStringList::removeFirst()
{
    removeAt(0);
}

void CStringList::removeLast()
{
    removeAt(_size - 1);
}

// read.

const CString& CStringList::at(int index) const
{
    if (!_data || index < 0 || index >= _size)
        return g_default;

    return *_data[index];
}

CString& CStringList::operator[](int index) const
{
    if (!_data || index < 0 || index >= _size)
        return g_default;

    return *_data[index];
}

int CStringList::find(const char *str, bool sensitive) const
{
    for (int i = 0; i < _size; ++i)
    {
        CString *current = _data[i];

        if (current->compare(str, sensitive) == 0)
            return i;
    }

    return -1;
}

// transform.

CString CStringList::join(const char *sep) const
{
    CString result;

    //int nsize = size();

    if (_size < 1)
        return result;

    int len = strlen(sep);

    for (int i = 0; i < _size; ++i)
    {
        if (i > 0)
            result.append(sep, len);

        result.append(_data[i]->c_str());
    }

    return result;
}

// sort

void CStringList::sort(int (*compare)(const void *, const void *))
{
    qsort(_data, size(), sizeof(void*), compare);
}


