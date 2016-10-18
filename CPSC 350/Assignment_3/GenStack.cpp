#include "GenStack.h"
#include <iostream>

using namespace std;

template<typename genType>
GenStack<genType>::GenStack(int size)
{ 
	(size > 0)? this->sizeStack = size : this->sizeStack = 1;
	this->top = -1;
	genStackPtr = new genType[this->sizeStack];
}

template<typename genType>
bool GenStack<genType>::push(const genType &obj)
{
	if(this->top < this->sizeStack - 1) {
		genStackPtr[++top] = obj;
		return true;
	}
	else if(this->top < this->sizeStack) {
		this->resize();
		genStackPtr[++top] = obj;
		return true;
	}
	else {
		cout << "ATTEMPT TO PUSH FULL STACK" << endl;
		return false;
	}
}

template<typename genType>
bool GenStack<genType>::pop(genType &obj)
{
	if(top >= 0){
		obj = genStackPtr[top--];
		return true;
	}
	else {
		cout << "ATTEMPT TO POP EMPTY STACK" << endl;
		return false;
	}
}

template<typename genType>
genType GenStack<genType>::peek(){
	if(this->top <= this->sizeStack-1 && !empty()){
		return genStackPtr[top];
	}
	else{
		cout << "CANNOT PEEK STACK" << endl;
		genType gen;
		return gen;
	}
}

template<typename genType>
bool GenStack<genType>::empty(){
	if(top < 0){
		return true;
	}
	else{
		return false;
	}
}

template<typename genType>
int GenStack<genType>::getSize(){
	return this->sizeStack;
}

template<typename genType>
void GenStack<genType>::resize(){
	cout << "RESIZING STACK" << endl;
	this->sizeStack *= 2;
	genType *gsClonePtr = new genType[this->sizeStack];
	for(int i = 0; i < sizeStack/2; ++i){
		gsClonePtr[i] = genStackPtr[i];
	}
	genStackPtr = gsClonePtr;
}

template class GenStack<char>;