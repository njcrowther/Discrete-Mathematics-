#pragma once

#include <iostream>
#include <vector>
#include "predicate.h"

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
	
	Predicate getPredicate() {
		return predicate;
	}
	
	vector<Predicate> getPredicateList() {
		return predicateList;
	}
	
	Predicate getHeadPredicate() {
		return headPredicate;
	}

private:
	Predicate headPredicate;
	Predicate predicate;
	vector<Predicate> predicateList;
};