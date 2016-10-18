#ifndef FACULTY_H
#define FACULTY_H
#include <iostream>
#include <string>

using namespace std;

class faculty
{
public:
	faculty();
	faculty(string serial);
	string toSerial();
	~faculty();
	int getFacultyID();
	void setFacultyID(int n);
	string getFacultyName();
	void setFacultyName(string n);
	string getFacultyLevel();
	void setFacultyLevel(string n);
	string getFacultyDpt();
	void setFacultyDpt(string n);
	void addFaculty();
	void deleteFaculty();
	bool operator <(const faculty& f);
	bool operator >(const faculty& f);
	bool operator ==(const faculty& f);
	friend ostream &operator<<(ostream &os, faculty f);
private:
	int facultyID;
	string name;
	string level;
	string department;
};
#endif