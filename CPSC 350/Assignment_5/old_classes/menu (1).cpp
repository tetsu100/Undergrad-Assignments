#include "menu.h"
#include "binaryST.h"
#include "student.h"
#include "GenStack.h"
#include "faculty.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

menu::menu()
{
	running = false;
	commitFaculty = 22;
	commitStudent = 33;
	commitBoth = 44;
	changeLogIterator = new GenStack<int>();
	changeLog = new GenStack<string>();
	
	studentBST = new binaryST<student>();
	facultyBST = new binaryST<faculty>();
	
}
menu::~menu()
{
	//delete studentBST;
	//delete facultyBST;
	//delete changeLogIterator;
	//delete changeLog;
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
				
				if(token.length() > 3){
					faculty tmp(token);
					facultyBST->insert(tmp);
				}
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
				
				if(token.length() > 3){
					student tmp(token);
					studentBST->insert(tmp);
				}
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
		string tmpSerial = "NULL";
		tmpSerial = facultyBST->serialBST;
		if(tmpSerial != "NULL" && tmpSerial.length() > 3 && tmpSerial != "UNSERIALIZED"){
			outFaculty << tmpSerial;
		}
		
		studentBST->serialize();
		tmpSerial = "NULL";
		tmpSerial = studentBST->serialBST;
		if(tmpSerial != "NULL" && tmpSerial.length() > 3 && tmpSerial != "UNSERIALIZED"){
			outStudent << tmpSerial;
		}
		
		outFaculty.close();
		outStudent.close(); 
	} 
}

void menu::activate(){
	
	running = true;
	load();
	
	while(running){
		try {
			printMenu();
		}
		catch (...) {
			cout << "ERROR PRINTING MENU" << endl;
		}
	}
	cout << "\nSAVING AND EXITING" << endl;
}

void menu::rollBack(){
	cout << "REVERTING CHANGES" << endl;
	int whichTree = -1;
	changeLogIterator->pop(whichTree);
	switch(whichTree){
		case -1:
			cout << "No changes to Roll-back!" << endl;
			break;
		case 22:
			try{
				facultyBST = new binaryST<faculty>();
				string delimiter = "#";
				string s = "";
				changeLog->pop(s);
				int i = 0;

				size_t pos = 0;
				string token;
				while ((pos = s.find(delimiter)) != string::npos) {
					token = s.substr(0, pos);
					s.erase(0, pos + delimiter.length());
					
					if(token.length() > 3){
						faculty tmp(token);
						facultyBST->insert(tmp);
					}
				}
				if(s.length() > 3){
					faculty tmp(s);
					facultyBST->insert(tmp);
				}
			}
			catch(...){
				cout << "ERROR LOADING NODE INTO DATABASE" << endl;
			}
			break;
		case 33:
			try{
				studentBST = new binaryST<student>();
				string delimiter = "#";
				string s = "";
				changeLog->pop(s);
				int i = 0;

				size_t pos = 0;
				string token;
				while ((pos = s.find(delimiter)) != string::npos) {
					token = s.substr(0, pos);
					s.erase(0, pos + delimiter.length());
					
					if(token.length() > 3){
						student tmp(token);
						studentBST->insert(tmp);
					}
				}
				if(s.length() > 3){
					student tmp(s);
					studentBST->insert(tmp);
				}
			}
			catch(...){
				cout << "ERROR LOADING NODE INTO DATABASE" << endl;
			}
			break;
		case 44:
			studentBST = new binaryST<student>();
			facultyBST = new binaryST<faculty>();
			try{
				string delimiter = "#";
				string s = "";
				changeLog->pop(s);
				int i = 0;

				size_t pos = 0;
				string token;
				while ((pos = s.find(delimiter)) != string::npos) {
					token = s.substr(0, pos);
					s.erase(0, pos + delimiter.length());
					
					if(token.length() > 3){
						faculty tmp(token);
						facultyBST->insert(tmp);
					}
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
				string s = "";
				changeLog->pop(s);
				int i = 0;

				size_t pos = 0;
				string token;
				while ((pos = s.find(delimiter)) != string::npos) {
					token = s.substr(0, pos);
					s.erase(0, pos + delimiter.length());
					
					if(token.length() > 3){
						student tmp(token);
						studentBST->insert(tmp);
					}
				}
				if(s.length() > 3){
					student tmp(s);
					studentBST->insert(tmp);
				}
			}
			catch(...){
				cout << "ERROR LOADING NODE INTO DATABASE" << endl;
			}
			break;
		default:
			cout << "Error reverting changes." << endl;
	}
}

void menu::commitChange(int whichTree){
	if(whichTree == 22 || whichTree == 44){
		facultyBST->serialize();
		cout << facultyBST->serialBST << "   OKOKO " << endl;
		changeLog->push(facultyBST->serialBST);
	}
	if(whichTree == 33 || whichTree == 44){
		studentBST->serialize();
		changeLog->push(studentBST->serialBST);
	}
	changeLogIterator->push(whichTree);
	cout << "CHANGES COMMITTED" << endl;
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
	
	
	/*
	student mee;
	mee.setName("ann");
	mee.setStudentID(12345);
	mee.setGPA(3.4);
	mee.setLevel("Sophomore");
	mee.setMajor("Computer Science bc im crazy");
	mee.setStudentAdvisor(5677);
	studentBST->insert(mee);

	student me2;
	me2.setName("don");
	me2.setStudentID(23456);
	me2.setGPA(3.4);
	me2.setLevel("Junior");
	me2.setMajor("Computer Science bc im smart");
	me2.setStudentAdvisor(5678);
	studentBST->insert(me2);

	faculty fac;
	fac.setFacultyName("Dr. hooohaw");
	fac.setFacultyID(5678);
	fac.setFacultyLevel("high");
	fac.setFacultyDpt("comp sci bishh");
	facultyBST->insert(fac);
	
	faculty testboy;
	facultyBST->insert(testboy); */

	int input;
	cin >> input;
	while(cin.fail()) {
        cout << "Integers only please." << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> input;
    }
	switch(input)
	{
		case 1:
		{
			studentBST->printTree();
			break;
		}
		case 2:
		{
			facultyBST->printTree(); 
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
			cout << "Enter faculty ID number: ";
			int id;
			cin >> id;
			faculty tmp;
			tmp.setFacultyID(id);
			tmp = facultyBST->searchData(tmp);
			cout << "\n" << tmp.getFacultyName() << "'s advisees include: " << endl;
			try{
				vector<int> tmpAdvisees = tmp.getAdvisees();
				cout << tmpAdvisees.size() << endl;
				for(vector<int>::iterator it = tmpAdvisees.begin(); it != tmpAdvisees.end(); ++it) {
					if(*it >=  0){
						student tmp2;
						tmp2.setStudentID(*it);
						tmp2 = studentBST->searchData(tmp2);
						cout << tmp2 << endl;
					}
				}
			}
			catch (...) { cout << "ERROR PRINTING STUDENTS" << endl; }
			break;
		}
		case 7:
		{
			commitChange(commitStudent);
			string n;
			cout << "Enter student's name: ";
			cin.ignore();
			getline(cin, n);
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
			cin.ignore();
			getline(cin, l);
			newStudent.setLevel(l);
			cout << "Enter student's major: ";
			string m;
			//cin.ignore();
			getline(cin, m);
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
			studentBST->remove(tmp);
			break;
		}
		case 9:
		{
			commitChange(commitBoth);
			cout << "Enter faculty member's name: ";
			string n;
			cin.ignore();
			getline(cin, n);
			faculty newFac;
			newFac.setFacultyName(n);
			cout << "Enter faculty member's ID number: ";
			int id;
			cin >> id;
			newFac.setFacultyID(id);
			cout << "Enter faculty member's level: ";
			string l;
			cin.ignore();
			getline(cin, l);
			newFac.setFacultyLevel(l);
			cout << "Enter faculty member's department: ";
			string m;
			cin.ignore();
			getline(cin, m);
			newFac.setFacultyDpt(m);
			cout << "Enter advisee ID number: ";
			int advID;
			cin >> advID;
			vector<int> supertTmpAdvisees;
			while(!cin.fail()) {
		       	cout << "Enter advisee ID number (enter '-1' to quit): ";
		        cin.clear();
		        cin.ignore(256,'\n');
		        cin >> advID;

		        if(advID == -1){
		        	break;
		        }
		        //check if student exists
		        student tmp;
		        tmp.setStudentID(advID);
				bool studentExists = studentBST->search(tmp);
				if(!studentExists)
				{
					cout << "Enter valid ID number. " << endl;
				}
				supertTmpAdvisees.push_back(advID);
   			}
   			newFac.setAdvisees(supertTmpAdvisees);
		
			facultyBST->insert(newFac);
			cout << "\n" << newFac.getFacultyName() << " has been added!\n" << endl;
			break;
		}
		case 10:
		{
			commitChange(commitBoth);
			cout << "Enter the ID number of the faculty member you would like to delete: ";
			int id;
			cin >> id;
			faculty tmp;
			tmp.setFacultyID(id);
			tmp = facultyBST->searchData(tmp);
			facultyBST->remove(tmp); 
			break;
		}
		case 11:
		{
			commitChange(commitBoth);
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
			tmp2.addAdvisee(id);
			cout << "\n" << tmp.getName() << "'s new advisor is " << tmp2.getFacultyName() << ".\n" << endl;
			break;
		}
		case 12:
		{
			break;
		}
		case 13:
		{
			rollBack();
			break;
		}
		case 14:
		{
			save();
			running = false;
			break;
		}
		default:
		{
			cout << "Try again!" << endl;
		}
	}
}