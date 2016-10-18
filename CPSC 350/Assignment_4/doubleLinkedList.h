#ifndef DOUBLINKEDLIST_H
#define DOUBLINKEDLIST_H

#include <iostream>

using namespace std;

template <typename T>
class doubleLinkedList
{
    struct node
    {
        T data;
        node* prev;
        node* next;
        node(T t, node* p, node* n) : data(t), prev(p), next(n) {}
    };
    node* head;
    node* tail;
public:
    doubleLinkedList() : head( NULL ), tail ( NULL ) {}
    template<int N>
    doubleLinkedList( T (&arr) [N]) : head( NULL ), tail ( NULL ) //overloaded constructor passes array by ref
    {
        for( int i(0); i != N; ++i)
            push_back(arr[i]);
    }
    bool empty() const { return ( !head || !tail ); }
    operator bool() const { return !empty(); } 
    void push_back(T);
    void push_front(T);
    T pop_back();
    T pop_front();
	T peek();
    ~doubleLinkedList()
    {
        while(head)
        {
            node* temp(head);
            head=head->next;
            delete temp;
        }
    }
};
template <typename T>
void doubleLinkedList<T>::push_back(T data)
{
    tail = new node(data, tail, NULL);
    if( tail->prev )
        tail->prev->next = tail;
    if( empty() )
        head = tail;
}
template <typename T>
void doubleLinkedList<T>::push_front(T data)
{
    head = new node(data, NULL, head);
    if( head->next )
        head->next->prev = head;
    if( empty() )
        tail = head;
}
template<typename T>
T doubleLinkedList<T>::pop_back()
{
    if( empty() )
        throw("doubleLinkedList : list empty");
    node* temp(tail);
    T data( tail->data );
    tail = tail->prev ;
    if( tail )
        tail->next = NULL;
    else
        head = NULL ;
    delete temp;
    return data;
}
template<typename T>
T doubleLinkedList<T>::pop_front()
{
    if( empty() )
        throw("doubleLinkedList : list empty");
    node* temp(head);
    T data( head->data );
    head = head->next ;
    if( head )
        head->prev = NULL;
    else
        tail = NULL;
    delete temp;
    return data;
}

template<typename T>
T doubleLinkedList<T>::peek()
{
    if( empty() )
        throw("doubleLinkedList : list empty");
    T data( head->data );
    return data;
}

#endif