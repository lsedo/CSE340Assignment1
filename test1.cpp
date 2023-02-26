#include "program1.h"
#include <stdio.h>

/* You may use this file to test your program.
	This file will not be submitted, as a different test1.cpp will be used. */
int main(int argv, char **argc) 
{
	std::string inp = "test.txt";
	std::string output = "";
	char* input = new char[inp.length() + 1];

	strcpy(input, inp.c_str());

	LoadGrammar(input);

	std::cout << GetStats();
	std::cout << GetFirstSets();
	std::cout << GetFollowSets();

	std::cout << programGrammarPointer;

	return 0;
}