#include "faculty.h"
#include <iostream>
#include <string>

using namespace std;

faculty::faculty()
{
	int facultyID;
	string name;
	string level;
	string department;
	//List<int> adviseeIDs; //syntax??
}
faculty::~faculty()
{

}
int faculty::getFacultyID()
{
	return facultyID;
}
void faculty::setFacultyID(int n)
{
	facultyID = n;
}
string faculty::getFacultyName()
{
	return name;
}
void faculty::setFacultyName(string n)
{
	name = n;
}
string faculty::getFacultyLevel()
{
	return level;
}
void faculty::setFacultyLevel(string n)
{
	level = n;
}
string faculty::getFacultyDpt()
{
	return department;
}
void faculty::setFacultyDpt(string n)
{
	department = n;
}
bool faculty::operator <(const faculty& f)
{
	if(facultyID < f.facultyID)
	{
		cout << "I am les than, booo :(" << endl;
		return true;
	}
	return false;
}
bool faculty::operator >(const faculty& f)
{
	if(facultyID > f.facultyID)
	{
		cout << "I am greater than, WOO!" << endl;
		return true;
	}
	return false;
}
bool faculty::operator ==(const faculty& f)
{
	if(facultyID == f.facultyID)
	{
		return true;
	}
	return false;
}
ostream& operator<<(ostream&os, faculty f)
{
	os <<"FACULTY: "<< s.getFacultyName() << "\n" << "ID number: "<< s.getFacultyID() << "\n" << "Department: "<< s.getFacultyDpt() << "\n"<< "Level: "<< s.getFacultyLevel() << endl;
	return os;
}