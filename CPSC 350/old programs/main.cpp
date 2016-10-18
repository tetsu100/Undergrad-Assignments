#include <iostream>
#include <fstream>
#include "data.h"
#include <string>

using namespace std;


int main( int argc, char *argv[]){
	data DNAdata;
	if(argc >=2){
		string fileName = string(argv[1]);
		DNAdata.getData(fileName);
	} else { cout<< "Failed to open sequence file."<<endl; }

	return 0;
}