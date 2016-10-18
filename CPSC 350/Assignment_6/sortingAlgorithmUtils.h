#ifndef SORTINGALGORITHMUTILS_H
#define SORTINGALGORITHMUTILS_H

class sortingAlgorithmUtils
{
public:
	static void printArr(double* array, int n);
	static void quickSort(double* array, int startIndex, int endIndex);
	static int pivotQS(double* array, double pivotValue, int startIndex, int endIndex);
	static void swapQS(double &a, double &b);
	static void insertionSort(double* array, int length);
	static void dinoSort(double* array, int endIndex);
};

#endif