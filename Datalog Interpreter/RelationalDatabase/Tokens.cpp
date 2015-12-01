#include <iostream>
#include <sstream>
#include "Tokens.h"

using namespace std; 

Tokens::Tokens(string inType, string inVal, int inLine){
	type = inType;
	val = inVal;
	
	stringstream ss;
	ss << inLine;
	string toString = ss.str();
	line = toString;
}

//######################################Private Functions##############################
string Tokens::getType(){
	return type;
}

string Tokens::getValue(){
	return val;
}

string Tokens::getLine(){
	return line;
}

string Tokens::toString() {
	return "(" + this->getType() + "," + this->getValue() + "," + this->getLine() + ")";
}
