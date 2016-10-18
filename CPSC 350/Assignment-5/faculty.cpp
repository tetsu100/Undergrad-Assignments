#include "Faculty.h"
#include <iostream>

Faculty::Faculty(){}

Faculty::~Faculty(){}

Faculty::Faculty(int id, string m_name, string m_level, string m_dept)
{
	arraySize = 50;
	arrayCount = 0;
	facultyID = id;
	name = m_name;
	level = m_level;
	department = m_dept;
	adviseeList = new Student[arraySize];
}

void Faculty::printDetails()
{
	cout << "ID:" << facultyID << endl;
	cout << "Name:" << name << endl;
	cout << "Level:" << level << endl;
	cout << "Department:" << department << endl;
}

void Faculty::listAdvisees()
{
	for(int i = 0;i<arrayCount;i++)
	{
		adviseeList[i].printDetails();
	}
}


void Faculty::addAdvisee(Student std)
{
	adviseeList[arrayCount] = std;
	arrayCount++;
}

void Faculty::removeAdvisee(Student std)
{
	bool studentFound = false;
	for(int i = 0; i < arrayCount; ++i)
	{
		if(adviseeList[i].getStudentID() == std.getStudentID())
		{
			studentFound = true;
		}
		if(studentFound)
		{
			adviseeList[i] = adviseeList[i+1];
		}
	}
	arrayCount--;
}


bool operator > (Faculty s1, Faculty s2)
{
	return (s1.facultyID > s2.facultyID);
}

bool operator < (Faculty s1, Faculty s2)
{
	return (s1.facultyID < s2.facultyID);
}

bool operator == (Faculty s1, Faculty s2)
{
	return (s1.facultyID == s2.facultyID);
}

bool operator != (Faculty s1, Faculty s2)
{
	return (s1.facultyID != s2.facultyID);
}