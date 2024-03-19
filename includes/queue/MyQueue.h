#ifndef MY_QUEUE
#define MY_QUEUE
#include<iostream>
#include<iomanip>
#include<cassert>
#include"../node/node.h"
#include"../linked_list_functions/linkedlistfunctionsTemplated.h"
using namespace std;

template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;          //give access to list to access _ptr
        Iterator(){ _ptr=nullptr;}         //default ctor
        Iterator(node<T>* p){ _ptr=p;}        //Point Iterator to where
        //...                        //  p is pointing to
        T &operator*()
        {
            assert(_ptr!=nullptr);
            return _ptr->_item;
        }                            //dereference operator

        T *operator->()
        {
            return &_ptr->_item;
        }                    //member access operator

        operator bool()
        {
            if(_ptr!=nullptr)
            {
                return true;
            }
            else
            return false;
        }

        bool is_null()
        {
            if(_ptr==nullptr)
                return true;
            else
                return false;
        }                        
        friend bool operator!=(const Iterator &left,
                               const Iterator &right)
        {
            if(left._ptr==right._ptr)
                return false;
            else
                return true;
        }//true if left != right

        friend bool operator==(const Iterator &left,
                               const Iterator &right)
        {
            if(left._ptr==right._ptr)
                return true;
            else
                return false;
        } //true if left == right

        Iterator &operator++()
        {
            _ptr=_ptr->_next;
            return *this;
        }                         //member operator:
                                                        //  ++it; or
                                                        //  ++it = new_value

        friend Iterator operator++(Iterator &it,
                                   int unused)
        {
            Iterator hold;
            hold=it;
            it._ptr=it._ptr->_next;
            return hold;
        } 
    private:
        node<T>* _ptr;               //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

template <typename T>
Queue<T>::Queue()
{
    _front=nullptr;
    _rear=nullptr;
    _size=0;
}

template <typename T>
Queue<T>::Queue(const Queue<T>& copyMe)
{
    _front=nullptr;
    _rear=_copy_list(_front,copyMe._front);
    _size=copyMe._size;
}

template <typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS)
{
    if(this == &RHS)
    {
        return *this;
    }
    if(_front!=nullptr)
    {
        _clear_list(_front);
        _front=nullptr;
        _rear=nullptr;
    }
    _rear=_copy_list(_front,RHS._front);
    _size=RHS._size;
    return *this;
}

template<typename T>
Queue<T>::~Queue()
{
    _clear_list(_front);
}

template<typename T>
bool Queue<T>::empty()
{
    return _front==nullptr;
}

template<typename T>
T Queue<T>::front()
{
    return _front->_item;
}

template<typename T>
T Queue<T>::back()
{
    return _rear->_item;
}

template<typename T>
void Queue<T>::push(T item)
{
    if(_front==nullptr)
    {
        _rear=_insert_head(_front,item);
    }
    else
    {
    _rear=_insert_after(_front,_rear,item);
    }
    _size++;
}

template<typename T>
T Queue<T>::pop()
{
    if(_front!=_rear)
    {
    _size--;
    return _delete_node(_front,_front);
    }
    else
    {
        _rear=nullptr;
        _size--;
        return _delete_node(_front,_front);
    }
}


template<typename T>
void Queue<T>::print_pointers()
{
    _print_list(this->_front);
}

template<typename T>
typename Queue<T>::Iterator Queue<T>::begin() const
{
    return Iterator(_front);
}

template<typename T>
typename Queue<T>::Iterator Queue<T>::end() const
{
    return Iterator(nullptr);
}

template<typename TT>
ostream& operator << (ostream& outs, const Queue<TT>& printMe)
{
    outs<<"Queue:";
    _print_list(printMe._front);
    return outs;
}

#endif  //QUEUE.H