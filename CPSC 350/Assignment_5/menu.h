#ifndef MENU_H
#define MENU_H
#include "binaryST.h"
#include "student.h"
#include "faculty.h"
#include <iostream>
#include <string>
#include "GenStack.h"

using namespace std;

class menu
{
public:
	menu();
	~menu();
	void printMenu();
	void save();
	void load();
	void activate();
	void rollBack();
	void commitChange(int whichTree);
	//print students & faculty
	//data base object
private:
	int input;
	int commitFaculty;
	int commitStudent;
	int commitBoth;
	bool running;
	binaryST<student>* studentBST;
	binaryST<faculty>* facultyBST;
	GenStack<string>* changeLog;
	GenStack<int>* changeLogIterator;
};
#endif
