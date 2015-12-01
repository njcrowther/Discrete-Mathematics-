#pragma once

#include <iostream>
#include <string>

using namespace std;

class Parameter { //parameter	->	STRING | ID | expression
public:
    Parameter(){}
    Parameter(string inputType, string inputValue) {
        parameterType = inputType;
		parameterValue = inputValue;
	}
//    Parameter(Parameter p1, Parameter p2, string op) {
//        parameterType = "EXPRESSION";
//        xP1 = p1;
//        xP2 = p2;
//        xOp = op;
//    }
    ~Parameter(){}
    
    string getParameterType() {
        return parameterType;
    }
    //const
    string getParameterValue() {
        return parameterValue;
    }
    
    bool operator < (const Parameter& p) const {
        return this->parameterValue < p.parameterValue;
        
    }
    
//    string getP1() {
//        return xP1.getParameterValue();
//    }
//
//    string getP2() {
//        return xP2.getParameterValue();
//    }
//    
//    string getOp() {
//        return xOp;
//    }
private:
	string parameterType;
	string parameterValue;
//	Parameter xP1;
//	string xOp;
//	Parameter xP2;
	//multiple constructors for String, ID, and expression

};