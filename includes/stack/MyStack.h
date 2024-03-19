#ifndef MY_STACK
#define MY_STACK
#include<iostream>
#include<iomanip>
#include<cassert>
#include"../node/node.h"
#include"../linked_list_functions/linkedlistfunctionsTemplated.h"
using namespace std;

template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                     //give access to list to access _ptr
        Iterator(){_ptr = NULL;}                //default ctor
        Iterator(node<T>* p){_ptr =p;}          //Point Iterator to where
                                                //  p is pointing to
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
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template<typename TT>
    friend ostream& operator<<(ostream& outs, const Stack<TT>& printMe);

    Iterator begin() const;              //Iterator to the head node
    Iterator end() const;                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};

template <typename T>
Stack<T>::Stack()
{
    _top=nullptr;
    _size=0;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& copyMe)
{
    // if(_top!=nullptr)
    // {
    //     _clear_list(_top);
    //     _top=nullptr;
    // }
    _top=nullptr;
    _top=_copy_list(copyMe._top);
    _size=copyMe._size;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& RHS)
{
    if(this == &RHS)
    {
        return *this;
    }
    if(_top!=nullptr)
    {
        _clear_list(_top);
        _top=nullptr;
    }
    _top=_copy_list(RHS._top);
    _size=RHS._size;
    return *this;
}

template<typename T>
Stack<T>::~Stack()
{
    _clear_list(_top);
}


template<typename T>
bool Stack<T>::empty()
{
    return _top==nullptr;
}

template<typename T>
T Stack<T>::top()
{
    return _top->_item;
}

template<typename T>
void Stack<T>::push(T item)
{
    _top=_insert_head(_top,item);
    _size++;
}

template<typename T>
T Stack<T>::pop()
{
    _size--;
    return _delete_node(_top,_top);
}

template<typename T>
typename Stack<T>::Iterator Stack<T>::begin() const
{
    return Iterator(_top);
}

template<typename T>
typename Stack<T>::Iterator Stack<T>::end() const
{
    return Iterator(nullptr);
}

template<typename TT>
ostream& operator<<(ostream& outs, const Stack<TT>& printMe)
{
    outs<<"Stack:";
    _print_list(printMe._top);
    return outs;
}
#endif //MY_STACK