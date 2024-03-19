#ifndef BTREE_ARRAY_FUNCS_H
#define BTREE_ARRAY_FUNCS_H
#include <cmath>
#include<iostream>
#include <iomanip>
#include <set>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

template <class T>
T maximal(const T& a, const T& b);                      //return the larger of the two items

template <class T>
void swap(T& a, T& b);  //swap the two items

template <class T>
int index_of_maximal(T data[ ], int n);                 //return index of the largest item in data

template <class T>
void ordered_insert(T data[ ], int& n, T entry);        //insert entry into the sorted array
                                                        //data with length n

template <class T>
int first_ge(const T data[ ], int n, const T& entry);   //return the first element in data that is
                                                        //not less than entry

template <class T>
void attach_item(T data[ ], int& n, const T& entry);    //append entry to the right of data

template <class T>
void insert_item(T data[ ], int i, int& n, T entry);    //insert entry at index i in data

template <class T>
void detach_item(T data[ ], int& n, T& entry);          //remove the last element in data and place
                                                        //it in entry

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry);   //delete item at index i and place it in entry

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2);   //append data2 to the right of data1

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2);   //move n/2 elements from the right of data1
                                                        //and move to data2

template <class T>
void copy_array(T dest[], const T src[],
                int& dest_size, int src_size);              //copy src[] into dest[]

template <class T>
void print_array(const T data[], int n, int pos = -1);  //print array data

template <class T>
bool is_gt(const T data[], int n, const T& item);       //item > all data[i]

template <class T>
bool is_le(const T data[], int n, const T& item);       //item <= all data[i]

template <class T>
bool search_array(T data[],int n,T item,int& index)
{
    for(int i=0; i<n; i++)
    {
        if(data[i]==item)
        {
            index=i;
            return true;
        }
    }
    return false;
}
//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list); //print vector list

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme); //list.push_back addme

template <typename T>
vector<T> vector_intersection(vector<T> v1,vector<T> v2)
{
     vector<T> v3;

    sort(v1.begin(), v1.end());
    sort(v2.begin(), v2.end());

    set_intersection(v1.begin(),v1.end(),
                          v2.begin(),v2.end(),
                          back_inserter(v3));
    return v3;
}

template <typename T>
vector<T> vector_union(vector<T> v1,vector<T> v2)
{
    vector<T> v3;
    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());
    set_union(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v3));
    return v3;
}

template<typename T>
vector<T>& operator +=(vector<T>& list1, const vector<T>& list2);

//-----------------------------------definitions----------------------------------------//

template <class T>
T maximal(const T& a, const T& b)                      //return the larger of the two items
{
    if(a>b)
        return a;
    return b;
}

template <class T>
void swap(T& a, T& b)  //swap the two items
{
    T temp=a;
    a=b;
    b=temp;
}

template <class T>
int index_of_maximal(T data[ ], int n)                 //return index of the largest item in data
{
    T max;
    int index;
    max=data[0];
    for(int i=0; i< n-1; i++)
    {
        if(max<data[i])
        {
            max=data[i];
            index=i;
        }
            //cout<<"max is "<<max<<endl;
    }
    //cout<<index<<endl;
    return index;
}

template <class T>
void ordered_insert(T data[ ], int& n, T entry)        //insert entry into the sorted array//data with length n
{
    int index=first_ge(data,n,entry);
    insert_item(data,index,n,entry);
}

template <class T>
int first_ge(const T data[ ], int n, const T& entry)   //return the first element in data that is//not less than entry
{
    //assert(n<=3);
    for(int i=0; i< n; i++)
    {
        if(!(data[i] < entry))
            return i;
    }
    return n;
}

template <class T>
int first_g(const T data[ ], int n, const T& entry)   //return the first element in data that is not less than and equal to entry
{
    //assert(n<=3);
    for(int i=0; i< n; i++)
    {
        if(!(data[i] <= entry))
            return i;
    }
    return n;
}

template <class T>
void attach_item(T data[ ], int& n, const T& entry)    //append entry to the right of data
{
    //cout<<"I am here"<<endl;
    data[n]=entry;
    n++;
}

template <class T>
void insert_item(T data[ ], int i, int& n, T entry)    //insert entry at index i in data
{
    //assert(n<=3);
        for(int index=n; index>i;index--)
        {
            data[index]=data[index-1];
        }
        n++;
        data[i]=entry;
}

template <class T>
void detach_item(T data[ ], int& n, T& entry)          //remove the last element in data and place//it in entry
{
    entry=data[n-1];
    //T* ptr=data[n-1];
    //delete ptr;
    n--;
}

template <class T>
void delete_item(T data[ ], int i, int& n, T& entry)   //delete item at index i and place it in entry
{
    if(n==0)
    {
        cout<<"I am here"<<endl;
        entry=T();
    }
    entry=data[i];
    n--;
    for(int index=i; index<n; index++)
    {
        data[index]=data[index+1];
    }
}

template <class T>
void merge(T data1[ ], int& n1, T data2[ ], int& n2)   //append data2 to the right of data1
{
    int size_2=n2;
    for(int i=0; i<size_2;i++)
    {
        data1[n1]=data2[i];
        n1++;
    }
    n2=0;
}

template <class T>
void split(T data1[ ], int& n1, T data2[ ], int& n2)   //move n/2 elements from the right of data1//and move to data2
{
    int half=n1/2;
    if(n1%2==0)
    {
    for(int i=half; i<n1; i++)
    {
        data2[n2]=data1[i];
        n2++;
    }
    n1=half;
    }
    else
    {
        for(int i=half+1; i<n1; i++)
    {
        data2[n2]=data1[i];
        n2++;
    }
    n1=half+1;
    }
}

template <class T>
void copy_array(T dest[], const T src[],int& dest_size, int src_size)              //copy src[] into dest[]
{
    dest_size=src_size;
    for(int i=0; i<src_size; i++)
    {
        //cout<<"I am here"<<endl;
        dest[i]=src[i];
    }
}

template <class T>
void print_array(const T data[], int n, int pos)  //print array data
{
    for(int i=pos; i<n; i++)
    {
        cout<<"["<<data[i]<<"]"<<"-";
    }
    cout<<endl;
}

template <class T>
bool is_gt(const T data[], int n, const T& item)       //item > all data[i]
{
    bool flag=false;
    for(int i=0; i<n; i++)
    {
        if(item>data[i])
            flag=true;
        flag=false;
    }
    return flag;
}

template <class T>
bool is_le(const T data[], int n, const T& item)       //item <= all data[i]
{
    bool flag=false;
    for(int i=0; i<n; i++)
    {
        if(item <= data[i])
            flag=true;
        flag=false;
    }
    return flag;
}

//-------------- Vector Extra operators: ---------------------

template <typename T>
ostream& operator <<(ostream& outs, const vector<T>& list) //print vector list
{
    for(int i=0; i<list.size(); i++)
    {
        outs<<" "<<list[i];
    }
    return outs;
}

template <typename T>
vector<T>& operator +=(vector<T>& list, const T& addme) //list.push_back addme
{
    list.push_back(addme);
    return list;
}

template <typename T>
vector<T>& operator +=(vector<T>& list1,const vector<T>& list2)
{
    for(int i=0; i<list2.size(); i++)
    {
        list1.push_back(list2[i]);
    }
    return list1;
}

#endif //BTREE_ARRAY_FUNCS_H