#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;
class Student
{

private:
	int studentID;
	string name;
	string year;
	string major;
	double GPA;
	int advisorID;

public:
	Student();
	Student(int id, string m_name, string m_year, string m_major, double gpa, int aid);
	~Student();
	void printDetails();
	int getAdvisorID();
	int getStudentID();
	void setAdvisorID(int advisorID);
	friend bool operator < (Student s1, Student s2);
	friend bool operator > (Student s1, Student s2);
	friend bool operator == (Student s1, Student s2);
	friend bool operator != (Student s1, Student s2);

};
#endif