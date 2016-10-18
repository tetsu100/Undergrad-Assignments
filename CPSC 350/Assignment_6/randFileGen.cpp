#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

int main () {
	ofstream myfile;
	myfile.open ("inputDoubles.txt");

	srand( time(NULL) );
	
	int max = 100000;
	int min = 1;
	
	for (int i = 0; i < 40000; ++i)
	{
		double r = (max - min) * ( (double)rand() / (double)RAND_MAX ) + min;
		ostringstream strs;
		strs << r;
		string Tmpstr = strs.str();
		myfile << Tmpstr << "\r\n";
	}
	
	myfile.close();
	return 0;
}