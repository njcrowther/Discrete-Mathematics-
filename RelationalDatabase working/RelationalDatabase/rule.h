#pragma once

#include <iostream>
#include <vector>

using namespace std;

class Rule {	//rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
public:
	Rule(Predicate inputHP, Predicate inputP, vector<Predicate> inputPL){
		headPredicate = inputHP;
		predicate = inputP;
		predicateList = inputPL;
	}
	~Rule(){}

	string ruleToString(){
		string returnString = "";
		returnString += headPredicate.predicateToString() + " :- " + predicate.predicateToString();

		for(int i=0; i < predicateList.size(); i++) {
			returnString += "," + predicateList[i].predicateToString();
		}
		

		returnString += ".";
		return returnString;
	}

private:
	Predicate headPredicate;
	Predicate predicate;
	vector<Predicate> predicateList;
};