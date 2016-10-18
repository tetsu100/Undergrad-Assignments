#ifndef GENQUEUE_H
#define GENQUEUE_H

#include <iostream>
#include "doubleLinkedList.h"

template <typename T>
class GenQueue
{
    int size;
	doubleLinkedList<T> *dlist;
public:
    GenQueue() : size ( 0 ) { dlist = new doubleLinkedList<T>(); }
    template<int N>
    GenQueue( T (&arr) [N]) : size ( 0 )
    {
        dlist = new doubleLinkedList<T>( arr );
		size = N;
    }
    bool notEmpty() const { return ( getSize() ); }
	int getSize() const { return ( this->size ); }
    void push(T);
	T peek();
    T pop();
};
template <typename T>
void GenQueue<T>::push(T data)
{
    dlist->push_back(data);
	size++;
}

template<typename T>
T GenQueue<T>::pop()
{
	if(notEmpty()) {
		size--;
		return dlist->pop_front();
	}
	std::cout << "popping empty Q" << std::endl;
	T tmp;
	return tmp;
}

template<typename T>
T GenQueue<T>::peek()
{
	if(notEmpty()) {
		return dlist->peek();
	}
	T tmp;
	return tmp;
}

#endif