#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "parameter.h"

using namespace std;

class Predicate { 		//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
public:
    Predicate(){}
	Predicate(string ID, Parameter inputP, vector<Parameter> capturedVector){
		predicateID = ID;
		parameter = inputP;
		parameterList = capturedVector;
	}
	~Predicate(){}

	string schemeToString() { //compile and return string
		string returnString = predicateID + "(" + parameter.getParameterValue();

		for(int i=0; i < parameterList.size(); i++) {
			returnString += "," + parameterList[i].getParameterValue();
		}

		returnString += ")\n";
		return returnString;
	}

	string predicateToString() {
		string returnString = predicateID + "(" + parameter.getParameterValue();

		for(int i=0; i < parameterList.size(); i++) {
			returnString += "," + parameterList[i].getParameterValue();
		}

		returnString += ")";
		return returnString;
	}
	string factToString() { //compile and return string
		string returnString = predicateID + "(" + parameter.getParameterValue();

		for(int i=0; i < parameterList.size(); i++) {
			returnString += "," + parameterList[i].getParameterValue();
		}

		returnString += ").\n";
		return returnString;
	}

	string queryToString() {
		string returnString = "\n  " + predicateID + "(" + parameter.getParameterValue();

		for(int i=0; i < parameterList.size(); i++) {
			returnString += "," + parameterList[i].getParameterValue();
		}

		returnString += ")?";
		return returnString;
	}
    
    string getPredicateID() {
        return predicateID;
    }
    
    Parameter getParameter() {
        return parameter;
    }
    
    vector<Parameter> getParameterList() {
        return parameterList;
    }

private:
	string predicateID;
	Parameter parameter;
	vector<Parameter> parameterList;
};