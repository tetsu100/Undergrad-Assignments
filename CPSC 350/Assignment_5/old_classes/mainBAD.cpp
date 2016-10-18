#include <iostream>
#include <string>
#include <cstdlib>
#include "binaryST.h"
#include "student.h"
using namespace std;

int main()
{
	binaryST<student> bst;

	student tmp1;
	student tmp2;
	
	//bst.insert(tmp1);
	//bst.insert(tmp2);
	
	bst.printTree();
	
	cout << "YAY" << endl;
	
	student boy;
	//cout << boy.toSerial() << endl;
	//student girl( boy.toSerial());
	//cout << girl.toSerial() << endl;
	
	
	return 0;
}