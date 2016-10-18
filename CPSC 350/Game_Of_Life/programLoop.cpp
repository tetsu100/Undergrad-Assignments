#include "programLoop.h"
#include "grid.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

programLoop::programLoop(){ //runs the proper mode, gets user input, and decides when to terminate.
	bool a = false;
	bool m = false;
	double inpD;
	string fileName;
	char MA = getInput("Would you like to provide a map, or have the world randomly assigned? (m/a)");
	if(MA=='a'){
		a = true;
		string prompt = "Please enter the height: ";
		int min = 1;
		int max = 150;
		cout << prompt << "\n >> ";
		int inp = -1;
		while(inp < min || inp > max) {
			if(inp != -1) cout << "INVALID INPUT " << "RANGE IS " << min << " to " << max << "\n >> ";
			cin>>inp;
		}
		programLoop::height = inp;
		prompt = "Please enter the width: ";
		cout << prompt << "\n >> ";
		inp = -1;
		while(inp < min || inp > max) {
			if(inp != -1) cout << "INVALID INPUT " << "RANGE IS " << min << " to " << max << "\n >> ";
			cin>>inp;
		}
		programLoop::width = inp;
		prompt = "Please enter the density (float from 0-1): ";
		cout << prompt << "\n >> ";
		inpD = -1.0;
		min = 0, max = 1;
		while(inpD <= (double)min || inpD > (double)max) {
			if(inpD != -1.0) cout << "INVALID INPUT " << "RANGE IS " << min << " to " << max << "\n >> ";
			cin>>inpD;
		}
	}
	else if(MA=='m'){
		m = true;
		ifstream inpLife;
		do {
			cout << "What is the filename?\n >> ";
			cin >> fileName;
			inpLife.open(fileName.c_str());
		} while(inpLife.fail());
		inpLife >> programLoop::height;
		inpLife >> programLoop::width;
	}
	grid life(width,height);
	if(a) life.randAssign(inpD);
	if(m) life.fileAssign(fileName);
	classic = false, doughnut = false, mirror = false, paused = false, automated = false;
	string promptMode = "Please select a mode: Doughnut (d), Mirror (m), or Classis (c)";
	cout << promptMode << "\n >> ";
	char inpMode = ' ';
	while(inpMode != 'd' && inpMode != 'm' && inpMode != 'c') {
		if(inpMode != ' ') cout << "INVALID INPUT " << "\n >> ";
		cin>>inpMode;
		inpMode = tolower(inpMode);
	}
	if(inpMode == 'd') doughnut = true;
	else if(inpMode == 'm') mirror = true;
	else if(inpMode == 'c') classic = true;
	promptMode = "Would you like automatic simulation (a), or a pause between generations (p)?";
	cout << promptMode << "\n >> ";
	inpMode = ' ';
	while(inpMode != 'a' && inpMode != 'p') {
		if(inpMode != ' ') cout << "INVALID INPUT " << "\n >> ";
		cin>>inpMode;
		inpMode = tolower(inpMode);
	}
	if(inpMode == 'a') automated = true;
	else if(inpMode == 'p') paused = true;
	//life.printGrid(life.gridCur);
	
	char **stagCheck;
	stagCheck = new char*[height];
	for(int i = 0; i < height; i++)
		stagCheck[i] = new char[width];
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			stagCheck[i][j] = life.gridCur[i][j];
		}
	}
	bool stagnant = false;

	while(!stagnant){
		if(paused) cin.get();
		if(automated) usleep(150000);
		
		if(classic){
			life.updateClassic();
		}
		else if(doughnut){
			life.updateDoughnut();
		}
		else if(mirror){
			life.updateMirror();
		}
		if(life.generation%2==0){
			int stagCntr = 0;
			for(int i = 0; i < height; i++){
				for(int j = 0; j < width; j++){
					if(stagCheck[i][j] == life.gridCur[i][j]) stagCntr++;
				}
			}
			if(stagCntr == width*height) {
				stagnant = true;
				cout << "Life has become stagnant.";
			}
			else{
				for(int i = 0; i < height; i++){
					for(int j = 0; j < width; j++){
						stagCheck[i][j] = life.gridCur[i][j];
					}
				}
			}
		}
	}
}

char programLoop::getInput(string prompt){
	cout << prompt << "\n >> ";
	char inp = ' ';
	while(inp != prompt[prompt.size()-2] && inp != prompt[prompt.size()-4]) {
		if(inp != ' ') cout << "INVALID INPUT " << prompt.substr(prompt.size()-5) << "\n >> ";
		cin>>inp;
		inp = tolower(inp);
	}
	return inp;
}
