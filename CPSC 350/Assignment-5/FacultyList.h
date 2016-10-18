#include "FacultyNode.h"
#include "BST.h"
#include "Faculty.h"

class FacultyList	// template class of a doubly linked list, refined to be used as a list of FacultyNodes
{
	//private:

	public:
		FacultyList();
		~FacultyList();
		void insertFront(FacultyNode &object); // take in parameters for student object in FacultyNode
		FacultyNode removeFront(BST<Faculty> &object);
		FacultyNode removeBack();
		//void insertBack(int m_tick,int m_time);	// take in parameters for student object in FacultyNode
		bool isEmpty();	// check if list is empty or not
		//FacultyFacultyNode front(); // return the element at head position
	unsigned int size; // for the size of the list
	FacultyNode *head;
	FacultyNode *back;
};

FacultyList::FacultyList() // initializing 
{
	size = 0;
	head = NULL;
	back = NULL;
}

 
FacultyList::~FacultyList(){}

 
bool FacultyList::isEmpty()
{
	return (size == 0);
}

/*  
T List<T>::front() // return whatever head points to
{
	T *FacultyFacultyNode = head;
	return *FacultyFacultyNode;
}*/


  
void FacultyList::insertFront(FacultyNode &object) // add element to front of list
{
	FacultyNode *Node = &object; // parameters for student object
	if (size  == 0) // if first element
	{
		back = Node;
	}
	else // if not, set up pointers respectively
	{
		head->prev = Node;
		Node->next = head;
	}

	head = Node;
	++size; // increment size
}


 
FacultyNode FacultyList::removeFront(BST<Faculty> &object) // remove element from front
{
	FacultyNode *temp = head; // take current head value
	if (head->next == NULL) // if only one
		back = NULL;
	else // otherwise, deal with pointers
	{
		head = head->next;
		head->prev = NULL;
	}
	--size;
	
	//object.root = NULL;
	//temp->facultyTree.copyf(object, temp->facultyTree.root);
	object = temp->facultyTree;
	temp->facultyTree.printTree();
	
	return *temp;
}


/*
void List<T>::insertBack(int m_tick,int m_time) // insert element to back of list
{
	T *FacultyNode = new T(m_tick,m_time); // parameters for student object
	if (size == 0)
		head = FacultyNode;
	else // if size not 0, deal with pointers
	{
		back->next = FacultyNode;
		FacultyNode->prev = back;
	}
	back = FacultyNode;
	++size;
}*/


 
FacultyNode FacultyList::removeBack() // remove element from back of list
{
	FacultyNode *temp = back; // take current last value
	if (back->prev = NULL) // if only element
		head = NULL;
	else // otherwise, set pointers
	{
		back = head->prev;
		back->next = NULL;
	}
	--size;
	return *temp; // return value held by last element
}