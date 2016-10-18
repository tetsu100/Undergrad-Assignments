#ifndef FACULTY_H
#define FACULTY_H
#include <iostream>
#include <string>

using namespace std;

class faculty
{
public:
	faculty();
	~faculty();
	int facultyID;
	string name;
	string level;
	string department;
	//List<int> adviseeIDs; //syntax??
	//overloaded operator methods
	void addFaculty();
	void deleteFaculty();
};
#endif