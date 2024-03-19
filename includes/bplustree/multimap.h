#ifndef MULTIMAP_H
#define MULTIMAP_H
#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <cassert>
#include "bplustree.h"
#include "btree_array_funcs.h"
template <typename K, typename V>
struct MPair{
    K key;
    vector<V> value_list;

    //--------------------------------------------------------------------------------
    /*      MPair CTORs:
     *  must have these CTORs:
     *  - default CTOR / CTOR with a key and no value: this will create an empty vector
     *  - CTOR with a key AND a value: pushes the value into the value_list
     *  _ CTOR with a key and a vector of values (to replace value_list)
     */
    //--------------------------------------------------------------------------------
    MPair(const K& k=K())
    {
        key=k;
        value_list.clear();
    }
    MPair(const K& k, const V& v)
    {
        key=k;
        value_list.push_back(v);
    }
    MPair(const K& k, const vector<V>& vlist)
    {
        key=k;
        value_list.clear();
        for(int i=0; i<vlist.size();i++)
        {
            value_list.push_back(vlist[i]);
        }
    }
    //--------------------------------------------------------------------------------

    //You'll need to overlod << for your vector:
    friend ostream& operator <<(ostream& outs, const MPair<K, V>& print_me)
    {
        outs<<print_me.key<<" : "<<print_me.value_list<<" ";
        return outs;
    }
    
    friend bool operator ==(const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        if(lhs.key == rhs.key)
            return true;
        return false;
    }
    friend bool operator < (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        if(lhs.key < rhs.key)
            return true;
        return false;
    }
    friend bool operator <= (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        if(lhs.key <= rhs.key)
            return true;
        return false;
    }
    friend bool operator > (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
        if(lhs.key > rhs.key)
            return true;
        return false;
    }
    friend MPair<K, V> operator + (const MPair<K, V>& lhs, const MPair<K, V>& rhs)
    {
       MPair<K,V> mp;
       mp.key=lhs.key;
       mp.value_list=lhs.value_list;
       for(int i=0; i<rhs.value_list.size(); i++)
       {
           mp.value_list.push_back(rhs.value_list[i]);
       }
       return mp;
    }
};


template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
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
        MPair<K, V> operator *()
        {
            return *_it;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            return(lhs._it==rhs._it);
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return(lhs._it!=rhs._it);
        }

    private:
        typename map_base::Iterator _it;
    };

    MMap()
    {
        bool flag=true;
        mmap=BPlusTree<MPair<K, V> >(flag);
    }

//  Iterators
    Iterator begin()
    {
        return Iterator(mmap.begin());
    }
    Iterator end()
    {
        return Iterator(mmap.end());
    }

//  Capacity
    int size() const
    {
        return mmap.size();
    }
    bool empty() const
    {
        return mmap.empty();
    }

//  Element Access
    const vector<V>& operator[](const K& key) const
    {
        return at(key);
    }
    vector<V>& operator[](const K& key)
    {
        return at(key);
    }
    vector<V> &at(const K& key)
    {
        return mmap.get(key).value_list;
    }
    
    const vector<V> &at(const K& key) const
    {   
        return mmap.get(key).value;
    }
//  Modifiers
    void insert(const K& k, const V& v)
    {
        mmap.insert(MPair<K,V>(k,v));
    }
    void erase(const K& key)
    {
        mmap.erase(key);
    }
    void clear()
    {
        mmap.clear_tree();
        // mmap.key=K();
        // mmap.value_list.clear();
    }

//  Operations:
    bool contains(const K& key) const
    {
        return mmap.contains(key);
    }
    vector<V> &get(const K& key)
    {
        return mmap.get(key).value_list;
    }
    Iterator find(const K& key)
    {
        return Iterator(mmap.find(key));
    }
    int count(const K& key)
    {
        return mmap.size();
    }
    Iterator lower_bound(const K& key)
    {
        return Iterator(mmap.lower_bound(key));
    }
    Iterator upper_bound(const K& key)
    {
        return Iterator(mmap.upper_bound(key));
    }
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    bool is_valid()
    {
        return mmap.is_valid();
    }

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        //print_me.print_iterator();
        return outs;
    }

    void print_iterator()const
    {
        MMap<K, V>::Iterator it;
        for (it =begin(); it != end(); it++)
        {
            cout << *it << " | ";
        }
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};
#endif //MULTIMAP_H