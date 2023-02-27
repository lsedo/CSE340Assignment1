#include "program1.h"
#include "Grammar.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>

/*

	FileLexer Methods

*/

FileLexer::FileLexer(char delim, char lEnd)
{
    delimiter = delim;
    lineEnd = lEnd;
}

FileLexer::~FileLexer()
{
    closeFile();
}

// peekToken()
// Returns the next token as a string variable.

std::string FileLexer::peekToken()
{  
    char currSymbol;

	// Iterates tokenIndexEnd until a delimiter or EOL symbol is read.

	for(int i = tokenIndexStart; i < line.length(); i++)
	{
		currSymbol = line.at(i);

		if(currSymbol == delimiter || currSymbol == lineEnd)
		{
			tokenIndexEnd = i;
			i = line.length();
		}
	}
    
	// Looks for EOL/EOF by checking if the current symbol is an EOL symbol and, if so, if another occurs after it.

    if(currSymbol == lineEnd)
    {
        if((tokenIndexEnd + 1) < line.length())	// To avoid seg fault <3
        {
            if(line.at(tokenIndexEnd + 1) == lineEnd)
            {
                return "EOF";
            }
        }
        
        return "EOL";
    }
    else if (currSymbol == delimiter)
    {
        int start = tokenIndexStart;
        int end = tokenIndexEnd;
        
        tokenIndexStart = tokenIndexEnd + 1;
        tokenIndexEnd = tokenIndexStart;
        
        return line.substr(start, end - start);
    }
    
    return "ERROR";
}

// getLine()
// Returns the entire line.

std::string FileLexer::getLine()
{
	return line;
}

// getCombinedTokens()
// Returns the rest of the tokens in the line as a single token.

std::string FileLexer::getCombinedTokens()
{
	std::string token = peekToken();
	std::string cToken = "";

	while(token.compare("EOL") != 0)
	{
		if(cToken.length() == 0)
		{
			cToken += token;	
		}
		else
		{
			cToken += delimiter + token;
		}

		token = peekToken();
	}

	return cToken;
}

char FileLexer::getDelimiter()
{
	return delimiter;
}

char FileLexer::getLineEnd()
{
	return lineEnd;
}

// openFile()
// Opens a new file for lexing and resets token indices.

void FileLexer::openFile(std::string pathToFile)
{
    closeFile();
    
    file.open(pathToFile);
    
    nextLine();
    
    tokenIndexStart = 0;
    tokenIndexEnd = 0;
}

// closeFile()
// Closes the current file.

void FileLexer::closeFile()
{
    if(file.is_open())
    {
        file.close();
    }
}

// nextLine()
// Retrieves the next line in the current file, assuming EOF is not reached.

void FileLexer::nextLine()
{
	if(!file.eof())
	{
	    std::getline(file, line);
    	tokenIndexStart = 0;
    	tokenIndexEnd = 0;
	}
}

// eof()
// Returns EOF status.

bool FileLexer::eof()
{
	return file.eof();
}

bool FileLexer::valid()
{
	return !file.fail();
}


/*

	NonTerminal Methods

*/

NonTerminal::NonTerminal(std::string k)
{
	key = k;
}

NonTerminal::NonTerminal()
{
	key = "undefined";
}

NonTerminal::~NonTerminal()
{

}
        
// void setKey
// Set the nonterminal's string key.

void NonTerminal::setKey(std::string k)
{
	key = k;
}
        
// void addRule
// Add a string terminal to the nonterminal's list of rules.

void NonTerminal::addRule(std::string r)
{
	rules.push_back(r);
	std::sort(rules.begin(), rules.end());
}
        
// void addToFirst
// Add a string terminal to the nonterminal's FIRST set.

void NonTerminal::addToFirst(std::string f)
{
	if(!setFirst.empty())
	{
		for(int i = 0; i < setFirst.size(); i++)
		{
			if(f.compare(setFirst.at(i)) == 0)
			{
				i = setFirst.size();
			}
			else
			{
				if(i == setFirst.size() - 1)
				{
					setFirst.push_back(f);
				}
			}
		}
	}
	else
	{
		setFirst.push_back(f);
	}

	std::sort(setFirst.begin(), setFirst.end());	
}
        
// addToFollow
// Add a string terminal to the nonterminal's FOLLOW set.

void NonTerminal::addToFollow(std::string f)
{
	
    
	if(!setFollow.empty())
	{
		for(int i = 0; i < setFollow.size(); i++)
		{

			if(f.compare(setFollow.at(i)) == 0)
			{
				i = setFollow.size();
			}
			else
			{
				if(i == setFollow.size() - 1)
				{
					setFollow.push_back(f);
				}
			}
		}
	}
	else
	{
		setFollow.push_back(f);
	}
	
	std::sort(setFollow.begin(), setFollow.end());
}
         
// getKey()
// Return the nonterminal's string key.
       
std::string NonTerminal::getKey()
{
	return key;
}
        
// getRules()
// Returns a pointer to the nonterminal's list of rules.

std::vector<std::string>* NonTerminal::getRules()
{
	return &rules;
}
        
// getFirstSet()
// Returns a pointer to the nonterminal's FIRST set.

std::vector<std::string>*  NonTerminal::getFirstSet()
{
	return &setFirst;
}
        
// std::vector<std::string>* NonTerminal::getFirstSet()
// Returns a pointer to the nonterminal's FOLLOW set.

std::vector<std::string>* NonTerminal::getFollowSet()
{
	return &setFollow;
}

void NonTerminal::addFirstToFirst(NonTerminal* nt, bool includeEpsilon)
{
	auto setPtr = nt->getFirstSet();

	if(!setPtr->empty())
	{
		for(int i = 0; i < setPtr->size(); i++)
		{
			if(!includeEpsilon)
			{
				if(setPtr->at(i).compare("#") != 0)
				{
					addToFirst(setPtr->at(i));
				}
			}
			else
			{
				addToFirst(setPtr->at(i));
			}
		}
	}
}

void NonTerminal::addFollowToFollow(NonTerminal* nt, bool includeEpsilon)
{
	auto setPtr = nt->getFollowSet();

	if(!setPtr->empty())
	{
		for(int i = 0; i < setPtr->size(); i++)
		{
			if(!includeEpsilon)
			{
				if(setPtr->at(i).compare("#") != 0)
				{
					addToFollow(setPtr->at(i));
				}
			}
			else
			{
				addToFollow(setPtr->at(i));
			}
		}
	}
}

void NonTerminal::addFirstToFollow(NonTerminal* nt, bool includeEpsilon)
{
	auto setPtr = nt->getFirstSet();

	if(!setPtr->empty())
	{
		for(int i = 0; i < setPtr->size(); i++)
		{
			if(!includeEpsilon)
			{
				if(setPtr->at(i).compare("#") != 0)
				{
					addToFollow(setPtr->at(i));
				}
			}
			else
			{
				addToFollow(setPtr->at(i));
			}
		}
	}
}

void NonTerminal::addFollowToFirst(NonTerminal* nt, bool includeEpsilon)
{
	auto setPtr = nt->getFollowSet();

	if(!setPtr->empty())
	{
		for(int i = 0; i < setPtr->size(); i++)
		{
			if(!includeEpsilon)
			{
				if(setPtr->at(i).compare("#") != 0)
				{
					addToFirst(setPtr->at(i));
				}
			}
			else
			{
				addToFirst(setPtr->at(i));
			}
		}
	}
}

bool NonTerminal::hasInFirst(std::string f)
{
	for(int i = 0; i < setFirst.size(); i++)
	{
		if(f.compare(setFirst.at(i)) == 0)
		{
			return true;
		}
	}

	return false;
}

bool NonTerminal::hasInFollow(std::string f)
{
	for(int i = 0; i < setFollow.size(); i++)
	{
		if(f.compare(setFollow.at(i)) == 0)
		{
			return true;
		}
	}

	return false;
}

/*

	Grammar Methods

*/

Grammar::Grammar(FileLexer* flPtr)
{
	loadGrammar(flPtr);
}

Grammar::~Grammar()
{

}
		
std::string Grammar::getNonTerminals()
{
	std::string nonTerms;

	for(int i = 0; i < nonTerminals.size(); i++)
	{
		nonTerms += nonTerminals.at(i)->getKey() + "\n";
	}

	return nonTerms;
}
std::string Grammar::getFirstSets()
{
	std::string firstSets = "";

	for(int i = 0; i < nonTerminals.size(); i++)
	{
		firstSets += getFirstSet(i);
	}

	return firstSets;
}

std::string Grammar::getFollowSets()
{
	std::string followSets = "";

	for(int i = 0; i < nonTerminals.size(); i++)
	{
		followSets += getFollowSet(i);
	}

	return followSets;
}

std::string Grammar::getFirstSet(int index)
{
	std::string firstSet = "FIRST(" + nonTerminals.at(index)->getKey() + ") = { ";

	for(int j = 0; j < nonTerminals.at(index)->getFirstSet()->size(); j++)
		{
			firstSet += nonTerminals.at(index)->getFirstSet()->at(j);

			if(j != nonTerminals.at(index)->getFirstSet()->size() - 1)
			{
				firstSet += ", ";
			}
		}

	return firstSet + " }\n";
}

std::string Grammar::getFollowSet(int index)
{
		std::string followSet = "FOLLOW(" + nonTerminals.at(index)->getKey() + ") = { ";

	for(int j = 0; j < nonTerminals.at(index)->getFollowSet()->size(); j++)
		{
			followSet += nonTerminals.at(index)->getFollowSet()->at(j);

			if(j != nonTerminals.at(index)->getFollowSet()->size() - 1)
			{
				followSet += ", ";
			}
		}

	return followSet + " }\n";
}

std::string Grammar::getFirstSet(std::string key)
{
	int index = -1;
	std::string firstSet = "FIRST(" + nonTerminals.at(index)->getKey() + ") = { ";

	for(int i = 0; i < nonTerminals.size(); i++)
	{
		if(nonTerminals.at(i)->getKey().compare(key) == 0)
		{
			index = i;
		}
	}



	for(int j = 0; j < nonTerminals.at(index)->getFirstSet()->size(); j++)
		{
			firstSet += nonTerminals.at(index)->getFirstSet()->at(j);

			if(j != nonTerminals.at(index)->getFirstSet()->size() - 1)
			{
				firstSet += ", ";
			}
		}

	return firstSet + " }\n";
}

std::string Grammar::getFollowSet(std::string key)
{
	int index = -1;
	std::string followSet = "FOLLOW(" + nonTerminals.at(index)->getKey() + ") = { ";

	for(int i = 0; i < nonTerminals.size(); i++)
	{
		if(nonTerminals.at(i)->getKey().compare(key) == 0)
		{
			index = i;
		}
	}


	for(int j = 0; j < nonTerminals.at(index)->getFollowSet()->size(); j++)
		{
			followSet += nonTerminals.at(index)->getFollowSet()->at(j);

			if(j != nonTerminals.at(index)->getFollowSet()->size() - 1)
			{
				followSet += ", ";
			}
		}

	return followSet + " }\n";
}

bool Grammar::isNonTerminal(std::string c)
{
	for(int i = 0; i < nonTerminals.size(); i++)
	{
		if(c.compare(nonTerminals.at(i)->getKey()) == 0)
		{
			return true;
		}
	}

	return false;
}
		
NonTerminal* Grammar::getNonTerminal(int index)
{
	if(index < nonTerminals.size())
	{
		return nonTerminals.at(index);
	}
	else
	{
		return NULL;
	}

}

NonTerminal* Grammar::getNonTerminal(std::string key)
{
	for(int i = 0; i < nonTerminals.size(); i++)
	{
		if(key.compare(nonTerminals.at(i)->getKey()) == 0)
		{
			return nonTerminals.at(i);
		}
	}

	return NULL;
}

void Grammar::loadGrammar(FileLexer* flPtr)
{
	loadNonTerminals(flPtr);

	flPtr->nextLine();

	loadRules(flPtr);

	loadFirstSets(flPtr);
	loadFollowSets(flPtr);
}

void Grammar::unloadGrammar()
{
	
}

void Grammar::loadNonTerminals(FileLexer* flPtr)
{
	std::string token = flPtr->peekToken();

	while(token.compare("EOL") != 0)
	{
		NonTerminal* nt = new NonTerminal(token);

		nonTerminals.push_back(nt);

		token = flPtr->peekToken();
	}
}

void Grammar::loadRules(FileLexer* flPtr)
{
	std::string token = "";

	while(!flPtr->eof())
	{
		token = flPtr->peekToken();
		NonTerminal* nt = getNonTerminal(token);

		if(nt != NULL)
		{
			token = flPtr->peekToken();

			if(token.compare("->") == 0)
			{
				token = flPtr->getCombinedTokens();

				nt->addRule(token);
			}
		}

		flPtr->nextLine();
	}
}

void Grammar::loadFirstSets(FileLexer* flPtr)
{
	initializeFirstSets();

	for(int n = 0; n < 2; n++)	// Run over all nonterminals twice to ensure correct FIRST sets.
	{
		for(int x = 0; x < nonTerminals.size(); x++)
		{
			NonTerminal* nt = nonTerminals.at(x);
			auto rulesPtr = nt->getRules();

			for(int y = 0; y < rulesPtr->size(); y++)
			{
				std::string rule = rulesPtr->at(y);
				char delim = flPtr->getDelimiter();

				if(rule.find(delim) == std::string::npos)	// Case: The rule produces a single token.
				{
					if(!isNonTerminal(rule)) // Case: The rule produces a single terminal token.
					{	for(int x = 0; x < nonTerminals.size(); x++)
						nt->addToFirst(rule);
					}
					else					 // Case: The rule produces a single nonterminal token.
					{
						nt->addFirstToFirst(getNonTerminal(rule), true);
					}
				}
				else						 // Case: The rule produces more than one token.
				{
					int start = 0;
					bool hasEpsilon = false;

					for(int z = 0; z < rule.length(); z++)
					{
						if(rule.at(z) == delim || z == rule.length() - 1)
						{
							std::string subToken = rule.substr(start, z - start);

							if(!isNonTerminal(subToken))
							{
								nt->addToFirst(subToken);
								z = rule.length();
							}
							else
							{
								if(getNonTerminal(subToken)->getRules()->at(0).compare("#") == 0)
								{
									hasEpsilon = true;
									start = z + 1;
								}
								else
								{
									z = rule.length();
								}

								nt->addFirstToFirst(getNonTerminal(subToken), false);
							}
						}
					}

					if(hasEpsilon)
					{
						nt->addToFirst("#");
					}
				}
			}
		}
	}
}

void Grammar::loadFollowSets(FileLexer* flPtr)
{
	for(int n = 0; n < 2; n++)
	{
		for(int x = 0; x < nonTerminals.size(); x++)
		{
			NonTerminal* nt = nonTerminals.at(x);
			auto rulesPtr = nt->getRules();

			for(int y = 0; y < nt->getRules()->size(); y++)
			{
				std::string subToken = "";
				int start = 0;
				NonTerminal* ntPtr = NULL;
				char delim = flPtr->getDelimiter();
				std::string rule = nt->getRules()->at(y);

				if(rule.find(delim) != std::string::npos)
				{
					for(int z = 0; z < rule.length(); z++)
					{
						if(rule.at(z) == delim)
						{
							subToken = rule.substr(start, z - start);
							start = z + 1;
						}
						else if(z == rule.length() - 1)
						{
							subToken = rule.substr(start);

							if(ntPtr == NULL)
							{
								if(isNonTerminal(subToken))
								{
									ntPtr = getNonTerminal(subToken);
									ntPtr->addFollowToFollow(nt, true);
								}
							}
							else
							{
								if(isNonTerminal(subToken))
								{
									ntPtr->addFirstToFollow(getNonTerminal(subToken), false);

									if(getNonTerminal(subToken)->hasInFirst("#"))
									{		
										ntPtr->addFollowToFollow(nt, true);
									}
								}
							}
						}

						if(start > 0)
						{
							if(ntPtr == NULL)
							{
								if(isNonTerminal(subToken))
								{
									ntPtr = getNonTerminal(subToken);
								}
							}
						}
					}					
				}
			}
		}
	}

	for(int i = 0; i < nonTerminals.size(); i++)
	{
		if(nonTerminals.at(i)->getFollowSet()->empty())
		{
			nonTerminals.at(i)->addToFollow("##");
		}
	}
}

void Grammar::initializeFirstSets()
{
	for(int i = 0; i < nonTerminals.size(); i++)
	{
		NonTerminal* nt = nonTerminals.at(i);
		auto rulesPtr = nt->getRules();

		if(rulesPtr->at(0).compare("#") == 0)
		{
			nt->addToFirst("#");
		}
	}
}

std::string Grammar::getStats(FileLexer* flPtr)
{
	std::string stats = "";

	stats += collectNonTerminalStatistics();
	stats += collectTerminalStatistics(flPtr);

	return stats;
}

std::string Grammar::collectNonTerminalStatistics()
{
	std::string stats = "";

	for(int i = 0; i < nonTerminals.size(); i++)
	{
		stats += nonTerminals.at(i)->getKey() + " - " + std::to_string(nonTerminals.at(i)->getRules()->size());

		if(i != nonTerminals.size() - 1)
		{
			stats += ", ";
		}
	}

	return stats + "\n";
}

std::string Grammar::collectTerminalStatistics(FileLexer* flPtr)
{
	std::vector<std::string> terminals;
	std::string stats = "";

	for(int x = 0; x < nonTerminals.size(); x++)
	{
		NonTerminal* nt = nonTerminals.at(x);
		auto rulesPtr = nt->getRules();

		for(int y = 0; y < rulesPtr->size(); y++)
		{
			int start = 0;
			std::string rule = rulesPtr->at(y);
			char delim = flPtr->getDelimiter();

			for(int z = 0; z < rule.length(); z++)
			{
				std::string subToken = "";

				if(rule.at(z) == delim || z == rule.length() - 1)
				{
					if(z == rule.length() - 1)
					{
						subToken = rule.substr(start);
					}
					else
					{
						subToken = rule.substr(start, z - start);
						start = z + 1;						
					}

					if(!isNonTerminal(subToken))
					{
						terminals.push_back(subToken);
					}
				}
			}

		}
	}


	std::sort(terminals.begin(), terminals.end());

	int count = 0;
	std::string term = "";

	for(int x = 0; x < terminals.size(); x++)
	{
		if(term.compare(terminals.at(x)) != 0)
		{
			if(x == 0)
			{
				term = terminals.at(x);
				count = 1;
			}
			else
			{
				if(x == terminals.size() - 1)
				{
					stats += term + " - " + std::to_string(count) + ", ";

					term = terminals.at(x);
					count = 1;

					stats += term + " - " + std::to_string(count);
				}
				else
				{
					stats += term + " - " + std::to_string(count) + ", ";
					term = terminals.at(x);
					count = 1;
				}
			}
		}
		else
		{
			count++;
		}
	}

	return stats + "\n";
}

/*

	DRIVER METHODS

*/

Grammar* programGrammarPointer = NULL;
FileLexer* programFileLexerPointer = NULL;