#pragma once

#include "Tokens.h"
#include "predicate.h"
#include "rule.h"
#include "parameter.h"
#include "database.h"

#include <vector>
#include <iostream>
#include <set>

using namespace std;

/*
	Facts and Rules can be empty
	Watch for spaces at end of items
	Failure value should be in double quotes
*/
class datalogProgram {
public:
	datalogProgram(vector<Tokens> inputVector, database dB){
		analyzedVector = inputVector;
		vC = 0;
        myDatabase = dB;
		// captureVector; empty the vector
	}
	~datalogProgram(){}


	bool parser();

	string match(string matchItem);

	void parseScheme();					//scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
	void parseSchemeList();				//schemeList	->	scheme schemeList | lambda

	void parseIDList();					//idList  	->	COMMA ID idList | lambda

	void parseFact();					//fact    	-> 	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
	void parseFactList();				//factList	->	fact factList | lambda

	void parseRule();					//rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
	void parseRuleList();				//ruleList	->	rule ruleList | lambda	

	Predicate parseHeadPredicate();			//headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
	Predicate parsePredicate(bool firstPred);				//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	void parsePredicateList();			//predicateList	->	COMMA predicate predicateList | lambda

	Parameter parseParameter();				//parameter	->	STRING | ID | expression
	void parseParameterList();			//parameterList	-> 	COMMA parameter parameterList | lambda

	Parameter parseExpression();				//expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN
	string parseOperator();				//operator	->	ADD | MULTIPLY

	void parseQuery();					//query	        ->      predicate Q_MARK
	void parseQueryList();				//queryList	->	query queryList | lambda

	void parseStringList();				//stringList	->	COMMA STRING stringList | lambda 

	//Helper Functions
	vector<Parameter> vectorShaver(vector<Parameter> inputVector);
    vector<Parameter> vectorAdder(vector<Parameter> oldVector, Parameter headP);
	vector<Predicate> predVectorAdder(vector<Predicate> oldVector, Predicate headP);
	
	void printSchemes();
	void printFacts();
	void printRules();
	void printQueries();
	void printDomain();
    
    vector<Predicate> getSchemeVector();
    vector<Predicate>getFactVector();
    vector<Rule> getRuleVector();
    vector<Predicate> getQueryVector();


private:
	vector<Tokens> analyzedVector;		//Vector created in Lab 1 - Lexicon Analyzer
	vector<Parameter> captureVector;		//Vector that catches Parameters
	vector<Predicate> ruleCaptureVector;//Captures Predicates to use in creating a rule
	vector<Predicate> queryCaptureVector;//Captures Predicates to use in creating a query

	//These vectors capture Schemes, Facts, Rules, and Queries
	vector<Predicate> schemeVector;		
	vector<Predicate> factVector;
	vector<Rule> ruleVector;
	vector<Predicate> queryVector;

	//Set for Facts
	set<Parameter> factStringsSet;
	
    //My Database
    database myDatabase;

	int vC;
	int vC2;
};