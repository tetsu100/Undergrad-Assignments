#include "faculty.h"
#include "binaryST.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <vector>

using namespace std;

faculty::faculty()
{
	facultyID = 54321;
	name = "Juniper Ya'Noodle";
	level = "Professor";
	department = "Dance History";
	studentIDs.push_back(11111);
	studentIDs.push_back(22222);
	studentIDs.push_back(33333);
}
faculty::faculty(string serial)
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
				department = token;
			break;
			case 2:
				facultyID = atoi(token.c_str());
			break;
			case 3:
				level =  token;
			break;
			default:
			cout << "Something went wrong deserializing students" << endl;
		}
		i++;
	}
	string studIDdelim = ":";
	while ((pos = s.find(studIDdelim)) != string::npos) {
		token = s.substr(0, pos);
		s.erase(0, pos + studIDdelim.length());
		studentIDs.push_back(atoi(token.c_str()));
	}
	//studentIDs.push_back(atoi(s.c_str()));
}
string faculty::toSerial()
{
	stringstream sstr;
    sstr << "#" << this->getFacultyName() << "~" << this->getFacultyDpt() << "~" << this->getFacultyID() <<
		"~" << this->getFacultyLevel() << "~";
		
	for(vector<int>::iterator it = studentIDs.begin(); it != studentIDs.end(); ++it) {
		if(*it >  0){
			sstr << *it << ":";
		}
	}
	string tmp = sstr.str();
    if (tmp.at(1) == '~'){
		return "";
	}
	return tmp;
}
faculty::~faculty()
{

}
vector<int> faculty::getAdvisees()
{
	return studentIDs;
}
void faculty::removeAdvisee(int n)
{
	size_t id_index;
	for(size_t i = 0; i < studentIDs.size(); ++i)
	{
		if(studentIDs[i] == n){
			id_index = i;
		}
	}
	studentIDs.erase(studentIDs.begin() + id_index);
}
void faculty::setAdvisees(vector<int> tmp){
	studentIDs = tmp;
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
void faculty::addAdvisee(int n){
	studentIDs.push_back(n);
}
bool faculty::operator ==(const faculty& f)
{
	if(facultyID == f.facultyID)
	{
		return true;
	}
	return false;
}
bool faculty::operator !=(const faculty& f)
{
	if(facultyID != f.facultyID)
	{
		return true;
	}
	return false;
}
ostream& operator<<(ostream&os, faculty f)
{
	os <<"FACULTY: "<< f.getFacultyName() << "\n" << "ID number: "<< f.getFacultyID() << "\n" << "Department: "<< f.getFacultyDpt() << "\n"<< "Level: "<< f.getFacultyLevel() << endl;
	return os;
}