#ifndef CSTRINGLIST_H
#define CSTRINGLIST_H

#include "CString.h"

class CStringList
{
public:

    CStringList();
    CStringList(const CStringList &list) = delete;
    CStringList& operator=(const CStringList &list) = delete;
    CStringList(CStringList &&list);
    CStringList& operator =(CStringList &&list);
    CStringList(int size);
    ~CStringList();

    // size.
    void clear();
    const int capacity() const;
    const int size() const;
    bool isEmpty() const;
    void resize(int size);

    // modify.
    void append(const char *str, int length = -1);
    void insert(int index, const char *str, int length = -1);
    void move(int from, int index);
    CString* takeAt(int index);
    CString* takeFirst();
    CString* takeLast();
    void removeAt(int index);
    void removeFirst();
    void removeLast();
    
    // read.
    const CString& at(int index) const;
    CString& operator[](int index) const;
    int find(const char *str, bool sensitive = true) const;

    // transform.
    CString join(const char *sep) const;
    
    void sort(int (*compare)(const void *, const void *));

private:

    CString **_data = nullptr;
    int _capacity = 0;
    int _size = 0;

};

#endif // CSTRINGLIST_H


