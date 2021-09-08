#include "CList.h"
#include <stdlib.h>
#include <string.h>

#define CSTRLIST_INITSIZE 16

// construct

CList::CList()
{
    _capacity = CSTRLIST_INITSIZE;
    _data = (void**) malloc(_capacity * sizeof(void*));
}

CList::CList(int size)
{
    _capacity = size;
    _data = (void**) malloc(_capacity * sizeof(void*));
}

CList::~CList()
{
    clear();

    if (_data)
        free(_data);
}

// size

void CList::setDeleteFunc(CDeleteFunc deleteFunc)
{
    _deleteFunc = deleteFunc;
}

void CList::clear()
{
    if (_data && _deleteFunc)
    {
        for (int i = 0; i < _size; ++i)
            _deleteFunc(_data[i]);
    }

    _size = 0;
}

void CList::resize(int capacity)
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

    _data = (void**) realloc(_data, _capacity * sizeof(void*));
}

int CList::capacity() const
{
    return _capacity;
}

int CList::size() const
{
    return _size;
}

bool CList::isEmpty() const
{
    return (_size < 1);
}

// read

void* CList::operator[](int index)
{
    if (!_data || index < 0 || index >= _size)
        return nullptr;

    return _data[index];
}

const void* CList::at(int index)
{
    if (!_data || index < 0 || index >= _size)
        return nullptr;

    return _data[index];
}

void* CList::first()
{
    return (void*) at(0);
}

void* CList::last()
{
    return (void*) at(_size - 1);
}

int CList::find(void *ptr)
{
    //int lsize = size();

    for (int i = 0; i < _size; ++i)
    {
        if (ptr == at(i))
            return i;
    }

    return -1;
}

// modify

void CList::append(void *ptr)
{
    resize(_size+1);

    _data[_size++] = ptr;
}

void CList::insert(int index, void *ptr)
{
    if (!_data || index < 0)
        return;

    if (index >= _size)
    {
        append(ptr);
        return;
    }

    resize(_size + 1);

    memmove(_data + index + 1, _data + index,
            (_size - index) * sizeof (void*));

    _data[index] = ptr;

    ++_size;
}

void CList::swap(CList &other)
{
    void **data = _data;
    int capacity = _capacity;
    int size = _size;
    CDeleteFunc deleteFunc = _deleteFunc;

    _data = other._data;
    _capacity = other._capacity;
    _size = other._size;
    _deleteFunc = other._deleteFunc;

    other._data = data;
    other._capacity = capacity;
    other._size = size;
    other._deleteFunc = deleteFunc;
}

void CList::removeAt(int index)
{
    if (!_data || _size < 1 || index < 0 || index >= _size)
        return;

    void *ptr = _data[index];

    if (_deleteFunc)
        _deleteFunc(ptr);

    --_size;

    int num = _size - index;

    if (num > 0)
    {
        memmove(_data + index, _data + index + 1,
                num * sizeof (void*));
   }
}

void CList::removeFirst()
{
    removeAt(0);
}

void CList::removeLast()
{
    removeAt(_size - 1);
}

void* CList::takeAt(int index)
{
    if (!_data || _size < 1 || index < 0 || index >= _size)
        return nullptr;

    void *ptr = _data[index];

    --_size;

    int num = _size - index;

    if (num > 0)
    {
        memmove(_data + index, _data + index + 1,
                num * sizeof (void*));
    }

    return ptr;
}

void* CList::takeFirst()
{
    return takeAt(0);
}

void* CList::takeLast()
{
    return takeAt(_size - 1);
}

// sort

void CList::sort(int (*compare)(const void *, const void *))
{
    qsort(_data, size(), sizeof(void*), compare);
}


