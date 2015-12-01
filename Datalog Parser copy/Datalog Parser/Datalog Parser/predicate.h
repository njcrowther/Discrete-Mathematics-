#pragma once

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Predicate { 		//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
public:
	Predicate(){
		predicateID = "ID";
		parameter = "inputP";
	}
	Predicate(string ID, string inputP, vector<string> capturedVector){
		predicateID = ID;
		parameter = inputP;
		parameterList = capturedVector;
	}
	~Predicate(){}

	string schemeToString() { //compile and return string
		string returnString = predicateID + "(" + parameter;

		for(int i=0; i < parameterList.size(); i++) {
			returnString += "," + parameterList[i];
		}

		returnString += ")\n";
		return returnString;
	}

	string predicateToString() {
		string returnString = predicateID + "(" + parameter;

		for(int i=0; i < parameterList.size(); i++) {
			returnString += "," + parameterList[i];
		}

		returnString += ")";
		return returnString;
	}
	string factToString() { //compile and return string
		string returnString = predicateID + "(" + parameter;

		for(int i=0; i < parameterList.size(); i++) {
			returnString += "," + parameterList[i];
		}

		returnString += ").\n";
		return returnString;
	}

	string queryToString() {
		string returnString = "\n  " + predicateID + "(" + parameter;

		for(int i=0; i < parameterList.size(); i++) {
			returnString += "," + parameterList[i];
		}

		returnString += ")?";
		return returnString;
	}

private:
	string predicateID;
	string parameter;
	vector<string> parameterList;
};