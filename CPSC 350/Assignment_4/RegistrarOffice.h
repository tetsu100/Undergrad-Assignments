#ifndef REGISTRAROFFICE_H
#define REGISTRAROFFICE_H

#include <iostream>
#include <vector>

class RegistrarOffice
{
	struct studentAtTime_N
    {
        int time_N;
		int timeNeeded;
        studentAtTime_N(int ptime_N, int ptimeNeeded) : timeNeeded(ptimeNeeded), time_N(ptime_N) {}
		studentAtTime_N() : timeNeeded(-1), time_N(-1) {}
    };
public:
	RegistrarOffice(string fileName);
	void getInfo(string fileName);
	void simulate(int passedWindowNum);
	void calculate(vector<int>& waitTimesPassed, vector<int>& idleTimesPassed);
	
	GenQueue<studentAtTime_N> studentLine;
};

#endif