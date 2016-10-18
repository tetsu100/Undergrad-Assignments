#include "GenQueue.h"
#include "RegistrarOffice.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

RegistrarOffice::RegistrarOffice(string fileName){ 
	getInfo(fileName); //retrieves how many students are coming and when from the text file
}

void RegistrarOffice::getInfo(string fileName){
	
	ifstream file(fileName.c_str());
    string str; 
	int str_to_int = -1;
	int lineNum = 0;
	int numWindows;
	int curClockTick = -1;
	int numStudentsArriving = 0;
	bool nextClockTick = true;
	
    while (getline(file, str))
    {
		stringstream ss(str);
		ss >> str_to_int;
        if(lineNum == 0){
			numWindows = str_to_int; //init num of windows
		}
		else if(nextClockTick){
			curClockTick = str_to_int;
			nextClockTick = false;
		}
		else if(numStudentsArriving == 0){
			numStudentsArriving = str_to_int;
		}
		else {
			studentLine.push(studentAtTime_N(curClockTick, str_to_int));
			numStudentsArriving--;
			if(numStudentsArriving == 0){
				nextClockTick = true; //logic chain gathers rest of info
			}
		}
		lineNum++;
    }
	simulate(numWindows); //let's get in line!
}

void RegistrarOffice::simulate(int passedWindowNum){
	int openWindows [passedWindowNum] = {0};
	int idleWindows [passedWindowNum] = {0};
	int clockTick = 0;
	vector <int> waitTimes;
	vector <int> idleTimes;
	bool windowsFull = false;
	bool windowsEmpty= true;
	
	while(studentLine.notEmpty() || !windowsEmpty){ //loops as long as windows still being used
		studentAtTime_N tmp;
		
		while(studentLine.peek().time_N <= clockTick && !windowsFull && studentLine.peek().time_N != -1){ //checks is students arriving/waiting
			for(int i = 0; i < passedWindowNum; i++){
				if(openWindows[i] == 0){
					tmp = studentLine.pop();
					openWindows[i] = tmp.timeNeeded;				
					waitTimes.push_back(clockTick - tmp.time_N);
					break;
				}
			}
			for(int i = 0; i < passedWindowNum; i++){
				if(openWindows[i] == 0){
					windowsFull = false;
					break;
				}
				windowsFull = true;
			}
		}
		
		for(int i = 0; i < passedWindowNum; i++){ //passes time at windows
			if(openWindows[i] > 0){
				openWindows[i] = openWindows[i] - 1;
			}
			if(openWindows[i] == 0){
				if(idleWindows[i] == 0){
					idleWindows[i] = clockTick;
				}
				windowsFull = false;
			}
		}
		clockTick++;
		
		for(int i = 0; i < passedWindowNum; i++){ //figures out window idle times
			if(openWindows[i] > 0){
				if(idleWindows[i] != 0){
					idleTimes.push_back(clockTick - idleWindows[i] -1);
					idleWindows[i] = 0;
				}
				windowsEmpty = false;
				break;
			}
			windowsEmpty = true;
		}
		//cout << "clockTick: " << clockTick << " studentLine: " << studentLine.getSize() << endl;
	}
	for(int i = 0; i < passedWindowNum; i++){
		if(idleWindows[i] != 0){
			idleTimes.push_back(clockTick - idleWindows[i] -1);
		}
	}
	calculate(waitTimes, idleTimes);
}

void RegistrarOffice::calculate(vector<int>& waitTimesPassed, vector<int>& idleTimesPassed){
	vector<int> waitTimes = waitTimesPassed;
	vector<int> idleTimes = idleTimesPassed;
	sort(waitTimes.begin(),waitTimes.end());
	double median;
	int longestTime = -1;
	int longestIdleTime = -1;
	int overTen = 0;
	int overFive = 0;
	size_t size = waitTimes.size();
	double mean = 0.0;
	double idleMean = 0.0;
	if (size  % 2 == 0) {
	  median = (waitTimes[size / 2 - 1] + waitTimes[size / 2]) / 2;
	}
	else {
	  median = waitTimes[size / 2];
	}
	for(std::vector<int>::iterator it = idleTimes.begin(); it != idleTimes.end(); ++it) {
		idleMean += *it;
		if (*it > longestIdleTime){
			longestIdleTime = *it;
		}
		if(*it > 5) {
			overFive++;
		}
	}
	for(std::vector<int>::iterator it = waitTimes.begin(); it != waitTimes.end(); ++it) {
		mean += *it;
		if (*it > longestTime){
			longestTime = *it;
		}
		if(*it > 10) {
			overTen++;
		}
	}
	mean = mean / size;
	idleMean = idleMean / idleTimes.size();
	
	cout << "Median wait time: " << median << endl;
	cout << "Mean wait time: " << mean << endl;
	cout << "Longest wait time: " << longestTime << endl;
	cout << "Wait times over ten minutes: " << overTen << endl;
	cout << "Mean window idle time: " << idleMean << endl;
	cout << "Longest idle time: " << longestIdleTime << endl;
	cout << "Idle times over five minutes: " << overFive << endl;
}