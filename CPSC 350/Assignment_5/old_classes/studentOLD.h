#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <string>

using namespace std;

class student
{
public:
	student();
	student(string serial);
	~student();
	int getStudentID();
	void setStudentID(int n);
	int getStudentAdvisor();
	void setStudentAdvisor(int n);
	double getGPA();
	void setGPA(double g);
	string getName();
	void setName(string s);
	string getLevel();
	void setLevel(string s);
	string getMajor();
	void setMajor(string s);
	void addStudent();
	void deleteStudent();
	string toSerial();
	
private:
	int studentID;
	int student_advisor;
	double gpa;
	string name;
	string level;
	string major;
	//overload operator methods
	

};
#endif