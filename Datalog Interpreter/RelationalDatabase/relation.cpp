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
	Relation returnRelation(getRelationID(), getRelationParameters(), returnSet, returnSet.size());
	
	
	return returnRelation;
}

Relation Relation::selectionL(vector<int> queryIDLocations, vector<string> queryIDs, Relation answerRel) { //Selects on two ID locations having the same string
//	cout << "(SELECTL) Test1" << endl;
	set<Tuple>::iterator it;
	//	set<Tuple> oldTuples = answerSet;
	set<Tuple> oldTuples = answerRel.getRelations();
	set<Tuple> answerSet = answerRel.getRelations();
	
//	cout << "(SELECTL) queryIDLocations size: " << queryIDLocations.size() << endl;
//	cout << "(SELECTL) queryIDs size: " << queryIDs.size() << endl;
//	cout << "(SELECTL) Test2" << endl;
	for (it = oldTuples.begin(); it != oldTuples.end(); it++) {
//		cout << "(SELECTL) Test3" << endl;
		for (int i=0; i < queryIDLocations.size(); i++) {
//			cout << "(SELECTL) Test4" << endl;
			string IDCheck = queryIDs[i];
//			cout << "(SELECTL) Test4.25" << endl;
			string tupleCheck = (*it)[queryIDLocations[i]];
			
//			cout << "(SELECTL) Test4.5" << endl;
			for (int t=i; t < queryIDLocations.size(); t++) {
//				cout << "(SELECTL) Test5" << endl;
				if ((*it)[queryIDLocations[t]] != tupleCheck && queryIDs[t] == IDCheck) {
					answerSet.erase((*it));
				}
//				cout << "(SELECTL) Test6" << endl;
			}
		}
	}
	
	//Create new Relation
	Relation returnRelation(getRelationID(), getRelationParameters(), answerSet, answerSet.size());
	
	return returnRelation;
}

Relation Relation::newSelectionL(vector<int> queryIDLocations, vector<string> queryIDs, Relation answerRel) { //Selects on two ID locations having the same string
	//	cout << "(SELECTL) Test1" << endl;
	set<Tuple>::iterator it;
	//	set<Tuple> oldTuples = answerSet;
	set<Tuple> oldTuples = answerRel.getRelations();
	set<Tuple> answerSet = answerRel.getRelations();
	
	//	cout << "(SELECTL) Test2" << endl;
	for (it = oldTuples.begin(); it != oldTuples.end(); it++) {
		//		cout << "(SELECTL) Test3" << endl;
		for (int i=0; i < queryIDLocations.size(); i++) {
//						cout << "(SELECTL) Test4" << endl;
			string IDCheck = queryIDs[i];
//						cout << "(SELECTL) Test4.25" << endl;
			string tupleCheck = (*it)[queryIDLocations[i]];
			
//						cout << "(SELECTL) Test4.5" << endl;
			for (int t=i; t < queryIDLocations.size(); t++) {
//								cout << "(SELECTL) Test5" << endl;
				if ((*it)[queryIDLocations[t]] != tupleCheck && queryIDs[t] == IDCheck) {
					answerSet.erase((*it));
				}
				//				cout << "(SELECTL) Test6" << endl;
			}
		}
	}
	
	//Create new Relation
	Relation returnRelation(getRelationID(), getRelationParameters(), answerSet, answerSet.size());
	
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
	
	//Project on Parameters
	for (int i=0; i < IDLocations.size(); i++) { // loops through tuple
		map<string,string> checkMap;
		
		if (checkMap.count(queryIDList[i]) == 0) {
			checkMap[queryIDList[i]] = "pants";
			
			//Create new Parameter
			Parameter newParameter("ID", queryIDList[i]);
			ansRelParameters.push_back(newParameter);
			
		}
		
	}
	
	//Project on Relations
	for (it = oldTuples.begin(); it != oldTuples.end(); it++) {
		map<string,string> checkMap;
		Tuple newTuple;
		Tuple thisTuple = (*it);
		
		for (int i=0; i < IDLocations.size(); i++) { // loops through tuple
			
			if (checkMap.count(queryIDList[i]) == 0) {
				checkMap[queryIDList[i]] = thisTuple[IDLocations[i]];
				newTuple.push_back(thisTuple[IDLocations[i]]);
			}
			
		}
		
		if (!newTuple.empty()) {
			newTuples.insert(newTuple);
		}
		
	}
	
	//Idlist needs to be where do I find HPparam in new Scheme
	//Size test
//	cout << "ansRelParameters size is: " << ansRelParameters.size() << endl;
	//Create new Relation
	Relation ansRelation(getRelationID(), ansRelParameters, newTuples, answerRel.getRelationAnswerSize());
	return ansRelation;
}


void Relation::rename(vector<Parameter> queryList) {
//	cout << "Rename1" << endl;
//	cout << "First Query Param is: " << queryList[0].getParameterValue() << endl;
//	cout << "First Relation Param is: " << relationParameters[0].getParameterValue() << endl;
//	cout << "QueryList size is: " << queryList.size() << endl;
//	cout << "RelationParameters size is: " << relationParameters.size() << endl;
	

	for (int i=0; i < relationParameters.size(); i++) {
//		cout << "Rename2" << endl;
		
		if (queryList[i].getParameterType() == "ID") {
//			cout << "Rename " << relationParameters[i].getParameterValue() << " to " << queryList[i].getParameterValue() << endl;
//			relationParameters[i].getParameterValue() = queryList[i].getParameterValue();
			
			setRelationParameter(i, queryList[i]);
//			cout << "Rename4" << endl;
		}
		
//		cout << "Rename5" << endl;
	}
	
//	cout << "Rename6" << endl;
	
	//Need to add possibleP of Predicate to captureVector
}




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

vector<Parameter> Relation::getRelationParameters() {
	return relationParameters;
}

int Relation::getRelationAnswerSize() {
//	cout << "getRelationAnswerSize: " << relAnswerSize << endl;
	return relAnswerSize;
}

//############################################### SET FUNCTIONS #################################
void Relation::setRelationParameter(int location, Parameter value) {
	relationParameters[location] = value;
}

void Relation::setRelations(set<Tuple> newTuples) {
	relations = newTuples;
}

void Relation::setRelationAnswerSize(int answerSize) {
	relAnswerSize = answerSize;
//	cout << "setRelationAnswerSize: " << relAnswerSize << endl;
}

void Relation::insertRelation(Tuple newTuple) {
	relations.insert(newTuple);
}

//############################################### PRINT FUNCTIONS #################################
string Relation::printRelation(vector<Parameter> queryParameters, vector<string> IDPrintVector) {
//	int answerSize2 = relations.size();
//	cout << "answerSize2 is: " << answerSize2 << endl;
	printQuery(queryParameters);
	
//	cout << "getRelationAnswerSize is: " << getRelationAnswerSize() << endl;
	
	if (getRelationAnswerSize() > 0) {
		cout << " Yes(" << getRelationAnswerSize() << ")" << endl;
		printYes(IDPrintVector); //used to be queryParameters;
	}
	else {
		cout << " No" << endl;
	}

    
    return "bob";
}

string Relation::printYes(vector<string> queryParameters) {
    set<Tuple>::iterator it;
	set<Tuple> answers = getRelations();
	
	string tupleValue;
	string tupleString;
	string parameter;
	
	vector<string> parameterPrint = queryParameters;
//	vector<string> parameterPrint = IDPrintVector(queryIDs);
	
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

//string Relation::printYes(set<Tuple> answers, vector<int> queryIDLocations, vector<string> queryIDs) {
//	set<Tuple>::iterator it;
//	
//	string tupleValue;
//	string tupleString;
//	string parameter;
//	
//	vector<string> parameterPrint = IDPrintVector(queryIDs);
//	
//	for (it = answers.begin(); it != answers.end(); it++) {
//		cout << "  ";
//		Tuple printTuple = (*it);
//		
//		for (int i=0; i < printTuple.size(); i++) {
//			tupleValue = (*it)[i];
//			parameter = parameterPrint[i];
//			
//			if ((i+1) == printTuple.size()) {
//				cout << parameter << "=" << tupleValue;
//			}
//			else {
//				cout << parameter << "=" << tupleValue << ", ";
//			}
//			
//		}
//		cout << endl;
//	}
//	
//	
//	
//	return "bob";
//}

vector<string> Relation::IDPrintVector(vector<Parameter> queryIDs) {
	vector<string> returnVector;
	
	for (int i=0; i < queryIDs.size(); i++) {
		if (queryIDs[i].getParameterType() == "ID") {
			returnVector.push_back(queryIDs[i].getParameterValue());
		}
	}
	
	
	
//	for (int i=0; i < queryIDs.size(); i++) {
//		bool found = false;
//		
//		for (int t=0; t < returnVector.size(); t++) {
//			if (queryIDs[i].getParameterValue() == returnVector[t]) {
//				found = true;
//			}
//		}
//		
//		if (!found) {
//			returnVector.push_back(queryIDs[i].getParameterValue());
//		}
//	}
	
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




