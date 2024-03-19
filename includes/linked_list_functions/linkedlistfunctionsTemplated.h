#ifndef LINKED_LIST
#define LINKED_LIST
#include<iostream>
#include<iomanip>
#include<cassert>
#include"../node/node.h"
using namespace std;

//Linked List General Functions:
    template <typename T>
    void _print_list(node<T>* head);

    //recursive fun! :)
    template <typename T>
    void _print_list_backwards(node<T> *head);

    //return ptr to key or NULL
    template <typename T>
    node<T>* _search_list(node<T>* head,
                                T key);


    template <typename T>
    node<T>* _insert_head(node<T> *&head,T insert_this);

    //insert after ptr
    template <typename T>
    node<T>* _insert_after(node<T>*& head,
                                 node<T> *after_this,
                                 T insert_this);

    //insert before ptr
    template <typename T>
    node<T>* _insert_before(node<T>*& head,
                                  node<T>* before_this,
                                  T insert_this);

    //ptr to previous node
    template <typename T>
    node<T>* _previous_node(node<T>* prev_to_this);

    //delete, return item
    template <typename T>
    T _delete_node(node<T>*&head,
                         node<T>* delete_this);

    //duplicate the list...
    template <typename T>
    node<T>* _copy_list(node<T>* head);

    //duplicate list and return the last node of the copy
    template <typename T>
    node<T> *_copy_list(node<T>* &dest, node<T> *src);

    //delete all the nodes
    template <typename T>
    void _clear_list(node<T>*& head);

    //_item at this position
    template <typename T>
    T& _at(node<T>* head, int pos);

    //Last Node in the list
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head);

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                                  ITEM_TYPE item,
                                  bool ascending=true);

    //insert or add if a dup
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                          ITEM_TYPE item,
                                          bool ascending=true);

    //node after which this item goes order: 0 ascending
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                   ITEM_TYPE item,
                                   bool ascending=true);

// definitions

template <typename T>
void _print_list(node<T>* head)
{
    node<T>*walker =head;
    cout << "H->";
    while(walker!=nullptr)
    {
        cout << *walker;
        walker = walker->_next;
    }
    cout << "T->|||"<<endl;
}

template <typename T>
void _print_list_backwards(node<T> *head)
{
if(head==nullptr)
    {
        return;
    }
    _print_list_backwards(head->_next);
    cout<<*head;
}

template <typename T>
node<T>* _search_list(node<T>* head,T key)
{
    node<T>*walker=head;
    while(walker!=nullptr)
    {
        if(walker->_item==key)
        {
            return  walker;
        }
    walker=walker->_next;
    }
    return walker;
}

template <typename T>
node<T>* _insert_head(node<T> *&head,T insert_this)
{
    if(head==nullptr)
    {
        node<T>*temp =new node<T>(insert_this,head);
        head=temp;
        return head;
    }
    node<T>*temp =new node<T>(insert_this,head);
    head->_prev=temp;
    head=temp;
    return head;
}

template <typename T>
node<T>* _insert_after(node<T>*& head,node<T> *after_this,T insert_this)
{
    if((head==nullptr)||(after_this==nullptr))
    {
       _insert_head(head,insert_this);
       return head;
    }
    //assert(after_this!=nullptr);
    node<T>*temp=after_this->_next;
    if(temp==nullptr)
    {         
                                                               //if inserting after the tail or list has only one node, do not
    node<T>*insert=new node<T>(insert_this,temp,after_this);    //worry about the prev of the nafter_this->_next since it is nullptr
    //temp->_prev=insert;
    after_this->_next=insert;
    return insert;
    }
    node<T>*insert=new node<T>(insert_this,temp,after_this);
    temp->_prev=insert;
    after_this->_next=insert;
    return insert;
}

template <typename T>
node<T>* _insert_before(node<T>*& head,node<T>* before_this,T insert_this)
{
    if((head==before_this)||(before_this==nullptr))
    {
        _insert_head(head,insert_this);
        return head;
    }
    node<T>*previous=_previous_node(before_this);
    node<T>*insert=new node<T>(insert_this,before_this,previous);
    before_this->_prev=insert;
    previous->_next=insert;
    return insert;
}

template <typename T>
node<T>* _previous_node(node<T>* prev_to_this)
{
    node<T>* temp= prev_to_this->_prev;
    if(temp==nullptr)
    {
        return nullptr;
    }
    return temp;
}

template <typename T>
 T _delete_node(node<T>*&head,node<T>* delete_this)
 {
     T temp;
     node<T>* walker=head;
     if(walker==nullptr)
     {
        return T();
     }
     else if(walker==delete_this)
     {
        if(walker->_next==nullptr)
        {
            temp=walker->_item;
            delete walker;
            head=nullptr;
            return temp;
        }
        temp=walker->_item;
        head=head->_next;
        head->_prev=nullptr;
        delete walker;
        return temp;
     }
    else
    {
     while(walker!=nullptr)
     {
         if(walker==delete_this)
         {
            cout<<"I am here"<<endl;
            node<T>* prev_walker=walker->_prev;
            node<T>* next_walker=walker->_next;
            if(next_walker==nullptr)
            {
                prev_walker->_next=nullptr;
                temp=walker->_item;
                delete walker;
                return temp;
            }
            prev_walker->_next=next_walker;
            next_walker->_prev=prev_walker;
            temp=walker->_item;
            delete walker;
            return temp;
         }
         walker=walker->_next;
     }
    return T();
    }
}

/*
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src)
{
    if(src==nullptr)
    {
        dest=nullptr;
        return dest;
    }
    node<T>*walker1=src;
    while(walker1->_next!=nullptr)
    {
        node<T>*temp =new node<T>(src->_item);
        temp-> _next= src->_next;
        dest=temp;
        walker1=walker1->_next;
    }
    return walker1;
}
*/

template <typename T>
node<T>* _copy_list(node<T>* &dest, node<T> *src)
{
    if(src==nullptr)
    {
        dest=nullptr;
        return dest;
    }
    node<T>*walker1=src;
    node<T>*walker2=_insert_head(dest,walker1->_item);
    walker1=walker1->_next;
    while(walker1!=nullptr)
    {
        _insert_after(dest,walker2,walker1->_item);
        walker1=walker1->_next;
        walker2=walker2->_next;
    }
    return _last_node(dest);
}

template <typename T>
node<T>* _copy_list(node<T>* head)
{
    node<T>* dest=nullptr;
    _copy_list(dest,head);
    return dest;
}

template <typename T>
void _clear_list(node<T>*& head)
{
    node<T>* walker=head;
    node<T>* walker2=head;
    while(walker2!=nullptr)
    {
        walker2=walker->_next;
        delete walker;
        walker=walker2;
    }
    head=nullptr;
}

template <typename T>
T& _at(node<T>* head, int pos)
{
    int num=0;
    node<T>* varify=head;
    while(varify!=nullptr)
    {
        varify=varify->_next;
        num++;
    }
    assert((num>pos)&&(pos>=0));
    node<T>* walker=head;
    for(int i=0;i<pos;i++)
    {
        walker=walker->_next;
    }
    return walker->_item;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head)
{
    if(head==nullptr||head->_next==nullptr)
    {
        return head;
    }
    node<ITEM_TYPE>* walker=head;
    while(walker->_next!=nullptr)
    {
        walker=walker->_next;
    }
    return walker;
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,ITEM_TYPE item,bool ascending)
{
    node<ITEM_TYPE>* walker=head;
    
    if(ascending)
    {
        if((walker==nullptr)||(item<walker->_item))
        {
            cout <<"returning null :";
            return nullptr;
        }
        node<ITEM_TYPE>* walker2=walker->_next;
        while(walker2!=nullptr)
        {
            if((item>=walker->_item)&&(item<walker2->_item))
            return walker;
            walker=walker->_next;
            walker2=walker2->_next;
        }
        return walker;
    }
    else
    {
        if((walker==nullptr)||(item>walker->_item))
        {
            return nullptr;
        }
        node<ITEM_TYPE>* walker2=walker->_next;
        while(walker2!=nullptr)
        {
            if((item<=walker->_item)&&(item>walker2->_item))
            return walker;
            walker=walker->_next;
            walker2=walker->_next;
        }
        return walker;
    }
}
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,ITEM_TYPE item,bool ascending)
{
    node<ITEM_TYPE>* found=_search_list(head,item);
    if(found)
    {
        found->_item=found->_item+item;
        return found;
    }
    else
        return _insert_sorted(head,item,ascending);
}

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,ITEM_TYPE item,bool ascending)
{
    node<ITEM_TYPE>* temp=_where_this_goes(head,item,ascending);
    if(temp==nullptr)
    {
        //cout<<"Entering here !"<<endl;
        return _insert_head(head,item);
    }
    else
    {
        return _insert_after(head,temp,item);
    }
}
#endif //LINKED_LIST