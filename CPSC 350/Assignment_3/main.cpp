#include "codeParser.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]){
	
	codeParser exampleCP;
	
	if ( argc != 2 )
		cout<<"Please pass file name as command line arg.";
	else {
		string arg1(argv[1]);
		exampleCP.readFile(arg1);
	}
	
	return 0;
}