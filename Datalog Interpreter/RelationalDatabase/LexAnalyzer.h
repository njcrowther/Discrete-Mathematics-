#pragma once

#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cctype>

#include "Tokens.h"

using namespace std;

/*
	- LexAnalyzer scans the file and moves between states, adds tokens to a vector, and returns a vector
	- Save stream somewhere
		- class level variable? OR pass stream to "tokenize"
	- function to return vector of tokens
*/
class LexAnalyzer {
public:
	LexAnalyzer(ifstream &file){
		//pass ifstream into constructor to make it a global variable that any test can use.
		
		FileStream = &file;
		lineNumber = 1;
	}
	~LexAnalyzer(){}

	vector<Tokens> tokenize();

	string toString(vector<Tokens> toStringVector);


/*###############################################PRIVATE FUNCTIONS###############################################*/
private:

	//isLetter
	bool isLetter(char testCharacter);

	//Iswhitespace
	bool isWhiteSpace(char testCharacter);

	//isDigit
	bool isNumber(char testCharacter);

	//isSymbol
	//bool isSymbol(char testCharacter);
	

	
	// STATE MACHINES
	string IDMachine(char testCharacter);
	string commentMachine(char testCharacter);
	string commaMachine(char testCharacter);
	string periodMachine(char testCharacter);
	string questionMachine(char testCharacter);
	string parenthesisMachine(char testCharacter);
	string colonMachine(char testCharacter);
	string operandMachine(char testCharacter);
	string stringMachine(char testCharacter);
	string multiCommentMachine(char testCharacter, int startLine);
	string singleCommentMachine(char testCharacter);

	//HELPER FUNCTIONS
	bool updateLineNumber(char testCharacter);
	string kWType(string KWTest);
	bool isKeyword(string testString);
	void newTokenGenerator(string tokenType, string tokenValue, int lineNumber);
	bool doubleApostropheCheck(char testCharacter);
	bool endStringCheck(char testCharacter);
	bool multiCommentBoolCheck();



//################################ PRIVATE VARIABLES ###############################################
	vector<Tokens> outputVector;
	ifstream* FileStream;
	int lineNumber;

};