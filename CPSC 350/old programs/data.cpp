#include "data.h"
#include <fstream>
#include <iostream>
#include <cctype>

using namespace std;

data::data(){
A = 0, G = 0, C = 0, T = 0, lines = 0;
}

void data::getData(string file){
	ifstream inpDNA(file.c_str());
	if (inpDNA.is_open()){
		string nucleotide;
		while(inpDNA >> nucleotide){
			cout << nucleotide << " " << nucleotide.length() <<  endl;
			lines++;
			string::iterator si;
			for(si = nucleotide.begin(); si<nucleotide.end(); si++) {
				switch(*si){
					case 'C': C++;
					break;
					case 'G': G++;
					break;
					case 'A': A++;
					break;
					case 'T': T++;
					break;
					default: cout << "something went wrong" <<endl;
				}
			}
		}
	}
	cout << "lines: " << lines;
}
