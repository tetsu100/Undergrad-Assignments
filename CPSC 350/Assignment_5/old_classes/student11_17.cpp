#include "binaryST.h"
#include "student.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

student::student()
{
	studentID = 12345;
	student_advisor = 54321; //"Reynaldino Jalpinasty";
	gpa = 3.1;
	name = "Booboo Man-pro";
	level = "Junior";
	major = "Communications";
}
student::student(string serial)
{
	string delimiter = "~";
	string s = serial;
	int i = 0;

	size_t pos = 0;
	string token;
	while ((pos = s.find(delimiter)) != string::npos) {
		token = s.substr(0, pos);
		s.erase(0, pos + delimiter.length());
		switch(i){
			case 0:
				name = token;
			break;
			case 1:
				level = token;
			break;
			case 2:
				major = token;
			break;
			case 3:
				gpa =  atof(token.c_str());
			break;
			case 4:
				student_advisor =  atoi(token.c_str());
			break;
			default:
			cout << "Something went wrong deserializing students" << endl;
		}
		i++;
	}
	studentID =  atoi(s.c_str());
}
string student::toSerial()
{
	stringstream sstr;
    sstr << "#" << this->getName() << "~" << this->getLevel() << "~" << this->getMajor() <<
		"~" << this->getGPA() << "~" << this->getStudentAdvisor() << "~" << this->getStudentID();
    
	string tmp = sstr.str();
    if (tmp.at(1) == '~'){
		return "";
	}
	return tmp;
}
student::~student()
{

}
int student::getStudentID()
{
	return studentID;
}
void student::setStudentID(int n)
{
	studentID = n;
}
int student::getStudentAdvisor()
{
	return student_advisor;
}
void student::setStudentAdvisor(int n)
{
	student_advisor = n;
}
double student::getGPA()
{
	return gpa;
}
void student::setGPA(double g)
{
	gpa = g;
}
string student::getName()
{
	return name;
}
void student::setName(string s)
{
	name = s;
}
string student::getLevel()
{
	return level;
}
void student::setLevel(string s)
{
	level = s;
}
string student::getMajor()
{
	return major;
}
void student::setMajor(string s)
{
	major = s;
}
bool student::operator <(const student& s)
{
	if(studentID < s.studentID)
	{
		cout << "I am les than, booo :(" << endl;
		return true;
	}
	return false;
}
bool student::operator >(const student& s)
{
	if(studentID > s.studentID)
	{
		cout << "I am greater than, WOO!" << endl;
		return true;
	}
	return false;
}
bool student::operator ==(const student& s)
{
	if(studentID == s.studentID)
	{
		return true;
	}
	return false;
}
ostream& operator<<(ostream&os, student s)
{
	os <<"STUDENT: "<< s.getName() << "\n" << "ID number: "<< s.getStudentID() << "\n" << "GPA: "<< s.getGPA() << "\n"<< "Level: "<< s.getLevel() << "\n" << "Major: "<< s.getMajor() << "\n"<<"Advisor: " << s.getStudentAdvisor() << "\n" << endl;
	return os;
}
//search for student by id number --> create temp student and find id in tree
//user input 