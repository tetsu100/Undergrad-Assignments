#ifndef STUDENTNODE_H
#define STUDENTNODE_H

#include "Student.h"
#include "BST.h"
#include <iostream>


using namespace std;

class StudentNode
{
	public:
	BST<Student> studentTree; // contains a student object
	StudentNode *next; // a prev
	StudentNode *prev; // and next pointer for a doubly linked list
	StudentNode();
	//StudentNode(); // takes initial values for student object
	~StudentNode();
};
#endif