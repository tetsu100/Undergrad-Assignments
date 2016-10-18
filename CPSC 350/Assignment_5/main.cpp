#include "sortingAlgorithmUtils.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
	//TODO 3 malloc arrays
	
	if ( argc != 2 )
		cout<<"Please pass file name as command line arg.";
	else {
		string arg1(argv[1]);
		string line;
		ifstream infile(arg1);
		
		while (getline(infile, line))
		{
			istringstream iss(line);
			double tmpDbl;
			if (!(iss >> tmpDbl)) { break; } // error

			cout << tmpDbl << endl;
		}
	}

	return 0;
}