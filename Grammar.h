#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bits/stdc++.h>

class FileLexer
{
    public:
        
        FileLexer(char delim, char lEnd);
        ~FileLexer();
        
        std::string peekToken();
        std::string getLine();
        std::string getCombinedTokens();

        char getDelimiter();
        char getLineEnd();
        
        void openFile(std::string pathToFile);
        void closeFile();
        void nextLine();
        bool eof();
        bool valid();
    
    private:
    
        std::ifstream file;
        std::string line;
        
        char delimiter;
        char lineEnd;
        
        int tokenIndexStart;
        int tokenIndexEnd;
        
};

class NonTerminal
{
    public:
    
		NonTerminal(std::string k);
        NonTerminal();
        ~NonTerminal();
        
        void setKey(std::string k);
        void addRule(std::string r);
        void addToFirst(std::string f);
        void addToFollow(std::string f);
        
        std::string getKey();
        std::vector<std::string>* getRules();
        std::vector<std::string>* getFirstSet();
        std::vector<std::string>* getFollowSet();

        void addFirstToFirst(NonTerminal* nt, bool includeEpsilon);
        void addFollowToFollow(NonTerminal* nt, bool includeEpsilon);
        void addFirstToFollow(NonTerminal* nt, bool includeEpsilon);
        void addFollowToFirst(NonTerminal* nt, bool includeEpsilon);

        bool hasInFirst(std::string f);
        bool hasInFollow(std::string f);
    
    
    private:
    
        std::string key;
        std::vector<std::string> rules;
        std::vector<std::string>  setFirst;
        std::vector<std::string>  setFollow;
};

class Grammar
{
	public:
		Grammar(FileLexer* flPtr);
		~Grammar();
		
		std::string getNonTerminals();
		std::string getStats(FileLexer* flPtr);
		std::string getFirstSets();
		std::string getFollowSets();

		std::string getFirstSet(int index);
		std::string getFollowSet(int index);
        std::string getFirstSet(std::string key);
		std::string getFollowSet(std::string key);

        bool isNonTerminal(std::string c);
		
		NonTerminal* getNonTerminal(int index);
		NonTerminal* getNonTerminal(std::string key);
        char getDelimiter();
        char getLineEnd();
		

	private:

		void loadGrammar(FileLexer* flPtr);
		void unloadGrammar();
		void loadNonTerminals(FileLexer* flPtr);
		void loadRules(FileLexer* flPtr);
        void loadFirstSets(FileLexer* flPtr);
        void loadFollowSets(FileLexer* flPtr);
        void initializeFirstSets();

        std::string collectTerminalStatistics(FileLexer* flPtr);
        std::string collectNonTerminalStatistics();

		std::vector<NonTerminal*> nonTerminals;

};

// Global pointers for driver methods
extern Grammar* programGrammarPointer;
extern FileLexer* programFileLexerPointer;

#endif