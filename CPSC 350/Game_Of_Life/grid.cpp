#include "grid.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

grid::grid(int x, int y){ //instantiates the original and update grids
	cout << "CREATING POPULATED GRID" << endl;
	generation = 0;
	width = x;
	height = y;
	grid::gridCur = new char*[y];
	grid::gridNew = new char*[y];
	for(int i = 0; i < y; i++)
		gridCur[i] = new char[x];
	for(int i = 0; i < y; i++)
		gridNew[i] = new char[x];
	grid::populate();
	srand(time(NULL));
	// grid::gridCur[1][5] = 'X';
	// grid::gridCur[1][6] = 'X';
	// grid::gridCur[1][7] = 'X';
}

void grid::populate(){ //fills blank grids
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			grid::gridCur[i][j] = '-';
			grid::gridNew[i][j] = '-';
		}
	}
}

void grid::randAssign(double density){ //fills grid based on density
	int lifeLeft = width*height*density;
	int rX, rY; 
	while(lifeLeft > 0){
		rX = (rand() % width);
		rY = (rand() % height);
		if(gridCur[rY][rX] == '-'){
			gridCur[rY][rX] = 'X';
			lifeLeft--;
		}
	}
}

void grid::fileAssign(string fName){ //fills grid based on file
	ifstream inpLife(fName.c_str());
	if (inpLife.is_open()){
		string lifeLine;
		int curLine = 0;
		while(inpLife >> lifeLine){
			curLine++;
			if(curLine >= 3){
				for(unsigned int i = 0; i<lifeLine.length(); i++) {
					gridCur[curLine-3][i] = lifeLine[i];
				}
			}
		}
	}
}

void grid::printGrid(char **grd){ //self explanatory
	cout << "GENERATION " << generation++ << endl;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			cout << grd[i][j];
			if(j< width-1)
				cout << ' ';
		}
		cout << endl;
	}
}

void grid::updateClassic(){ //uses classic rules
	int cntr = 0;
	printGrid(gridCur);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			grid::gridNew[i][j] = '-';
		}
	}
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			if(x>0&&y>0&&y<height-1&&x<width-1){
				if(gridCur[(y-1)][x] == 'X') cntr++;
				if(gridCur[(y+1)][x] == 'X') cntr++;
				if(gridCur[y][(x+1)] == 'X') cntr++;
				if(gridCur[y][(x-1)] == 'X') cntr++;
				if(gridCur[(y-1)][(x-1)] == 'X') cntr++;
				if(gridCur[(y-1)][x+1] == 'X') cntr++;
				if(gridCur[(y+1)][(x-1)] == 'X') cntr++;
				if(gridCur[(y+1)][(x+1)] == 'X') cntr++;
			}
			if(x==0){
				if(y>0 && gridCur[(y-1)][x+1] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][x+1] == 'X') cntr++;
				if(y>0 &&gridCur[(y-1)][x] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][x] == 'X') cntr++;
				if(gridCur[(y)][x+1] == 'X') cntr++;
			}
			if(x==width-1){
				if(y>0 && gridCur[(y-1)][x-1] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][x-1] == 'X') cntr++;
				if(y > 0 && gridCur[(y-1)][x] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][x] == 'X') cntr++;
				if(gridCur[(y)][x-1] == 'X') cntr++;
			}
			if(y==0){
				if(x>0 && gridCur[y+1][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[y+1][x+1]=='X')cntr++;
				if(x>0 && gridCur[y][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[y][x+1]=='X')cntr++;
				if(gridCur[y+1][x]=='X') cntr++;
			}
			if(y==height-1){
				if(x>0 && gridCur[y-1][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[y-1][x+1]=='X')cntr++;
				if(x>0 && gridCur[y][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[y][x+1]=='X')cntr++;
				if(gridCur[y-1][x]=='X') cntr++;
			}
			if(cntr < 2 || cntr >3) gridNew[y][x] = '-';
			if(cntr == 2 ) gridNew[y][x] = gridCur[y][x];
			if(cntr == 3 ) { gridNew[y][x] = 'X'; }
			//if(cntr > 0){ cout << "x: " << x << " y: " << y << " cntr: " << cntr << " " << endl; }
			cntr = 0;
		}
	}
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			grid::gridCur[i][j] = grid::gridNew[i][j];
		}
	}
}

void grid::updateDoughnut(){ //uses doughnut rules
	int cntr = 0;
	printGrid(gridCur);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			grid::gridNew[i][j] = '-';
		}
	}
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			if(x>0&&y>0&&y<height-1&&x<width-1){
				if(gridCur[(y-1)][x] == 'X') cntr++;
				if(gridCur[(y+1)][x] == 'X') cntr++;
				if(gridCur[y][(x+1)] == 'X') cntr++;
				if(gridCur[y][(x-1)] == 'X') cntr++;
				if(gridCur[(y-1)][(x-1)] == 'X') cntr++;
				if(gridCur[(y-1)][x+1] == 'X') cntr++;
				if(gridCur[(y+1)][(x-1)] == 'X') cntr++;
				if(gridCur[(y+1)][(x+1)] == 'X') cntr++;
			}
			if(x==0){
				if(y>0 && gridCur[(y-1)][x+1] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][x+1] == 'X') cntr++;
				if(y>0 &&gridCur[(y-1)][x] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][x] == 'X') cntr++;
				if(gridCur[(y)][x+1] == 'X') cntr++;
				if(y>0 && gridCur[(y-1)][width-1] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][width-1] == 'X') cntr++;
				if(gridCur[(y)][width-1] == 'X') cntr++;
			}
			if(x==width-1){
				if(y>0 && gridCur[(y-1)][x-1] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][x-1] == 'X') cntr++;
				if(y > 0 && gridCur[(y-1)][x] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][x] == 'X') cntr++;
				if(gridCur[(y)][x-1] == 'X') cntr++;
				if(y > 0 && gridCur[(y-1)][0] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][0] == 'X') cntr++;
				if(gridCur[(y)][0] == 'X') cntr++;
			}
			if(y==0){
				if(x>0 && gridCur[y+1][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[y+1][x+1]=='X')cntr++;
				if(x>0 && gridCur[y][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[y][x+1]=='X')cntr++;
				if(gridCur[y+1][x]=='X') cntr++;
				if(x>0 && gridCur[height-1][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[height-1][x+1]=='X')cntr++;
				if(gridCur[height-1][x]=='X') cntr++;
			}
			if(y==height-1){
				if(x>0 && gridCur[y-1][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[y-1][x+1]=='X')cntr++;
				if(x>0 && gridCur[y][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[y][x+1]=='X')cntr++;
				if(gridCur[y-1][x]=='X') cntr++;
				if(x>0 && gridCur[0][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[0][x+1]=='X')cntr++;
				if(gridCur[0][x]=='X') cntr++;
			}
			if(cntr < 2 || cntr >3) gridNew[y][x] = '-';
			if(cntr == 2 ) gridNew[y][x] = gridCur[y][x];
			if(cntr == 3 ) { gridNew[y][x] = 'X'; }
			//if(cntr > 0){ cout << "x: " << x << " y: " << y << " cntr: " << cntr << " " << endl; }
			cntr = 0;
		}
	}
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			grid::gridCur[i][j] = grid::gridNew[i][j];
		}
	}
}

void grid::updateMirror(){ //uses mirror rules
	int cntr = 0;
	printGrid(gridCur);
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			grid::gridNew[i][j] = '-';
		}
	}
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			if(x>0&&y>0&&y<height-1&&x<width-1){
				if(gridCur[(y-1)][x] == 'X') cntr++;
				if(gridCur[(y+1)][x] == 'X') cntr++;
				if(gridCur[y][(x+1)] == 'X') cntr++;
				if(gridCur[y][(x-1)] == 'X') cntr++;
				if(gridCur[(y-1)][(x-1)] == 'X') cntr++;
				if(gridCur[(y-1)][x+1] == 'X') cntr++;
				if(gridCur[(y+1)][(x-1)] == 'X') cntr++;
				if(gridCur[(y+1)][(x+1)] == 'X') cntr++;
			}
			if(x==0){
				if(y>0 && gridCur[(y-1)][x+1] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][x+1] == 'X') cntr++;
				if(y>0 &&gridCur[(y-1)][x] == 'X') cntr+=2;
				if(y<height-1 && gridCur[(y+1)][x] == 'X') cntr+=2;
				if(gridCur[(y)][x] == 'X') cntr++;
			}
			if(x==width-1){
				if(y>0 && gridCur[(y-1)][x-1] == 'X') cntr++;
				if(y<height-1 && gridCur[(y+1)][x-1] == 'X') cntr++;
				if(y > 0 && gridCur[(y-1)][x] == 'X') cntr+=2;
				if(y<height-1 && gridCur[(y+1)][x] == 'X') cntr+=2;
				if(gridCur[(y)][x] == 'X') cntr++;
			}
			if(y==0){
				if(x>0 && gridCur[y+1][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[y+1][x+1]=='X')cntr++;
				if(x>0 && gridCur[y][x-1] == 'X') cntr+=2;
				if(x < width-1 && gridCur[y][x+1]=='X')cntr+=2;
				if(gridCur[y][x]=='X') cntr++;
			}
			if(y==height-1){
				if(x>0 && gridCur[y-1][x-1] == 'X') cntr++;
				if(x < width-1 && gridCur[y-1][x+1]=='X')cntr++;
				if(x>0 && gridCur[y][x-1] == 'X') cntr+=2;
				if(x < width-1 && gridCur[y][x+1]=='X')cntr+=2;
				if(gridCur[y][x]=='X') cntr++;
			}
			if(cntr < 2 || cntr >3) gridNew[y][x] = '-';
			if(cntr == 2 ) gridNew[y][x] = gridCur[y][x];
			if(cntr == 3 ) { gridNew[y][x] = 'X'; }
			//if(cntr > 0){ cout << "x: " << x << " y: " << y << " cntr: " << cntr << " " << endl; }
			cntr = 0;
		}
	}
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			grid::gridCur[i][j] = grid::gridNew[i][j];
		}
	}
}