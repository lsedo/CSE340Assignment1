#include "program1.h"
#include "Grammar.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>


// Loads the grammar.
void LoadGrammar(char *grammarFileName) 
{
	programFileLexerPointer = new FileLexer(' ', '@');
	programFileLexerPointer->openFile(grammarFileName);
	
	if(programFileLexerPointer->valid())
	{
		programGrammarPointer = new Grammar(programFileLexerPointer);
	}
}

// Returns a string with some statistics for the grammar.
char* GetStats() 
{   
	char* cStyleOutput;
	
	if(programGrammarPointer != NULL)
	{
	    std::string output = programGrammarPointer->getStats(programFileLexerPointer);
	    char* cStyleOutput = new char[output.length() + 1];
	    strcpy(cStyleOutput, output.c_str());
	    
		return cStyleOutput;
	}
	else
	{
		cStyleOutput = new char[1];
		cStyleOutput[0] = '\0';
		
		return cStyleOutput;
	}
}

// Returns the first sets of all nonterminals.
char* GetFirstSets() 
{
	char* cStyleOutput;
	
	if(programGrammarPointer != NULL)
	{
		std::string output = programGrammarPointer->getFirstSets();
		
	    	cStyleOutput = new char[output.length() + 1];
	   	strcpy(cStyleOutput, output.c_str());
	    
		return cStyleOutput;
	}
	else
	{
		cStyleOutput = new char[1];
		cStyleOutput[0] = '\0';
		
		return cStyleOutput;
	}
}

// Returns the first set of the specified nonterminal.
char* GetFirstSet(char *nonTerminal) 
{
	char* cStyleOutput;

	if(programGrammarPointer != NULL)
	{	
		std::string input(nonTerminal);
		std::string output = programGrammarPointer->getFirstSet(input);
		
	    	cStyleOutput = new char[output.length() + 1];
	   	strcpy(cStyleOutput, output.c_str());
	    
		return cStyleOutput;
	}
	else
	{
		cStyleOutput = new char[1];
		cStyleOutput[0] = '\0';
		
		return cStyleOutput;
	}
}

// Returns the follow sets of all nonterminals.
char* GetFollowSets() 
{
	char* cStyleOutput;
	
	if(programGrammarPointer != NULL)
	{
		std::string output = programGrammarPointer->getFollowSets();
		
		cStyleOutput = new char[output.length() + 1];
	   	strcpy(cStyleOutput, output.c_str());
		
		return cStyleOutput;
	}
	else
	{
		cStyleOutput = new char[1];
		cStyleOutput[0] = '\0';
		
		return cStyleOutput;
	}
}

// Returns the follow set of the specified nonterminal.
char* GetFollowSet(char *nonTerminal) 
{
	char* cStyleOutput;
	
	if(programGrammarPointer != NULL)
	{
		std::string input(nonTerminal);
		std::string output = programGrammarPointer->getFollowSet(input);
		
		cStyleOutput = new char[output.length() + 1];
	   	strcpy(cStyleOutput, output.c_str());
		
		return cStyleOutput;
	}
	else
	{
		cStyleOutput = new char[1];
		cStyleOutput[0] = '\0';
		
		return cStyleOutput;
	}
}
