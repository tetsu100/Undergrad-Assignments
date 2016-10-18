#ifndef GRID_H
#define GRID_H
#include <iostream>

class grid 
{
public:
	grid(int x, int y);
	void printGrid(char **grd);
	void populate();
	void randAssign(double density);
	void fileAssign(std::string fName);
	void updateClassic();
	void updateDoughnut();
	void updateMirror();
	int width;
	int height;
	int generation;
	char **gridCur;
	char **gridNew;
};

#endif