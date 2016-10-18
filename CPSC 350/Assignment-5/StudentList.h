#include "StudentNode.h"
#include "BST.h"
#include "Student.h"

class StudentList	// template class of a doubly linked list, refined to be used as a list of StudentNodes
{
	//private:

	public:
		StudentList();
		~StudentList();
		void insertFront(StudentNode &object); // take in parameters for student object in StudentNode
		StudentNode removeFront(BST<Student> &object);
		StudentNode removeBack();
		//void insertBack(int m_tick,int m_time);	// take in parameters for student object in StudentNode
		bool isEmpty();	// check if list is empty or not
		//StudentStudentNode front(); // return the element at head position
	unsigned int size; // for the size of the list
	StudentNode *head;
	StudentNode *back;
};

StudentList::StudentList() // initializing 
{
	size = 0;
	head = NULL;
	back = NULL;
}

 
StudentList::~StudentList(){}

 
bool StudentList::isEmpty()
{
	return (size == 0);
}

/*  
T List<T>::front() // return whatever head points to
{
	T *StudentStudentNode = head;
	return *StudentStudentNode;
}*/


  
void StudentList::insertFront(StudentNode &object) // add element to front of list
{
	StudentNode *Node = &object; // parameters for student object
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


 
StudentNode StudentList::removeFront(BST<Student> &object) // remove element from front
{
	StudentNode *temp = head; // take current head value
	if (head->next == NULL) // if only one
		back = NULL;
	else // otherwise, deal with pointers
	{
		head = head->next;
		head->prev = NULL;
	}
	--size;
	
	//object.root = NULL;
	//temp->StudentTree.copyf(object, temp->StudentTree.root);
	object = temp->studentTree;
	temp->studentTree.printTree();
	
	return *temp;
}


/*
void List<T>::insertBack(int m_tick,int m_time) // insert element to back of list
{
	T *StudentNode = new T(m_tick,m_time); // parameters for student object
	if (size == 0)
		head = StudentNode;
	else // if size not 0, deal with pointers
	{
		back->next = StudentNode;
		StudentNode->prev = back;
	}
	back = StudentNode;
	++size;
}*/


 
StudentNode StudentList::removeBack() // remove element from back of list
{
	StudentNode *temp = back; // take current last value
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