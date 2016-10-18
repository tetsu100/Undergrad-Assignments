#include <iostream>
#include "GenQueue.h"
#include "RegistrarOffice.h"

using namespace std;

int main(int argc, char *argv[])
{
	
	if(argc >=2){
		string fileName = string(argv[1]);
		RegistrarOffice chapmanOffice(fileName);
	} else { cout<< "Failed to open sequence file."<<endl; }
	
	return 0;
}