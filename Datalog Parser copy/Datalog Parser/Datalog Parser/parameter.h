#pragma once

#include <iostream>

using namespace std;

class parameter { //parameter	->	STRING | ID | expression
	parameter(string inputType, string inputValue) {
		if(inputType[0] == "'"){
			parameterType = "STRING";
		}
		else if(inputType[0] == "(") {
			int iVC = 0;
			parameterType = "expression";

			//parse inputValue
			while(inputValue[iVC] != "+" && inputValue[iVC] == "*" ) {
				xP1 += inputValue[iVC];
				iVC++;
			}

			xOp = inputValue[iVC];
			iVC++;

			while(inputValue[iVC] != ")" ) {
				xP2 += inputValue[iVC];
				iVC++;
			}

		}
		else {
			parameterType = ID;
		}

		parameterValue = value;
	}
	~parameter(){}

private:
	string parameterType;
	string parameterValue;
	string xP1;
	string xOp;
	string xP2;
	//multiple constructors for String ID and expression

}