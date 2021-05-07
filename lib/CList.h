#ifndef CLIST_H
#define CLIST_H

#include "deletefunc.h"

class CList
{
public:

    CList();
    CList(int size);
    ~CList();

    // clear / size
    void setDeleteFunc(CDeleteFunc deleteFunc);
    void clear();
    void resize(int size);
    const int capacity() const;
    const int size() const;
    bool isEmpty() const;

    // read / find
    void* operator[](int index);
    const void* at(int index);
    void* first();
    void* last();
    int find(void *ptr);

    // modify
    void append(void *ptr);
    void insert(int index, void *ptr);
    void swap(CList &other);
    void removeAt(int index);
    void removeFirst();
    void removeLast();
    void* takeAt(int index);
    void* takeFirst();
    void* takeLast();

    // sort
    void sort(int (*compare)(const void *, const void *));

private:

    void** _data = nullptr;
    int _capacity = 0;
    int _size = 0;

    CDeleteFunc _deleteFunc = nullptr;

};

#endif // CLIST_H


