#include "menu.h"
#include "binaryST.h"
#include "student.h"
#include "faculty.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

menu::menu()
{
	
}
menu::~menu()
{

}
void menu::load(){
	ifstream inFaculty;
	ifstream inStudent;
	inFaculty.open("masterFaculty.txt");
	inStudent.open("masterStudent.txt");
	
	if ( inFaculty.fail() || inStudent.fail() ) {
		cout <<"ERROR LOADING DATABASE" << endl;
	}
	else{
		try{
			string delimiter = "#";
			string s( (std::istreambuf_iterator<char>(inFaculty) ),	
                       (std::istreambuf_iterator<char>()    ) );
			int i = 0;

			size_t pos = 0;
			string token;
			while ((pos = s.find(delimiter)) != string::npos) {
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());
				
				faculty tmp(token);
				facultyBST->insert(tmp);
			}
			if(s.length() > 3){
				faculty tmp(s);
				facultyBST->insert(tmp);
			}
		}
		catch(...){
			cout << "ERROR LOADING NODE INTO DATABASE" << endl;
		}
		try{
			string delimiter = "#";
			string s( (std::istreambuf_iterator<char>(inStudent) ),	
                       (std::istreambuf_iterator<char>()    ) );
			int i = 0;

			size_t pos = 0;
			string token;
			while ((pos = s.find(delimiter)) != string::npos) {
				token = s.substr(0, pos);
				s.erase(0, pos + delimiter.length());
				
				student tmp(token);
				studentBST->insert(tmp);
			}
			if(s.length() > 3){
				student tmp(s);
				studentBST->insert(tmp);
			}
		}
		catch(...){
			cout << "ERROR LOADING NODE INTO DATABASE" << endl;
		}
		inFaculty.close();
		inStudent.close();
	}
}
void menu::save(){
	ofstream outFaculty;
	ofstream outStudent;
	outFaculty.open("masterFaculty.txt");
	outStudent.open("masterStudent.txt");
	
	if ( outFaculty.fail() || outStudent.fail() ) {
		cout <<"ERROR SAVING DATABASE" << endl;
	}
	else{
		facultyBST->serialize();
		outFaculty << facultyBST->serialBST;
		studentBST->serialize();
		cout <<studentBST->serialBST << endl;
		outStudent << studentBST->serialBST;
		
		outFaculty.close();
		outStudent.close();
	}
}
void menu::printMenu()
{
	cout<< "Menu: " << endl;
	cout << "	(1) Print all students and their information" << endl;
	cout << "	(2) Print all faculty and their information" << endl;
	cout << " 	(3) Find a student by ID number" << endl;
	cout << "	(4) Find a faculty member by ID number" << endl;
	cout << "	(5) Find a student's faculty advisor" << endl;
	cout << "	(6) Find all faculty advisees" << endl;
	cout << "	(7) Add new student" << endl;
	cout << "	(8) Delete student" << endl;
	cout << "	(9) Add faculty member" << endl;
	cout << "	(10) Delete faculty member" << endl;
	cout << "	(11) Change student's advisor to new faculty member" << endl;
	cout << "	(12) Remove advisee from faculty member" << endl;
	cout << "	(13) Rollback" << endl;
	cout << "	(14) Exit" << endl;

	studentBST = new binaryST<student>();
	facultyBST = new binaryST<faculty>();
	
	load();

	student mee;
	mee.setName("me");
	mee.setStudentID(12345);
	mee.setGPA(3.4);
	mee.setLevel("Sophomore");
	mee.setMajor("Computer Science bc im crazy");
	mee.setStudentAdvisor(5678);
	studentBST->insert(mee);



	int input;
	cin >> input;
	switch(input)
	{
		case 1:
		{
			studentBST->printTree(); //segmentation fault
			cout << "ding dong" << endl;
			break;
		}
		case 2:
		{
			facultyBST->printTree(); //seg fault
			break;
		}
		case 3:
		{
			cout << "Enter student ID number: ";
			int id;
			cin >> id;
			student tmp;
			tmp.setStudentID(id);
			tmp = studentBST->searchData(tmp);
			cout << tmp << endl;
			break;
		}
		case 4:
		{
			cout << "Enter faculty ID number: ";
			int id;
			cin >> id;
			faculty tmp;
			tmp.setFacultyID(id);
			tmp = facultyBST->searchData(tmp);
			cout << tmp << endl;
			break;
		}
		case 5:
		{
			cout << "Enter student ID number: ";
			int id;
			cin >> id;
			student tmp;
			tmp.setStudentID(id);
			tmp = studentBST->searchData(tmp);
			int facID = tmp.getStudentAdvisor();
			faculty tmp2;
			tmp2.setFacultyID(facID);
			tmp2 = facultyBST->searchData(tmp2);
			cout << tmp2 << endl;
			break;
		}
		case 6:
		{
			break;
		}
		case 7:
		{
			cout << "Enter student's name: ";
			string n;
			cin >> n;
			student newStudent;
			newStudent.setName(n);
			cout << "Enter student's ID number: ";
			int id;
			cin >> id;
			newStudent.setStudentID(id);
			cout << "Enter student's GPA: ";
			double gpa;
			cin >> gpa;
			newStudent.setGPA(gpa);
			cout << "Enter student's level: ";
			string l;
			cin >> l;
			newStudent.setLevel(l);
			cout << "Enter student's major: ";
			string m;
			cin >> m;
			newStudent.setMajor(m);
			cout << "Enter student's advisor's ID number: ";
			int adv;
			cin >> adv;
			newStudent.setStudentAdvisor(adv);
			studentBST->insert(newStudent);
			cout << "\n" << newStudent.getName() << " has been added!\n" << endl;
			break;
		}
		case 8:
		{
			cout << "Enter the ID number of the student you would like to delete: ";
			int id;
			cin >> id;
			student tmp;
			tmp.setStudentID(id);
			tmp = studentBST->searchData(tmp);
			//studentBST->remove(tmp); //baaaaaddddddd
			break;
		}
		case 9:
		{
			cout << "Enter faculty member's name: ";
			string n;
			cin >> n;
			faculty newFac;
			newFac.setFacultyName(n);
			cout << "Enter faculty member's ID number: ";
			int id;
			cin >> id;
			newFac.setFacultyID(id);
			cout << "Enter faculty member's level: ";
			string l;
			cin >> l;
			newFac.setFacultyLevel(l);
			cout << "Enter faculty member's department: ";
			string m;
			cin >> m;
			newFac.setFacultyDpt(m);
			facultyBST->insert(newFac);
			cout << "\n" << newFac.getFacultyName() << " has been added!\n" << endl;
			break;
		}
		case 10:
		{
			cout << "Enter the ID number of the faculty member you would like to delete: ";
			int id;
			cin >> id;
			faculty tmp;
			tmp.setFacultyID(id);
			tmp = facultyBST->searchData(tmp);
			//facultyBST->remove(tmp); BADDDDD
			break;
		}
		case 11:
		{
			cout << "Enter student's ID number: ";
			int id;
			cin >> id;
			student tmp;
			tmp.setStudentID(id);
			tmp = studentBST->searchData(tmp);
			cout << "Enter the new student advisor's ID number: ";
			int facID;
			cin >> facID;
			tmp.setStudentAdvisor(facID);
			faculty tmp2;
			tmp2.setFacultyID(facID);
			tmp2 = facultyBST->searchData(tmp2);
			cout << "\n" << tmp.getName() << "'s new advisor is " << tmp2.getFacultyName() << ".\n" << endl;
			//not done???
			break;
		}
		case 12:
		{

		}
		case 13:
		{

		}
		case 14:
		{
			save();
			exit(0);
		}
		default:
		{
			cout << "Try again!" << endl;
		}
	}
}