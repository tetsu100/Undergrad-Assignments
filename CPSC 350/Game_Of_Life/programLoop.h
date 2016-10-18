#ifndef PROGRAMLOOP_H
#define PROGRAMLOOP_H
#include <string>
#include "grid.h"

class programLoop 
{
public:
	int width;
	int height;
	bool classic, doughnut, mirror, paused, automated;
	static grid life;
	programLoop();
	char getInput(std::string prompt);
};

#endif