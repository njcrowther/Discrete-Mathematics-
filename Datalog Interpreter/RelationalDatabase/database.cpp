//
//  database.cpp
//  RelationalDatabase
//
//  Created by Nathan Crowther on 10/22/15.
//  Copyright © 2015 Nathan Crowther. All rights reserved.
//

#include "database.h"
#include "predicate.h"
#include "relation.h"

/*
    1. Create new relation or modify old one? Mapping to same relation
 */


using namespace std;

Relation database::queryAnswer(string ID, vector<Parameter> queryList) {
//	cout << "NEW QUERY!" << endl;
	
	//Variables
	set<Tuple> answerSet;
	Relation answerRel;
	
//	cout << "(QUERYANSWER) Test1" << endl;
    Relation checkAgainstRel = databaseMap[ID]; //copy Relation

//	cout << "(QUERYANSWER) Test2" << endl;
    vector<string> queryStringVector = queryStrings(queryList);                 //Gets the vector of Strings from the Query FOR SELECTION
    vector<int> queryStringLocations = queryListStringLocations(queryList);     //Gets the locations of the strings in the Query FOR SELECTION
    vector<int> queryIDLocations = queryListIDLocations(queryList);             //Gets the ID Locations in the query FOR PROJECTION
	vector<string> queryIDList = queryIDs(queryList);
	
//	cout << "(QUERYANSWER) Test3" << endl;
    //Selection
    answerRel = checkAgainstRel.selectionV(queryStringVector, queryStringLocations);
	
//	cout << "(QUERYANSWER) Test4" << endl;
	//Select on multiple same variables
	answerRel = checkAgainstRel.selectionL(queryIDLocations, queryIDList, answerRel);
//	cout << "answerRel size (queryAnswer): " << answerRel.getRelations().size() << endl;
	
	//Do I need this?
//	answerRel.setRelationAnswerSize(answerRel.getRelations().size());
//	int answerSize = answerRel.getRelations().size();
	
//	cout << "(QUERYANSWER) Test5" << endl;
    //Projection
    answerRel = checkAgainstRel.projection(answerRel, queryIDLocations, queryIDList);
	
//	cout << "(QUERYANSWER) Test6" << endl;
    //Rename
    answerRel.rename(queryList);
	
//	cout << "(QUERYANSWER) Test7" << endl;
//	answerRel.printRelation(answerSize, queryList);
//	answerRel.printRelation(answerSize, answerSet, queryList, queryIDList, queryIDLocations);

    return answerRel;
}







/* While predicateList isn't empty
 1. Get database tables
 2. Compare matching variables
 3.
 
 */
void database::join(vector<Rule> ruleVector) {
	//MARK: Properties
	bool didChange = true;
	bool hasChanged = true;
//	vector<Predicate>::iterator it;
//	cout << "(JOIN) Test1" << endl;
	
	

	while (hasChanged) {	//Analyze rules until nothing changes
		hasChanged = false;
		
		//		int beforeSize = databaseMap.size();
//		cout << "beforeSize is: " << beforeSize << endl;

		//For each rule
//		cout << "(JOIN) Number of Times Through Rule Vector: " << timeThrough << endl;
		
		int ruleNumber = 1;
		for (int i=0; i < ruleVector.size(); i++) {
			//MARK: Rule Properties
			bool isFirstPred = true;
			vector<Parameter> rel1NewParams;
			vector<Parameter> rel2NewParams;
			Relation rel1;
			Relation rel2;
			vector<Predicate> predicateList = ruleVector[i].getPredicateList();
			int beforeSize = databaseMap[ruleVector[i].getHeadPredicate().getPredicateID()].getRelations().size();
			
//			cout << "(JOIN) RULE NUMBER: " << ruleNumber << endl;

			//Get before size
//			cout << "(JOIN) Test3" << endl;
			
			
			
			
			//This section takes care of the first predicate and sets up for the while loop
			Predicate firstPredicate = ruleVector[i].getPredicate();
			
			int predicateNumber = 1;
//			cout << "firstPredicateID is: " << firstPredicate.getPredicateID() << endl;
			predicateNumber++;
			
//			cout << "(JOIN) firstPredicateID is: " << firstPredicate.getPredicateID() << endl;
			vector<Parameter> rel1FirstNewParams = vectorAdder(firstPredicate.getParameterList(), firstPredicate.getParameter());
			
//			cout << "(JOIN) Test4" << endl;
			//Test print rel1NewParams
//			cout << "(JOIN) rel1FirstNewParams size: " << rel1FirstNewParams.size() << endl;
//			cout << "(Join) rel1NewParams are: ";
//			for (int i=0; i < rel1FirstNewParams.size(); i++) {
//				cout << rel1FirstNewParams[i].getParameterValue() << " ";
//			}
//			cout << endl;
			
			Relation oldRelation = databaseMap[ruleVector[i].getPredicate().getPredicateID()];
			//MAY NOT BE CORRECT
			oldRelation = queryAnswer(oldRelation.getRelationID(), rel1FirstNewParams);

//			cout << "(JOIN) Test5" << endl;
		
		//While the rule hasn't been fully analyzed
			for (int z=0; z < predicateList.size(); z++) {
//				cout << "predicateNumber: " << predicateNumber << endl;
//				cout << "predicateID is: " << predicateList[z].getPredicateID() << endl;
				predicateNumber++;
				
				rel1 = oldRelation;
				rel2 = databaseMap[predicateList[z].getPredicateID()];

				
//				cout << "(JOIN) Test6" << endl;
				
				//Needs to update rel1Params
				if (isFirstPred) {
//					cout << "rel1FirstNewParams" << endl;
					rel1NewParams = rel1FirstNewParams;
					isFirstPred = false;
				}
				else {
//					cout << "rel1.getRelationParameters" << endl;
					rel1NewParams = rel1.getRelationParameters();
				}
				
//				cout << "rel2NewParams ParameterList size: " << predicateList[z].getParameterList().size() << endl;
//				cout << "rel2NewParams Parameter is: " << predicateList[z].getParameter().getParameterValue() << endl;
				rel2NewParams = vectorAdder(predicateList[z].getParameterList(), predicateList[z].getParameter());
//				cout << "rel2NewParams New size: " << rel2NewParams.size() << endl;
				
				//Run Relations as queries
//				cout << "(JOIN) Test7" << endl;
//				rel1 = queryAnswer(rel1.getRelationID(), rel1NewParams);
				
//				cout << "(JOIN) Test7.5" << endl;
				rel2 = queryAnswer(rel2.getRelationID(), rel2NewParams);
				
//				cout << "(JOIN) Test8" << endl;
			
			//Join Relations
				//Get new parameters
				vector<Parameter> newRelParameters = parameterJoiner(rel1, rel2);
				
				
				//Get tuple set
				set<Tuple> newTuples = tupleJoiner(rel1, rel2);
				//Get relation name (use rel1 ID every time? shouldn't matter?)
				string relationID = rel1.getRelationID();
				
				//Create New Relation
//				cout << "New Tuples Size: " << newTuples.size();
				Relation newRelation(relationID, newRelParameters, newTuples, newTuples.size());
				
//				cout << "(JOIN) Test9" << endl;
				
				oldRelation = newRelation;
				
//				cout << "(JOIN) Test10" << endl;
				
			}
			
//			cout << "headPredicate relations size before union: " << databaseMap[ruleVector[i].getHeadPredicate().getPredicateID()].getRelations().size() << endl;
//
////TEST
//			cout << "(Join) out of predicate List" << endl;

			
			//Union
			didChange = Union(ruleVector[i].getHeadPredicate(), oldRelation);
			
//			cout << "headPredicate relations size after union: " << databaseMap[ruleVector[i].getHeadPredicate().getPredicateID()].getRelations().size() << endl;
			
			if (didChange) {
				hasChanged = true;
			}
			ruleNumber++;

//			cout << "(JOIN) Test11" << endl;
			
		}
		//Save how many times through
		setTimeThrough();
	}
}

bool database::Union(Predicate headPredicate, Relation newRelation) {
	int beforeSize = 0;
	int afterSize = 0;
	
	//What if there are no facts for DeaUoo?
	//Project newRelation
	Relation headRelation = databaseMap[headPredicate.getPredicateID()];
	
	vector<Parameter> headRelationParameters = vectorAdder(headPredicate.getParameterList(), headPredicate.getParameter());
	
//	newRelation.rename(headRelationParameters);
	
	vector<int> IDLocations = unionIDLocations(headRelationParameters, newRelation.getRelationParameters());
	
	vector<string> IDList = unionIDs(headRelationParameters, newRelation.getRelationParameters());
	
//	cout << "(Union) headRelationParameters size: " << headRelationParameters.size() << endl;
//	cout << "(UNION) newRelationParameters size: " << newRelation.getRelationParameterSize() << endl;
//	cout << "(Union) IDLocations size: " << IDLocations.size() << endl;
//	cout << "(Union) IDs size: " << IDList.size() << endl;
	
	Relation ansRel = headRelation.projection(newRelation, IDLocations, IDList);
	
//	cout << "(UNION) ansRel size: " << ansRel.getRelations().size() << endl;
	
	//Test print ansRel
//	cout << "(Union) ansRel: " << endl;
//	ansRel.printRelation(ansRel.getRelationAnswerSize(), ansRel.getRelationParameters());
//	cout << "printed it" << endl;
	
	beforeSize = databaseMap[headPredicate.getPredicateID()].getRelations().size();
	
	tupleAdder(headRelation,ansRel);
	
	afterSize = databaseMap[headPredicate.getPredicateID()].getRelations().size();
	
//	vector<Parameter> newRelParameters = headRelationParameters;
//	cout << "(JOIN) newRelParameters are: ";
//	for (int i=0; i < newRelParameters.size(); i++) {
//		cout << newRelParameters[i].getParameterValue() << ", ";
//	}
//	cout << endl;
	
	
	if (afterSize > beforeSize) {
		return true;
	}
	else return false;

}

//############################################### HELPER FUNCTIONS #################################
bool database::changeCheck(int startSize, int endSize) {
	
	for (int i=0; i < databaseMap.size(); i++) {

	}
	
	
	return true;
}

set<Tuple> database::tupleAdder(Relation headRelation, Relation ansRel) {
	set<Tuple> newTuples = databaseMap[headRelation.getRelationID()].getRelations();
	set<Tuple>::iterator itAR;

	//Get tuples from answer and headRelation
	set<Tuple> ansRelTuples = ansRel.getRelations();
//	set<Tuple> headRelationTuples = headRelation.getRelations();
	
	//Add answer tuples to headRelation tuples
//	for (itHR = headRelationTuples.begin(); itHR != headRelationTuples.end(); itHR++) {
//		newTuples.insert((*itHR));
//	}


	
	for (itAR = ansRelTuples.begin(); itAR != ansRelTuples.end(); itAR++) {
		databaseMap[headRelation.getRelationID()].addRelation((*itAR));
	}
	
	//Save
//	databaseMap[headRelation.getRelationID()].setRelations(headRelationTuples);
	
	return newTuples;

}


set<Tuple> database::tupleJoiner(Relation rel1, Relation rel2) {
	set<Tuple>::iterator it1;
	set<Tuple>::iterator it2;
	set<Tuple> rel1Tuples = rel1.getRelations();
	set<Tuple> rel2Tuples = rel2.getRelations();
	set<Tuple> newTuples;
	map<string,string> tup1Map;
	map<string,string> tup2Map;
	
	
	for (it1 = rel1Tuples.begin(); it1 != rel1Tuples.end(); it1++) {
		for (it2 = rel2Tuples.begin(); it2 != rel2Tuples.end(); it2++) {
			if (isJoinable((*it1), (*it2), rel1.getRelationParameters(), rel2.getRelationParameters())) {
				
				Tuple newTuple = joinTuples((*it1), (*it2), rel1.getRelationParameters(), rel2.getRelationParameters());
				newTuples.insert(newTuple);
				

			}
//			else {
//				//don't add it to new relation
//			}
		}
	}
	
	return newTuples;
}

bool database::isJoinable(Tuple tup1, Tuple tup2, vector<Parameter> scheme1, vector<Parameter> scheme2) {
	
	for (int i=0; i < tup1.size(); i++) {

		for (int z=0; z < tup2.size(); z++) {

			if (scheme1[i].getParameterValue() == scheme2[z].getParameterValue() && tup1[i] != tup2[z]) {

				return false;
			}
		}
	}
	
	return true;
}

Tuple database::joinTuples(Tuple tup1, Tuple tup2, vector<Parameter> scheme1, vector<Parameter> scheme2) {
	Tuple returnTuple;
	map<string,string> addedMap;
	
	for (int i=0; i < tup1.size(); i++) {
		addedMap[scheme1[i].getParameterValue()] = tup1[i];
		returnTuple.push_back(tup1[i]);
	}
	
	for (int z=0; z < tup2.size(); z++) {
		if (addedMap.count(scheme2[z].getParameterValue()) == 0) {
			returnTuple.push_back(tup2[z]);
		}
	}
	
	return returnTuple;
}

vector<Parameter> database::parameterJoiner(Relation rel1, Relation rel2) {
	map<string,string> checkMap;
	vector<Parameter> rel1P = rel1.getRelationParameters();
	vector<Parameter> rel2P = rel2.getRelationParameters();
	vector<Parameter> newRelParameters;
	
//	cout << "New Parameters are: (";
	
	for (int i=0; i < rel1P.size(); i++) {
		
		if (checkMap.count(rel1P[i].getParameterValue()) == 0 ) {
			checkMap[rel1P[i].getParameterValue()] = "pants";
			newRelParameters.push_back(rel1P[i]);
//			cout << rel1P[i].getParameterValue() << ",";
		}
		
	}
	
	for (int z=0; z < rel2P.size(); z++) {

		if (checkMap.count(rel2P[z].getParameterValue()) == 0) {
			checkMap[rel2P[z].getParameterValue()] = "pants";
			newRelParameters.push_back(rel2P[z]);
//			cout << rel2P[z].getParameterValue() << ",";
		}
		
	}
	
//	cout << ")" << endl;
	
	return newRelParameters;
}

vector<int> database::unionIDLocations(vector<Parameter> headParameters, vector<Parameter> predParameters) {
	vector<int> IDLocations;
	
	for (int i=0; i < headParameters.size(); i++) {
//		cout << "(unionIDLocations) headParameter is: " << headParameters[i].getParameterValue() << endl;
		for (int z=0; z < predParameters.size(); z++) {
//			cout << "(unionIDLocations) predParameters is: " << predParameters[i].getParameterValue() << endl;
			if (headParameters[i].getParameterValue() == predParameters[z].getParameterValue()) {
				IDLocations.push_back(z);
			}
		}
	}
	
	return IDLocations;
}

vector<string> database::unionIDs(vector<Parameter> headParameters, vector<Parameter> predParameters) {
	vector<string> IDs;
	
	for (int i=0; i < headParameters.size(); i++) {
		for (int z=0; z < predParameters.size(); z++) {
			if (headParameters[i].getParameterValue() == predParameters[z].getParameterValue()) {
				IDs.push_back(predParameters[z].getParameterValue());
			}
		}
	}
	
	return IDs;
}

vector<Parameter> database::vectorAdder(vector<Parameter> vector, Parameter headP) {
	vector.insert(vector.begin(), headP);
	return vector;
}

vector<Predicate> database::vectorPredAdder(vector<Predicate> vector, Predicate firstP) {
	vector.insert(vector.begin(), firstP);
	return vector;
}

vector<string> database::queryStrings(vector<Parameter> queryList) {
    vector<string> returnVector;
    
    for (int i=0; i<queryList.size(); i++) {
        if (queryList[i].getParameterType() == "STRING") {
            returnVector.push_back(queryList[i].getParameterValue());
        }
    }
    
    return returnVector;
}

vector<string> database::queryIDs(vector<Parameter> queryList) {
    vector<string> returnVector;
    
    for (int i=0; i< queryList.size(); i++) {
        if (queryList[i].getParameterType() == "ID") {
            returnVector.push_back(queryList[i].getParameterValue());
        }
    }
    
    return returnVector;
}

vector<int> database::queryListStringLocations(vector<Parameter> queryList) {
    vector<int> returnVector;
    
    for (int i=0; i<queryList.size(); i++) {
        if (queryList[i].getParameterType() == "STRING") {
            returnVector.push_back(i);
        }
    }
    
    return returnVector;
}

vector<int> database::queryListIDLocations(vector<Parameter> queryList) {
    vector<int> returnVector;
    
    for (int i=0; i<queryList.size(); i++) {
        if (queryList[i].getParameterType() == "ID") {
            returnVector.push_back(i);
        }
    }
    
    return returnVector;
}

void database::setTimeThrough() {
	timeThrough++;
}

int database::getTimeThrough() {
	return timeThrough;
}
