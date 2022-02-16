#ifndef dynamicalSearch
#define dynamicalSearch

#include <iostream>

template <typename K, typename V>
struct searchSet {
    K key;
    V value;
    searchSet(const K& x, const V& y) : key(x), value(y) {}
};

template <typename K, typename V>
class dynamicalSearchTable {
    typedef const struct searchSet<K, V> SET;

public:
    virtual SET* find(const K&) const = 0;
    virtual void insert(const SET&) = 0;
    void insert(K x, V y) { insert(SET(x, y)); }
    virtual void remove(const K&) = 0;
    virtual ~dynamicalSearchTable() {}
};

#endif