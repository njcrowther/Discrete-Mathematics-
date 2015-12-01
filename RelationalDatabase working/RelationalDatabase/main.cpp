#include "datalogProgram.h"
#include "LexAnalyzer.h"
#include "Tokens.h"
#include "predicate.h"
#include "database.h"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;



int main(int argc,char* argv[]){
	ifstream in;
	string outString;
	
	in.open(argv[1]);
    
//    cout << argv[1] << endl;

	if(in.is_open()){	//Check if file is open
		cout << "It's open!" << endl;
		LexAnalyzer lex = LexAnalyzer(in);
		vector<Tokens> outVector = lex.tokenize(); //OutVector is the vector of Tokens created from Lab 1
		// outString = lex.toString(outVector); //For Analyzer Output
		// cout << outString;

		datalogProgram dL = datalogProgram(outVector);
		bool success = dL.parser();
		
        database dB = database(dL);
		
		
		//Could probably make this into it's own function
		if(success){
			cout << "Success!" << endl;
			//Print
			dL.printSchemes();
			dL.printFacts();
			dL.printRules();
			dL.printQueries();
			dL.printDomain();
			
		}
		else {
			// cout << "Failure!" << endl;
		}
		return 1;
	}
	else{
		 cout << "It's broken" << endl;
		return 2;
	}
}