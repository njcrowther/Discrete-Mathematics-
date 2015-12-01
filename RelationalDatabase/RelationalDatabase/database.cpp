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

set<Tuple> database::queryAnswer(string ID, vector<Parameter> queryList) {
    //Variables
	set<Tuple> answerSet;
	
	
    Relation checkAgainstRel = databaseMap[ID]; //copy Relation
	
    vector<string> queryStringVector = queryStrings(queryList);                 //Gets the vector of Strings from the Query FOR SELECTION
    vector<int> queryStringLocations = queryListStringLocations(queryList);     //Gets the locations of the strings in the Query FOR SELECTION
    vector<int> queryIDLocations = queryListIDLocations(queryList);             //Gets the ID Locations in the query FOR PROJECTION
	vector<string> queryIDList = queryIDs(queryList);
	
    //Selection
    answerSet = checkAgainstRel.selectionV(queryStringVector, queryStringLocations);
//	cout << "First Selection Size: " << answerSet.size() << endl;
	
	//Select on multiple same variables
	answerSet = checkAgainstRel.selectionL(queryIDLocations, queryIDList, answerSet);
	int answerSize = answerSet.size();
//	cout << "Second Selection Size: " << answerSet.size() << endl;
	
//	cout << endl << endl << "After Select: " << endl;
//	checkAgainstRel.printRelation(answerSize, answerSet, queryList);
	
    //Projection
    answerSet = checkAgainstRel.projection(answerSet, queryIDLocations, queryIDList);
//	cout << endl << endl << "After Project: " << endl;
//	checkAgainstRel.printRelation(answerSize, answerSet, queryList);
	
    //Rename
    checkAgainstRel.rename(queryList);
	checkAgainstRel.printRelation(answerSize, answerSet, queryList, queryIDList, queryIDLocations);
	
    return answerSet;
}

//############################################### HELPER FUNCTIONS #################################
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

