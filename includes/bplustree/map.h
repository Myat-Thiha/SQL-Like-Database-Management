#ifndef MAP_H
#define MAP_H

#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <cassert>
#include "bplustree.h"
#include "btree_array_funcs.h"
template <typename K, typename V>
struct Pair{
    K key;
    V value;

    Pair(const K& k=K(), const V& v=V());
    friend ostream& operator <<(ostream& outs, const Pair<K, V>& print_me)
    {
        outs<<print_me.key<<" : "<<print_me.value;
        return outs;
    }
    friend bool operator ==(const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        if(lhs.key == rhs.key)
        {
            return true;
        }
        return false;
    }
    friend bool operator < (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        if(lhs.key < rhs.key)
            return true;
        return false;
    }
    friend bool operator > (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        if(lhs.key > rhs.key)
            return true;
        return false;
    }
    friend bool operator <= (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        if(lhs.key <= rhs.key)
            return true;
        return false;
    }
    friend Pair<K, V> operator + (const Pair<K, V>& lhs, const Pair<K, V>& rhs)
    {
        //lhs.key+=rhs.key;
        return rhs;
    }
};

template <typename K, typename V>
Pair<K,V>::Pair(const K& k, const V& v)
{
    key=k;
    value=v;
}

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator{
    public:
        friend class Map;
        Iterator(typename map_base::Iterator it=typename map_base::Iterator())
        {
            _it=it;
        }
        Iterator operator ++(int unused)
        {
            Iterator temp=_it;
            _it++;
            return temp;
        }
        Iterator operator ++()
        {
            ++_it;
            return *this;
        }
        Pair<K, V> operator *()
        {
            return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            if(lhs._it==rhs._it)
            {
                return true;
            }
            return false;
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            if(lhs._it!=rhs._it)
            {
                return true;
            }
            return false;
        }
    private:
        typename map_base::Iterator _it;

    };

    Map();
//  Iterators
    Iterator begin();
    Iterator end();

//  Capacity
    int size() const{return key_count;}
    bool empty() const{
        if(key_count==0)
        return true; 
        return false;
    }

//  Element Access
    V& operator[](const K& key);
    V& at(const K& key);
    const V& at(const K& key) const;


//  Modifiers
    void insert(const K& k, const V& v);
    void erase(const K& key);
    void clear();
    V get(const K& key);

//  Operations:
    Iterator find(const K& key);
    bool contains(const Pair<K, V>& target) const;

    //I have not writtent these yet, but we will need them:
    int count(const K& key);
    Iterator lower_bound(const K& key)
    {
        return Iterator(map.lower_bound(key));
    }
    Iterator upper_bound(const K& key)
    {
        return Iterator(map.upper_bound(key));
    }

    bool is_valid(){return map.is_valid();}

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }
private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

template <typename K, typename V>
Map<K,V>::Map()
{
    map=BPlusTree<Pair<K,V>>(true);
    key_count=0;
}

template <typename K, typename V>
typename::Map<K,V>::Iterator Map<K,V>::begin()
{
    return Iterator(map.begin());
}

template <typename K, typename V>
typename::Map<K,V>::Iterator Map<K,V>::end()
{
    return Iterator(map.end());
}

template <typename K, typename V>
V& Map<K,V>::operator[](const K& key)
{
    return at(key);
}

template <typename K, typename V>
V& Map<K,V>::at(const K& key)
{
    return map.get(key).value;
}

template <typename K, typename V>
const V& Map<K,V>::at(const K& key) const
{
    return map.get(key).value;
}

template <typename K, typename V>
void Map<K,V>::insert(const K& k, const V& v)
{
    Pair<K,V> pair(k,v);
    map.insert(pair);
    key_count++;
}

template <typename K, typename V>
void Map<K,V>::erase(const K& key)
{
    map.remove(key);
    key_count--;
}

template <typename K, typename V>
void Map<K,V>::clear()
{
    map.clear_tree();
    // map.key=K();
    // map.value=V();
}

template <typename K, typename V>
V Map<K,V>::get(const K& key)
{
    Pair<K,V> get=map.get(key);
    return get.value;
}

template <typename K, typename V>
typename::Map<K,V>::Iterator Map<K,V>::find(const K& key)
{
    // Pair<K,V> pair(key);
    return Iterator(map.find(key));
}

template <typename K, typename V>
bool Map<K,V>::contains(const Pair<K, V>& target) const
{
    return map.contains(target);
}


#endif //MAP_H