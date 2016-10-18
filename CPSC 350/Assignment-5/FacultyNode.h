#ifndef FACULTYNODE_H
#define FACULTYNODE_H

#include "Faculty.h"
#include "BST.h"
#include <iostream>


using namespace std;

class FacultyNode
{
	public:
	BST<Faculty> facultyTree; // contains a Faculty object
	FacultyNode *next; // a prev
	FacultyNode *prev; // and next pointer for a doubly linked list
	FacultyNode();
	//FacultyNode(); // takes initial values for Faculty object
	~FacultyNode();
};
#endif