#ifndef FACULTY_H
#define FACULTY_H
#include <string>
#include "Student.h"

using namespace std;
class Faculty
{

private:
	int facultyID;
	string name;
	string level;
	int arraySize;
	string department;
	Student *adviseeList;
	int arrayCount;

public:
	Faculty();
	Faculty(int id, string m_name, string m_level, string m_dept);
	~Faculty();
	void printDetails();
	void addAdvisee(Student std);
	void removeAdvisee(Student std);
	void listAdvisees();
	friend bool operator < (Faculty f1, Faculty f2);
	friend bool operator > (Faculty f1, Faculty f2);
	friend bool operator == (Faculty f1, Faculty f2);
	friend bool operator != (Faculty f1, Faculty f2);

};
#endif