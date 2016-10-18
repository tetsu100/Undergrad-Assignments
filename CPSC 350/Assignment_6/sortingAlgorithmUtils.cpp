#include "sortingAlgorithmUtils.h"
#include "binaryST.h"
#include <iostream>


using namespace std;

void sortingAlgorithmUtils::printArr(double* array, int n)
{
	for(int i = 0; i < n; i++) cout<<array[i]<<",  ";
	cout<<array[n] << endl;
}

void sortingAlgorithmUtils::dinoSort(double* array, int endIndex)
{ /*
	double average = 0;
	int middle;
	int length = endIndex-startIndex + 1;
	int leftBoundary = startIndex;
	int rightBoundary;
	bool leftNoted = false;
	bool rightNoted = false;
	
	if(length <= 1){
		return;
	}
	
	if(length%2 == 0){
		middle = (length/2)-1 + startIndex;
	}
	else{
		middle = length/2 + startIndex;
	}
	
	for (int i = startIndex + 1; i <= endIndex; i++){
		average += array[i];
	}
	average = average / (length -1);

	cout << "\n****\nStart: " << startIndex << " Middle: " << middle << " End: " << endIndex << endl;
	cout << "leftB: " << leftBoundary << " rightB: " << rightBoundary << " average: " << average << " Length: " << length << "\n" << endl;
	cout << "Before: " << endl;
	printArr(array, 9);

	
	while(leftBoundary < endIndex){
	cout << "\n****\nStart: " << startIndex << " Middle: " << middle << " End: " << endIndex << endl;
	cout << "leftB: " << leftBoundary << " rightB: " << rightBoundary << " average: " << average << " Length: " << length << "\n" << endl;
	cout << "Before: " << endl;
	printArr(array, 9);
		if(!leftNoted){
			if(array[leftBoundary] >= average){
				leftNoted = true;
				rightBoundary = endIndex;
			}
			else{
				leftBoundary++;
			}
		}
		int notedInd = leftBoundary;
		while(leftNoted){
			if(array[leftBoundary] > array[rightBoundary]){
				swapQS(array[leftBoundary], array[rightBoundary]);
				leftNoted = false;
			}
			else if(rightBoundary == notedInd){
				leftBoundary = startIndex;
				while(leftBoundary < notedInd){
					if(array[notedInd] < array[leftBoundary])
					cout << "swapping " << array[leftBoundary] << " with " << array[notedInd] << endl;
					swapQS(array[leftBoundary], array[notedInd]);
					leftBoundary++;
				}
				leftNoted = false;
				leftBoundary = notedInd+1;
			}
			else{
				rightBoundary--;
			}
		}
			cout << "\nStart: " << startIndex << " Middle: " << middle << " End: " << endIndex << endl;
	cout << "leftB: " << leftBoundary << " rightB: " << rightBoundary << " average: " << average << " Length: " << length << "\n" << endl;
	cout << "After: " << endl;
	printArr(array, 9);
	}

	cout << "\nStart: " << startIndex << " Middle: " << middle << " End: " << endIndex << endl;
	cout << "leftB: " << leftBoundary << " rightB: " << rightBoundary << " average: " << average << " Length: " << length << "\n" << endl;
	cout << "After: " << endl;
	printArr(array, 9);
*/ 
	binaryST<double>* sortBST  = new binaryST<double>(array);
	
	for(int i = 0; i <= endIndex; i++){
		sortBST->insert(array[i]);
	}
	sortBST->fillArray();
}

void sortingAlgorithmUtils::insertionSort (double* array, int length)
{
	int j;
		
	for (int i = 0; i < length; i++){
		j = i;
		
		while (j > 0 && array[j] < array[j-1]){
			  swapQS(array[j], array[j-1]);
			  j--;
		}
	}
}

void sortingAlgorithmUtils::swapQS(double &a, double &b)
{
	double temp;
	temp = a;
	a = b;
	b = temp;
}

void sortingAlgorithmUtils::quickSort(double* array, int startIndex, int endIndex)
{
	double pivot = array[startIndex];
	int splitPoint;
	
	if(endIndex > startIndex)
	{
		splitPoint = pivotQS(array, pivot, startIndex, endIndex);
		
		array[splitPoint] = pivot;
		quickSort(array, startIndex, splitPoint-1);
		quickSort(array, splitPoint+1, endIndex);
	}
}

int sortingAlgorithmUtils::pivotQS(double* array, double pivot, int startIndex, int endIndex)
{
	int leftBoundary = startIndex;
	int rightBoundary = endIndex;
	
	while(leftBoundary < rightBoundary)
	{
		 while( pivot < array[rightBoundary] && rightBoundary > leftBoundary)
		 {
			  rightBoundary--;
		 }
		 swapQS(array[leftBoundary], array[rightBoundary]);
		 
		 while( pivot >= array[leftBoundary] && leftBoundary < rightBoundary)
		 {
			  leftBoundary++;
		 }
		 swapQS(array[rightBoundary], array[leftBoundary]);
	}
	return leftBoundary;
}