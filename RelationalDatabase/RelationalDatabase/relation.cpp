//
//  relation.cpp
//  RelationalDatabase
//
//  Created by Nathan Crowther on 10/23/15.
//  Copyright © 2015 Nathan Crowther. All rights reserved.
//

#include "relation.h"

using namespace std;

void Relation::addRelation(Tuple relation) {
    relations.insert(relation);
}

//############################################### NEW RELATION FUNCTIONS #################################
Relation Relation::selectionV(vector<string> queryStrings, vector<int> queryStringLocations) { //Selects on a string
	set<Tuple>::iterator it;
	set<Tuple> oldTuples = getRelations();
	set<Tuple> newTuples;
	set<Tuple> returnSet = oldTuples;
	
	
	for (it = oldTuples.begin(); it != oldTuples.end(); it++) {
		
		for (int i=0; i < queryStringLocations.size(); i++) {
			
			
			if (queryStrings[i] == (*it)[queryStringLocations[i]]) {
				
				newTuples.insert(*it);
				returnSet = newTuples;
			}
			else {
				newTuples.erase(*it);
				returnSet = newTuples;
				break;
			}
			
		}
		
	}
	
	//Create new Relation
	Relation returnRelation(getRelationID(), getrelationParameters(), returnSet);
	
	
	return returnRelation;
}

Relation Relation::selectionL(vector<int> queryIDLocations, vector<string> queryIDs, Relation answerRel) { //Selects on two ID locations having the same string
	set<Tuple>::iterator it;
//	set<Tuple> oldTuples = answerSet;
	set<Tuple> oldTuples = answerRel.getRelations();
	
	for (it = oldTuples.begin(); it != oldTuples.end(); it++) {
		
		for (int i=0; i < queryIDLocations.size(); i++) {
			
			string IDCheck = queryIDs[i];
			string tupleCheck = (*it)[queryIDLocations[i]];
			
			for (int t=i; t < queryIDLocations.size(); t++) {
				
				if ((*it)[queryIDLocations[t]] != tupleCheck && queryIDs[t] == IDCheck) {
					answerSet.erase((*it));
				}
			}
		}
	}
	
	//Create new Relation
	Relation returnRelation(getRelationID(), getrelationParameters(), answerSet);
	
	return returnRelation;
}


Relation Relation::projection(Relation answerRel, vector<int> IDLocations, vector<string> queryIDList) {
	//map ID's to a value?
	//S -> gives count of answers
	//P/R -> gives answers
	
	set<Tuple>::iterator it;
	set<Tuple> oldTuples = answerRel.getRelations();
	set<Tuple> newTuples;
	vector<Parameter> ansRelParameters;
	
	for (it = oldTuples.begin(); it != oldTuples.end(); it++) {
		map<string,string> checkMap;
		Tuple newTuple;
		Tuple thisTuple = (*it);
		
		for (int i=0; i < IDLocations.size(); i++) { // loops through tuple
			
			if (checkMap.count(queryIDList[i]) == 0) {
				checkMap[queryIDList[i]] = thisTuple[IDLocations[i]];
				newTuple.push_back(thisTuple[IDLocations[i]]);
				
				//Create new Parameter
				Parameter newParameter("ID", queryIDList[i]);
				ansRelParameters.push_back(newParameter);
			}
			
		}
		
		if (!newTuple.empty()) {
			newTuples.insert(newTuple);
		}
		else {}
	}
	
	//Create new Relation
	Relation ansRelation(getRelationID(), ansRelParameters, newTuples);
	return ansRelation;
}


void Relation::rename(vector<Parameter> queryList) {
	for (int i=0; i < relationParameters.size(); i++) {
		if (queryList[i].getParameterType() == "ID") {
			relationParameters[i].getParameterValue() = queryList[i].getParameterValue();
		}
		
	}
}

//############################################### RELATION FUNCTIONS #################################
//set<Tuple> Relation::selectionV(vector<string> queryStrings, vector<int> queryStringLocations) { //Selects on a string
//    set<Tuple>::iterator it;
//	set<Tuple> oldTuples = getRelations();
//	set<Tuple> newTuples;
//	set<Tuple> returnSet = oldTuples;
//	
//
//	for (it = oldTuples.begin(); it != oldTuples.end(); it++) {
//		
//		for (int i=0; i < queryStringLocations.size(); i++) {
//
//			
//			if (queryStrings[i] == (*it)[queryStringLocations[i]]) {
//
//				newTuples.insert(*it);
//				returnSet = newTuples;
//			}
//			else {
//				newTuples.erase(*it);
//				returnSet = newTuples;
//				break;
//			}
//			
//		}
//	
//	}
//	
//	
//
//    return returnSet;
//}
//
//set<Tuple> Relation::selectionL(vector<int> queryIDLocations, vector<string> queryIDs, set<Tuple> answerSet) { //Selects on two ID locations having the same string
//	set<Tuple>::iterator it;
//	set<Tuple> oldTuples = answerSet;
//	
//	for (it = oldTuples.begin(); it != oldTuples.end(); it++) {
//		
//		for (int i=0; i < queryIDLocations.size(); i++) {
//			
//			string IDCheck = queryIDs[i];
//			string tupleCheck = (*it)[queryIDLocations[i]];
//			
//			for (int t=i; t < queryIDLocations.size(); t++) {
//				
//				if ((*it)[queryIDLocations[t]] != tupleCheck && queryIDs[t] == IDCheck) {
//					answerSet.erase((*it));
//				}
//			}
//		}
//	}
//	
//	return answerSet;
//}
//
//
//set<Tuple> Relation::projection(set<Tuple> answerSet, vector<int> IDLocations, vector<string> queryIDList) {
//	//map ID's to a value?
//	//S -> gives count of answers
//	//P/R -> gives answers
//
//	set<Tuple>::iterator it;
//	set<Tuple> oldTuples = answerSet;
//	set<Tuple> newTuples;
//	
//	for (it = oldTuples.begin(); it != oldTuples.end(); it++) {
//		map<string,string> checkMap;
//		Tuple newTuple;
//		Tuple thisTuple = (*it);
//
//		for (int i=0; i < IDLocations.size(); i++) { // loops through tuple
//
//			if (checkMap.count(queryIDList[i]) == 0) {
//				checkMap[queryIDList[i]] = thisTuple[IDLocations[i]];
//				newTuple.push_back(thisTuple[IDLocations[i]]);
//			}
//
//		}
//		
//		if (!newTuple.empty()) {
//			newTuples.insert(newTuple);
//		}
//		else {}
//	}
//
//    return newTuples;
//}
//
//
//void Relation::rename(vector<Parameter> queryList) {
//    for (int i=0; i < relationParameters.size(); i++) {
//        if (queryList[i].getParameterType() == "ID") {
//            relationParameters[i].getParameterValue() = queryList[i].getParameterValue();
//        }
//        
//    }
//}


//############################################### HELPER FUNCTIONS #################################




//############################################### SIZE FUNCTIONS #################################
int Relation::getSize() {
    return relations.size();
}

int Relation::getRelationParameterSize() {
    return relationParameters.size();
}

//############################################### GET FUNCTIONS #################################
set<Tuple> Relation::getRelations() {
    return relations;
}

string Relation::getRelationID() {
//	cout << "getRelationID(): " << relationKey << endl;
	return relationKey;
}

vector<Parameter> Relation::getrelationParameters() {
	return relationParameters;
}

//############################################### PRINT FUNCTIONS #################################
string Relation::printRelation(int answerSize, set<Tuple> answers, vector<Parameter> queryParameters, vector<string> queryIDs, vector<int> queryIDLocations) {
	
	printQuery(queryParameters);
	
	if (answerSize > 0) {
		cout << " Yes(" << answerSize << ")" << endl;
		printYes(answers, queryIDLocations, queryIDs);
	}
	else {
		cout << " No" << endl;
	}

    
    return "bob";
}

string Relation::printYes(set<Tuple> answers, vector<int> queryIDLocations, vector<string> queryIDs) {
    set<Tuple>::iterator it;
    string tupleValue;
	string tupleString;
	string parameter;
	
	vector<string> parameterPrint = IDPrintVector(queryIDs);
	
    for (it = answers.begin(); it != answers.end(); it++) {
        cout << "  ";
		Tuple printTuple = (*it);
	
        for (int i=0; i < printTuple.size(); i++) {
            tupleValue = (*it)[i];
			parameter = parameterPrint[i];
			
			if ((i+1) == printTuple.size()) {
				cout << parameter << "=" << tupleValue;
			}
			else {
				cout << parameter << "=" << tupleValue << ", ";
			}
			
        }
        cout << endl;
    }
    
    
    
    return "bob";
}

vector<string> Relation::IDPrintVector(vector<string> queryIDs) {
	vector<string> returnVector;
	
	for (int i=0; i < queryIDs.size(); i++) {
		bool found = false;
		
		for (int t=0; t < returnVector.size(); t++) {
			if (queryIDs[i] == returnVector[t]) {
				found = true;
			}
		}
		
		if (!found) {
			returnVector.push_back(queryIDs[i]);
		}
	}
	
	return returnVector;
}


void Relation::printQuery(vector<Parameter> queryParameters) {
	cout << getRelationID() << "(";
	for (int i=0; i < queryParameters.size(); i++) {
		if ((i+1) == queryParameters.size()) {
			cout << queryParameters[i].getParameterValue();
		}
		else {
			cout << queryParameters[i].getParameterValue() << ",";
		}
		
	}
	cout << ")?";
}




