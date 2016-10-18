#ifndef CODEPARSER_H
#define CODEPARSER_H
#include "GenStack.h"
#include <iostream>

class codeParser
{
public:
	codeParser();
	void readFile(std::string fName);
	static void reportError(int lines, int chars, char chType);
};

#endif