#ifndef DATA_H
#define DATA_H
#include <string>

class data 
{
public:
	int A, G, C, T, lines;
	data();
	void getData(std::string file);
	void extractData(std::string sequence);
};

#endif