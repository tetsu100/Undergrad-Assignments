#include "Student.h"
#include <iostream>

Student::~Student()
{}

Student::Student()
{
	studentID = -1;
}

Student::Student(int id, string m_name, string m_year, string m_major, double gpa, int aid)
{
	studentID = id;
	name = m_name;
	year = m_year;
	major = m_major;
	GPA = gpa;
	advisorID = aid;
}

void Student::printDetails()
{
	cout << "ID:" << studentID << endl;
	cout << "Name:" << name << endl;
	cout << "Year:" << year << endl;
	cout << "Major:" << major << endl;
	cout << "GPA:" << GPA << endl;
	cout << "Advisor ID:" << advisorID << endl;
}



int Student::getAdvisorID()
{
	return advisorID;
}

int Student::getStudentID()
{
	return studentID;
}

void Student::setAdvisorID(int advisorID)
{
	this->advisorID = advisorID;
}


bool operator > (Student s1, Student s2)
{
	return (s1.studentID > s2.studentID);
}


bool operator < (Student s1, Student s2)
{
	return (s1.studentID < s2.studentID);
}


bool operator == (Student s1, Student s2)
{
	return (s1.studentID == s2.studentID);
}

bool operator != (Student s1, Student s2)
{
	return (s1.studentID != s2.studentID);
}