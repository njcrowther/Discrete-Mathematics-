#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Tokens {
	public:
		Tokens(string, string, int);
		~Tokens(){}

		string getType();

		string getValue();

		string getLine();

		string toString();

	private:
		string type;
		string val;
		string line;	

};