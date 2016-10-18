#include "BST.h"
#include "Faculty.h"
#include "Student.h"
#include <string>
#include <cstdlib>
#include <fstream>
#include "StudentList.h"
#include "FacultyList.h"
#include "FacultyNode.h"
#include "StudentNode.h"

using namespace std;

int userInput = 0;

BST<Student> masterStudent;
BST<Faculty> masterFaculty;
StudentList studentList;
FacultyList facultyList;
FacultyNode *fNode;
StudentNode *sNode;

void intro();
void printStudentsInfo();
void printFacultyInfo();
void findStudent();
void findFaculty();
void findAdvisor();
void printAdvisees();
void addStudent();
void deleteStudent();
void addFaculty();
void deleteFaculty();
void changeStudentAdvisor();
void removeAdvisee();
void snapshot();
void rollback();
void exit();


int main()
{

	//Student hamza(3,"Hamza","Sophomore","CompSci",3.9,4);
	//masterStudent.insert(hamza);
	//Faculty professor(4,"fname","prof","compsci");
	//masterFaculty.insert(professor);

	while(userInput !=  14)
	{
		intro();
		cin >> userInput;
		switch(userInput)
		{
			case 1:
				printStudentsInfo();
				break;
			case 2:
				printFacultyInfo();
				break;
			case 3:
				findStudent();
				break;
			case 4:
				findFaculty();
				break;
			case 5:
				findAdvisor();
				break;
			case 6:
				printAdvisees();
				break;
			case 7:
				addStudent();
				break;
			case 8:
				deleteStudent();
				break;
			case 9:
				addFaculty();
				break;
			case 10:
				deleteFaculty();
				break;
			case 11:
				changeStudentAdvisor();
				break;
			case 12:
				removeAdvisee();
				break;
			case 13:
				rollback();
				break;
			case 14:
				exit();
				break;
			default:
				cout << "Incorrect Choice" << endl;
				break;
		};

		cout << endl;
	}

	cout << "Program will end now..." << endl;
	return 0;
}

void intro()
{
	cout << "1. Print all students and their information (sorted by ascending id#)" << endl;
	cout << "2. Print all faculty and their information (sorted by ascending id #)" << endl;
	cout << "3. Find and display student information given the students id" << endl;
	cout << "4. Find and display faculty information given the faculty id" << endl;
	cout << "5. Given a student’s id, print the name and info of their faculty advisor" << endl;
	cout << "6. Given a faculty id, print ALL the names and info of his/her advisees." << endl;
	cout << "7. Add a new student" << endl;
	cout << "8. Delete a student given the id" << endl;
	cout << "9. Add a new faculty member"  << endl;
	cout << "10. Delete a faculty member given the id." << endl;
	cout << "11. Change a student’s advisor given the student id and the new faculty id." << endl;
	cout << "12. Remove an advisee from a faculty member given the id" << endl;
	cout << "13. Rollback" << endl;
	cout << "14. Exit" << endl;
}

void printStudentsInfo()
{
	masterStudent.printTree();
}

void printFacultyInfo()
{
	masterFaculty.printTree();
}

void findStudent()
{
	int stdID;
	cout << "Enter the Student ID:";
	cin >> stdID;
	Student temp(stdID,"","","",0,0);

	Student *temp2 = masterStudent.find(temp);
	if(temp2 != NULL)
		{
	 	Student temp3 = *temp2;
		temp3.printDetails();
	}
	else
	{
		cout << "Student with ID:" << stdID << " was not found" << endl << endl;
	}
}

void findFaculty()
{
	int facID;
	cout << "Enter the Faculty ID:";
	cin >> facID;
	Faculty temp(facID,"","","");

	cout << masterFaculty.contains(temp) << endl;
	Faculty *temp2 = masterFaculty.find(temp);
	if(temp2 != NULL)
		{
	 	Faculty temp3 = *temp2;
		temp3.printDetails();
	}
	else
	{
		cout << "Faculty with ID:" << facID << " was not found" << endl << endl;
	}
}

void findAdvisor()
{
	int stdID;
	cout << "Enter the Student ID:";
	cin >> stdID;
	Student temp(stdID,"","","",0,0);

	Student *temp2 = masterStudent.find(temp);
	if(temp2 != NULL)
	{
	 	Student temp3 = *temp2;
	 	int aid = temp3.getAdvisorID();
	 	Faculty temp(aid,"","","");
	 	Faculty *f = masterFaculty.find(temp);
		cout << "finally" << endl;
		if(f != NULL)
			{
		 	Faculty g = *f;
			g.printDetails();
		}
	}
	else
	{
		cout << "Student with ID:" << stdID << " was not found" << endl << endl;
	}
}

void printAdvisees()
{
	int facID;
	cout << "Enter the Faculty ID:";
	cin >> facID;
	Faculty temp(facID,"","","");

	Faculty *temp2 = masterFaculty.find(temp);
	if(temp2 != NULL)
	{
	 	Faculty temp3 = *temp2;
		temp3.listAdvisees();
	}

	else
	{
		cout << "Faculty with ID:" << facID << " was not found" << endl << endl;
	}
}

void addStudent()
{
	snapshot();
	string name,year,major;
	int sid,aid;
	double gpa;
	cout << "Enter the student ID:";
	cin >> sid;
	cin.ignore();
	cout << "Enter the student name:";
	getline(cin, name);
	cout << "Enter the student year:";
	cin >> year;
	cin.ignore();
	cout << "Enter the student major:";
	getline(cin, major);
	cout << "Enter the student GPA:";
	cin >> gpa;
	cout << "Enter the advisorID:";
	cin >> aid;

	Faculty ftemp(aid,"","","");
	Faculty *temp2 = masterFaculty.find(ftemp);
	if(temp2 != NULL)
	{	
		Student temp(sid,name,year,major,gpa,aid);
		masterStudent.insert(temp);
		temp2->addAdvisee(temp);  				//WHAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAt
		cout << "Student Added" << endl;
	}
	else
	{
		cout << "Incorrect advisorID" << endl;
		cout << "Aborting adding student" << endl;
		return;
	}
}

void deleteStudent()
{
	snapshot();
	int sid;
	cout << "Enter the student ID to delete:";
	cin >> sid;

	Student temp(sid,"","","",0,0);
	masterStudent.deleteNode(temp);
	cout << "Student deleted from records" << endl;
	// also remove from advisor list, get aid before hand
}

void addFaculty()
{
	snapshot();
	string name,level,dept;
	int aid;
	cout << "Enter the faculty ID:";
	cin >> aid;
	cout << "Enter the member name:";
	cin >> name;
	cout << "Enter the member level:";
	cin >> level;
	cout << "Enter the member department:";
	cin >> dept;

	Faculty temp(aid,name,level,dept);
	masterFaculty.insert(temp);
	cout << "Faculty Added" << endl;
}

void deleteFaculty()
{
	snapshot();
	int aid;
	cout << "Enter the faculty ID to delete:";
	cin >> aid;

	Faculty temp(aid,"","","");
	masterFaculty.deleteNode(temp);
	cout << "Faculty deleted from records" << endl;
}

void changeStudentAdvisor()
{
	snapshot();
	int sid, aid;
	cout << "Enter student’s ID:" << endl;
	cin >> sid;
	cout << "Enter faculty's ID:" << endl;
	cin >> aid;

	Student temp(sid,"","","",0,0);

	Student *temp2 = masterStudent.find(temp);
	if(temp2 != NULL)
	{
	 	Student temp3 = *temp2;
		
		Faculty ftemp(aid,"","","");

		Faculty *ftemp2 = masterFaculty.find(ftemp);

		if(ftemp2 != NULL)
		{
		 	Faculty ftemp3 = *ftemp2;
		 	masterStudent.deleteNode(temp);

		 	Faculty oFtemp(temp2->getAdvisorID(),"","","");

		 	Faculty *oFtemp2 = masterFaculty.find(oFtemp);

			if(oFtemp2 != NULL)
			{
	 			Faculty oFtemp3 = *oFtemp2;
	 			masterFaculty.deleteNode(oFtemp3);
	 			oFtemp3.removeAdvisee(temp);
	 			masterFaculty.insert(oFtemp3);
			 	temp3.setAdvisorID(aid);
			 	masterStudent.insert(temp3);

			 	Faculty nFtemp(aid,"","","");

				Faculty *nFtemp2 = masterFaculty.find(nFtemp);
				if(nFtemp2 != NULL)
				{
				 	Faculty nFtemp3 = *nFtemp2;
				 	masterFaculty.deleteNode(nFtemp3);
				 	nFtemp3.addAdvisee(temp3);
				 	masterFaculty.insert(nFtemp3);
				}
			}
		}
		else
		{
			cout << "Faculty with ID:" << aid << " was not found" << endl << endl;
		}
	}
	else
	{
		cout << "Student with ID:" << sid << " was not found" << endl << endl;
	}
}

void removeAdvisee()
{
	snapshot();
	/*
	step 1: get student id and faculty id
	step 2: check if student and faculty exists
	step 3: save both student and faculty to temp objects
	step 4: change student's advisor ID to default faculty, maybe first faculty, (or NULL)
	step 5: remove student from faculty's advisee list
	step 6: remove student and faculty objects from respective trees
	step 7: add new temp student and faculty to respective trees
	*/
}

void snapshot()
{
	/*
	step 1: add to beginning of options 7,8,9,10,11,12
	step 2: use double ended list of object type student bst and faculty bst
	step 3: for each tree add to the end of the respective lists
	step 4: check to see if list is greater than 5 in size
	step 5: if yes, then remove snapshot from other end (end not inserting on)
	*/
	//delete fNode;
	//delete sNode;
	fNode = new FacultyNode;
	masterFaculty.copyf(fNode->facultyTree, masterFaculty.root);
	sNode = new StudentNode;
	masterStudent.copys(sNode->studentTree, masterStudent.root);

	facultyList.insertFront(*fNode);
	cout << fNode << endl;
	studentList.insertFront(*sNode);

	if(facultyList.size >= 5)
		facultyList.removeBack();
	if(studentList.size >= 5)
		studentList.removeBack();
}

void rollback()
{
	/*
	step 1: confirm that each list is not NULL
	step 2: set student tree and faculty tree to ends of respective lists
	step 3: remove ends of each list
	*/
	if(!facultyList.isEmpty())
		facultyList.removeFront(masterFaculty).facultyTree;
	if(!studentList.isEmpty())
		studentList.removeFront(masterStudent).studentTree;
}

void exit()
{
	/*
	*note: at start of program read in from files; call deserialize functions
	step 1: call serialize functions
	step 2: quit
	*/
}

Student Deserialize(string cereal)
{
	string str1 = cereal;
	string ID = str1.substr(0,str1.find('@'));
	str1 = str1.substr(str1.find('@') + 1, -1);

	string name = str1.substr(0,str1.find('@'));
	str1 = str1.substr(str1.find('@') + 1, -1);

	string level = str1.substr(0,str1.find('@'));
	str1 = str1.substr(str1.find('@') + 1, -1);

	string major = str1.substr(0,str1.find('@'));
	str1 = str1.substr(str1.find('@') + 1, -1);

	string GPA = str1.substr(0,str1.find('@'));
	str1 = str1.substr(str1.find('@') + 1, -1);

	string advisorID = str1.substr(0,str1.find('@'));

	Student temp(atoi(ID.c_str()), name, level, major, atof(GPA.c_str()), atoi(advisorID.c_str()));
	return temp;
}

Faculty Deserializer(string serial)
{
	string str2 = serial;
	string ID = str2.substr(0,str2.find('@'));
	str2 = str2.substr(str2.find('@') + 1, -1);

	string name = str2.substr(0,str2.find('@'));
	str2 = str2.substr(str2.find('@') + 1, -1);

	string level = str2.substr(0,str2.find('@'));
	str2 = str2.substr(str2.find('@') + 1, -1);

	string department = str2.substr(0,str2.find('@'));
	str2 = str2.substr(str2.find('@') + 1, -1);

	Faculty temp(atoi(ID.c_str()), name, level, department);
	return temp;
	//make sure to accomodate for the list of student's ID's
}

void studentToFile(Student& object)
{
	
}

void facultyToFile(Faculty& object)
{
	
}

void readFromFile(string filename) //for faculty
{

}