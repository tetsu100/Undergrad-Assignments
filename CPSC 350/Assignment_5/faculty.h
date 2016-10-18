#ifndef FACULTY_H
#define FACULTY_H
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class faculty
{
public:
	faculty();
	~faculty();
	faculty(string serial);
	string toSerial();
	int getFacultyID();
	void addAdvisee(int n);
	void setFacultyID(int n);
	string getFacultyName();
	void setFacultyName(string n);
	vector<int> getAdvisees();
	void setAdvisees(vector<int> tmp);
	string getFacultyLevel();
	void setFacultyLevel(string n);
	string getFacultyDpt();
	void setFacultyDpt(string n);
	void addFaculty();
	void deleteFaculty();
	void removeAdvisee(int n);
	bool operator <(const faculty& f);
	bool operator >(const faculty& f);
	bool operator ==(const faculty& f);
	bool operator !=(const faculty& f);
	friend ostream &operator<<(ostream &os, faculty f);
private:
	int facultyID;
	string name;
	string level;
	string department;
	vector<int> studentIDs;
};
#endif