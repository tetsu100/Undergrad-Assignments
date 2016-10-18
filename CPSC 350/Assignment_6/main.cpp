#include "sortingAlgorithmUtils.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

using namespace std;

int main(int argc, char *argv[])
{
	//TODO 3 malloc arrays
	double *arrayOne;
	double *arrayTwo;
	double *arrayThree;
	int arrIndex = 0;
	int sizeArr = 0;
	
	if ( argc != 2 )
		cout<<"Please pass file name as command line arg.";
	else {
		string line;
		ifstream infile(argv[1]);
		
		bool firstLine = true;
		
		while (getline(infile, line))
		{
			if(firstLine){
				istringstream iss(line);
				if (!(iss >> sizeArr)) { break; } // error
				
				arrayOne=new double[sizeArr];
				arrayTwo=new double[sizeArr];
				arrayThree=new double[sizeArr];
				
				firstLine = false;
			}
			else{
				istringstream iss(line);
				double tmpDbl;
				if (!(iss >> tmpDbl)) { break; } // error
				
				arrayOne[arrIndex] = tmpDbl;
				arrayTwo[arrIndex] = tmpDbl;
				arrayThree[arrIndex] = tmpDbl;
				
				arrIndex++;
			}
		}
		clock_t    start;

		start = clock();
		cout << "Starting InsertionSort at: " <<  (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
		sortingAlgorithmUtils::insertionSort(arrayOne, sizeArr);
		cout << "Finished InsertionSort at: " <<  (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms\n" << endl;
		
		start = clock();
		cout << "Starting QuickSort at: " <<  (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
		sortingAlgorithmUtils::quickSort(arrayTwo, 0, sizeArr-1);
		cout << "Finished QuickSort at: " <<  (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms\n" << endl;
		
		start = clock();
		cout << "Starting DinoSort at: " <<  (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << endl;
		sortingAlgorithmUtils::dinoSort(arrayThree, sizeArr-1);
		cout << "Finished DinoSort at: " <<  (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms\n" << endl;
		
		
		//cout << endl;
		//sortingAlgorithmUtils::printArr(arrayTwo, sizeArr-1);
		
		delete [] arrayOne;
		delete [] arrayTwo;
		delete [] arrayThree;
	}
	
	return 0;
}