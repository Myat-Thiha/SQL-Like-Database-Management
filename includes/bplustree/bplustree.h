#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include<iostream>
#include<iomanip>
#include <set>
#include <vector>
#include <cassert>
#include"btree_array_funcs.h"
using namespace std;

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=NULL, int _key_ptr = 0):
                                                it(_it), key_ptr(_key_ptr){}

        T operator *()
        {
            assert(it);
            return it->data[key_ptr];
        }

        Iterator operator++(int un_used)
        {
            Iterator temp=it;
            assert(it);
            if(key_ptr<it->data_count-1)
            {
                key_ptr++;
            }
            else
            {
                //cout<<"I am here";
                key_ptr=0;
                it=it->next;
                //cout<<"next is "<<endl<<*it<<endl;
            }
            return temp;
        }

        Iterator operator++()
        {
            assert(it);
            if(key_ptr<it->data_count-1)
            {
                key_ptr++;
            }
            else
            {
                key_ptr=0;
                it=it->next;
            }
            return *this;
        }
        friend bool operator ==(const Iterator& lhs, const Iterator& rhs)
        {
            if((lhs.it==rhs.it)&&(lhs.key_ptr==rhs.key_ptr))
                    return true;
            else
            {
                return false;
            }
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs)
        {
            return((lhs.it!=rhs.it)||(lhs.key_ptr!=rhs.key_ptr));
        }
        void print_Iterator(){
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }
        bool is_null(){return !it;}
        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it;
        int key_ptr;
    };

    BPlusTree(bool dups = false)
    {
        data_count=0;
        child_count=0;
        dups_ok=dups;
        next=nullptr;
    }
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry)const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry
    Iterator find(const T& key);         //return an iterator to this key.
                                         //     NULL if not there.
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs,
                               const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();
    string post_order()
    {
        string post_order;
         for(int i=0; i<=data_count; i++)
        {
           
            if(!is_leaf())
            {
                post_order+=subset[i]->post_order();
            }
             if(i-1>=0)
            {
                post_order+=to_string(data[i-1])+"|";
            }
        }
    return post_order;

    }
    string pre_order()
    {
        string pre_order;
    for(int i=0; i<=data_count; i++)
        {
            if(i<data_count)
            {
                pre_order+=to_string(data[i])+"|";
            }
            if(!is_leaf())
            {
                pre_order+=subset[i]->pre_order();
            }
        }
    return pre_order;
    }
    Iterator begin();
    Iterator end();
    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;

    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;
    bool is_leaf() const
    {return child_count==0;}             //true if this is a leaf node

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // NULL if not there.

    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root
    void breadcrumbs(const T& entry);
    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

};

template<class T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups)
{
    data_count=0;
    child_count=0;
    dups_ok=dups;
    next=nullptr;
    for(int i=0; i<size;i++)
    {
        insert(a[i]);
    }
}

//big three:
template<class T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other)
{
    data_count=0;
    child_count=0;
    dups_ok=other.dups_ok;
    next=nullptr;
    copy_tree(other);
}

template<class T>
BPlusTree<T>::~BPlusTree()
{
    clear_tree();
}

template<class T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS)
{
    if(this ==&RHS)
    {
        return *this;
    }
    clear_tree();
    dups_ok=RHS.dups_ok;
    copy_tree(RHS);
    return *this;
}

template<class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other)  //copy other into this object
{
    //cout<<"I am here"<<endl;
    BPlusTree<T>* last_leaf=nullptr;
    copy_tree(other,last_leaf);
}

template<class T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node)
{
    copy_array(data,other.data,data_count,other.data_count);
    dups_ok=other.dups_ok;
    child_count=other.child_count;
    next=nullptr;
    for(int i=0; i<child_count; i++)
    {
        subset[i]=new BPlusTree<T>;
        subset[i]->copy_tree(*(other.subset[i]),last_node);
    }
    if(other.is_leaf())
    {
        if(last_node)
        {
            last_node->next=this;
        }
        last_node=this;
    }
}

template<class T>
void BPlusTree<T>::remove(const T& entry)   //remove entry from the tree
{
    loose_remove(entry);
    if((data_count==0)&&(child_count==1))
    {
        //cout<<"Shrinking..."<<endl;
        BPlusTree<T>* ptr=subset[0];
        copy_array(data,ptr->data,data_count,ptr->data_count);
        copy_array(subset,ptr->subset,child_count,ptr->child_count);
        ptr->data_count=0;
        ptr->child_count=0;
        delete ptr;
    }
}

template<class T>
void BPlusTree<T>::clear_tree()             //clear this object (delete all nodes etc.)
{
    int child_size=child_count;
    for(int i=0; i<child_size;i++)
    {
        subset[i]->clear_tree();
        delete subset[i];
    }
    child_count=0;
    data_count=0;
    next=nullptr;
}

template<typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& key)         //return an iterator to this key.//     NULL if not there.
{
    int i=first_ge(data,data_count,key);
    if(is_leaf())
    {
        if(i<data_count && key==data[i])
            return Iterator(this,i);
        else
            return Iterator(NULL);
    }
    else
    {
        if(i<data_count && key==data[i])
            return subset[i+1]->find(key);
        else
            return subset[i]->find(key);
    }
}

template<typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key)  //return first that goes NOT BEFORE// key entry or next if does not// exist: >= entry
{
    int i=first_ge(data,data_count,key);
    if(is_leaf())
    {
        for(Iterator it=begin(); it!=end();it++)
    {
        if(key<=*it)
        {
            return it;
        }
    }
    return Iterator(NULL);
    }
    else
    {
        if(i<data_count && key==data[i])
            return subset[i+1]->lower_bound(key);
        else
            return subset[i]->lower_bound(key);
    }
}

template<typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key)  //return first that goes AFTER key//exist or not, the next entry  >entry
{
    int i=first_ge(data,data_count,key);
    if(is_leaf())
    {
        for(Iterator it=begin(); it!=end();it++)
    {
        if(key<*it)
        {
            return it;
        }
    }
    return Iterator(NULL);
    }
    else
    {
        if(i<data_count && key==data[i])
            return subset[i+1]->upper_bound(key);
        else
            return subset[i]->upper_bound(key);
    }
}

template<class T>
int BPlusTree<T>::size() const                    //count the number of elements
{
    return 0;
}

template<class T>
bool BPlusTree<T>::empty() const                  //true if the tree is empty
{
    if(data_count==0)
        return true;
    else
        return false;
}

template<class T>
void BPlusTree<T>::print_tree(int level,ostream &outs) const
{
    for(int i=data_count; i>=0; i--)
        {
            if(i<data_count)
            {
                outs<<setw(4*level)<<""<<"["<<data[i]<<"]"<<endl;
            }
            if(!is_leaf())
            {
                subset[i]->print_tree(level+1);
            }
        }
}

template<class T>
bool BPlusTree<T>::is_valid()
{
    return true;
}

template<class T>
string BPlusTree<T>::in_order()
{
    string in_order;
    for(int i=0; i<=data_count; i++)
        {
            if(!is_leaf())
            {
                in_order+=subset[i]->in_order();
            }
            if(i<data_count)
            {
                in_order+=to_string(data[i])+"|";
            }
        }
    return in_order;
}

template<class T>
typename::BPlusTree<T>::Iterator BPlusTree<T>::begin()
{
    return Iterator(get_smallest_node());
}

template<class T>
typename::BPlusTree<T>::Iterator BPlusTree<T>::end()
{
    return Iterator(NULL);
}

template<class T>
bool BPlusTree<T>::contains(const T& entry) const //true if entry can be found
{
    int i=first_ge(data,data_count,entry);
    if(is_leaf())
    {
        if(i<data_count && entry==data[i])
            return true;
        else
            return false;
    }
    else
    {
        if(i<data_count && entry==data[i])
            return subset[i+1]->contains(entry);
        else
            return subset[i]->contains(entry);
    }
}

template<class T>
T& BPlusTree<T>::get(const T& entry)              //return a reference to entry
{
    //If entry is not in the tree, add it to the tree
    //assert(contains(entry));
    const bool debug = false;
    if (!contains(entry))
    {
        insert(entry);
    }
    return get_existing(entry);
}

template<class T>
T& BPlusTree<T>::get_existing(const T& entry)     //return a reference to entry
{
    //assert that entry is not in the tree.
    assert(contains(entry));

    const bool debug = false;
    int i = first_ge(data, data_count, entry);
    bool found = (i<data_count && data[i]==entry);
    if (is_leaf())
{
        if (found){
            return data[i];
        }
        else{
            if (debug) cout<<"get_existing was called with nonexistent entry"<<endl;
            assert(found);
        }
}
    if (found) //inner node
        return subset[i+1]->get(entry);
        //or just return true?
    else //not found yet...
        return subset[i]->get(entry);
}

template<class T>
const T& BPlusTree<T>::get(const T& entry)const   //return a reference to entry
{
    assert(contains(entry));
    int i=first_ge(data,data_count,entry);
    if(is_leaf())
    {
        if(i<data_count && entry==data[i])
            return data[i];
        else
            return NULL;
    }
    else
    {
        if(i<data_count && entry==data[i])
            return subset[i+1]->get(entry);
        else
            return subset[i]->get(entry);
    }
}

template<class T>
T* BPlusTree<T>::find_ptr(const T& entry)         //return a pointer to this key.// NULL if not there.
{
    int i=first_ge(data,data_count,entry);
    if(is_leaf())
    {
        if(i<data_count && entry==data[i])
            return &data[i];
        else
            return nullptr;
    }
    else
    {
        if(i<data_count && entry==data[i])
            return subset[i+1]->find_ptr(entry);
        else
            return subset[i]->find_ptr(entry);
    }
}

template<class T>
void BPlusTree<T>::insert(const T& entry)   //insert entry into the tree
{
    loose_insert(entry);
    if(data_count>MAXIMUM)
    {
    BPlusTree<T>* ptr=new BPlusTree<T>(dups_ok);
    copy_array(ptr->data,data,ptr->data_count,data_count);
    copy_array(ptr->subset,subset,ptr->child_count,child_count);
    data_count=0;
    child_count=1;
    subset[0]=ptr;
    fix_excess(0);
    }
}

template<class T>//insert element functions
void BPlusTree<T>::loose_insert(const T& entry)   //allows MAXIMUM+1 data elements in//   the root
{
    int i=first_ge(data,data_count,entry);
    if(is_leaf())
    {
        if(i<data_count && entry==data[i])
        {
            if(dups_ok==true)
            {
                data[i]=data[i]+entry;
            }
            else
            {
                data[i]=entry;
            }
        }
        else
        {
            insert_item(data,i,data_count,entry);
        }
    }
    else
    {
        if(i<data_count && entry==data[i])
        {
            subset[i+1]->loose_insert(entry);
            if(subset[i+1]->data_count>MAXIMUM)
            fix_excess(i+1);
        }
        else
        {
            subset[i]->loose_insert(entry);
            if(subset[i]->data_count>MAXIMUM)
            fix_excess(i);
        }
    }
}

template<class T>
void BPlusTree<T>::fix_excess(int i)             //fix excess in child i
{
T excess;
    BPlusTree<T>* ptr=new BPlusTree<T>(dups_ok); 
    split(subset[i]->data,subset[i]->data_count,ptr->data,ptr->data_count);
    split(subset[i]->subset,subset[i]->child_count,ptr->subset,ptr->child_count);
    detach_item(subset[i]->data,subset[i]->data_count,excess);
    ordered_insert(data,data_count,excess);
    insert_item(subset,i+1,child_count,ptr);
    if(subset[i]->is_leaf())
    {
        subset[i+1]->next=subset[i]->next;
        subset[i]->next=subset[i+1];
        insert_item(subset[i+1]->data,0,subset[i+1]->data_count,excess);
    }
}

template<class T>//remove element functions:
void BPlusTree<T>::loose_remove(const T& entry)  //allows MINIMUM-1 data elements//  in the root
{
    int i=first_ge(data,data_count,entry);
    T remove;
    T hold;
    int index1,index2,index3;
    bool found_data=false;
    bool found_subseti=false;
    bool found_subseti1=false;
    if(is_leaf())
    {
        if(i<data_count && entry==data[i])
            delete_item(data,i,data_count,remove);
        else
            cout<<"entry not found!"<<endl;
    }
    else
    {
        if(i<data_count && entry==data[i])
        {
            subset[i+1]->loose_remove(entry);
            if(subset[i+1]->data_count < MINIMUM)
            {
            fix_shortage(i+1);
            breadcrumbs(entry);
            }
            else if(i+1 < child_count && i < data_count)
            {
                subset[i+1]->get_smallest(hold);
                data[i]=hold;
            }
            else{}
        }
        else
        {
            subset[i]->loose_remove(entry);
            if(subset[i]->data_count < MINIMUM)
            {
            fix_shortage(i);
            }
        }
    }
}

template<typename T>
void BPlusTree<T>::breadcrumbs(const T& entry)
{
    int i=first_ge(data,data_count,entry);
     if(i < data_count && data[i]==entry)
     {
         subset[i+1]->get_smallest(data[i]);
     }
     else if(i<child_count)
     {
         subset[i]->breadcrumbs(entry);
     }
    //  else if(i+1<child_count)
    //  {
    //      subset[i+1]->breadcrumbs(entry);
    //  }
}

template<class T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int i)  //fix shortage in child i// and return the smallest key in this subtree
{
    cout<<"i is "<<i<<endl;
        if(i<child_count-1 && subset[i+1]->data_count>MINIMUM)
        {
            cout<<"rotate left"<<endl;
            transfer_left(i);
        }
        else if(i>0 && subset[i-1]->data_count>MINIMUM)
        {
            cout<<"rotate right"<<endl;
            transfer_right(i);
        }
        else if(i>0 && subset[i-1]->data_count<=MINIMUM)
        {
            cout<<"merge i-1"<<endl;
            merge_with_next_subset(i-1);
        }
        else
        {
            cout<<"merge i "<<endl;
            merge_with_next_subset(i);
        }
        return subset[i];
        // else
        // {
        //     cout<<"GOD HELP ME"<<endl;
        //     return subset[i];
        // }
}

template<class T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node()
{
    if(!is_leaf())
    {
        return subset[0]->get_smallest_node();
    }
    else
    {
        return this;
    }
}

template<class T>
void BPlusTree<T>::get_smallest(T& entry)      //entry := leftmost leaf
{
    if(!is_leaf())
    {
        subset[0]->get_smallest(entry);
    }
    else
    {
        if(data_count>0)
        entry=data[0];
    }
}

template<class T>
void BPlusTree<T>::get_biggest(T& entry)       //entry := rightmost leaf
{
    if(!is_leaf())
    {
        subset[child_count-1]->get_biggest(entry);
    }
    else
    {
        entry=data[data_count-1];
    }
}

template<class T>
void BPlusTree<T>::remove_biggest(T& entry)    //remove the biggest child of tree->entry
{

}

template<class T>
void BPlusTree<T>::transfer_left(int i)        //transfer one element LEFT from child i
{
    if(!(subset[i]->is_leaf()))
    {
        T last_from_subset;
        insert_item(subset[i]->data,0,subset[i]->data_count,data[i]);
        delete_item(subset[i+1]->data,0,subset[i+1]->data_count,last_from_subset);
        data[i]=last_from_subset;
        if(subset[i+1]->child_count>0)
        {
            BPlusTree<T>* ptr;
            delete_item(subset[i+1]->subset,0,subset[i+1]->child_count,ptr);
            insert_item(subset[i]->subset,subset[i]->child_count,subset[i]->child_count,ptr);
        } 
    }   
    else
    {
        T first_data;
        delete_item(subset[i+1]->data,0,subset[i+1]->data_count,first_data);
        attach_item(subset[i]->data,subset[i]->data_count,first_data);
        data[i]=subset[i+1]->data[0];
    }
}

template<class T>
void BPlusTree<T>::transfer_right(int i)       //transfer one element RIGHT from child i
{
    if(!(subset[i]->is_leaf()))
    {
        T last_from_subset;
        insert_item(subset[i]->data,0,subset[i]->data_count,data[i-1]);
        delete_item(subset[i-1]->data,subset[i-1]->data_count-1,subset[i-1]->data_count,last_from_subset);
        data[i-1]=last_from_subset;
        if(subset[i-1]->child_count>0)
        {
            BPlusTree<T>* ptr;
            delete_item(subset[i-1]->subset,subset[i-1]->child_count-1,subset[i-1]->child_count,ptr);
            insert_item(subset[i]->subset,0,subset[i]->child_count,ptr);
        }
    }
    else
    {
        T last_data;
        delete_item(subset[i-1]->data,subset[i-1]->data_count-1,subset[i-1]->data_count,last_data);
        insert_item(subset[i]->data,0,subset[i]->data_count,last_data);
        data[i-1]=last_data;
    }
}

template<class T>
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int i) //merge subset i with  i+1
{
        T remove_data=T();
        delete_item(data,i,data_count,remove_data);
        if(!subset[i]->is_leaf())
        attach_item(subset[i]->data,subset[i]->data_count,remove_data);
        merge(subset[i]->data,subset[i]->data_count,subset[i+1]->data,subset[i+1]->data_count);
        merge(subset[i]->subset,subset[i]->child_count,subset[i+1]->subset,subset[i+1]->child_count);
        BPlusTree<T>* ptr;
        delete_item(subset,i+1,child_count,ptr);
        if(subset[i]->is_leaf())
        {
            subset[i]->next=ptr->next;
        }
        delete ptr;
        return subset[i];
}


#endif //BPLUSTREE_H