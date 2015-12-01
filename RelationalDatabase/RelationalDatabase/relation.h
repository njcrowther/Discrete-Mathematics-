//
//  relation.h
//  RelationalDatabase
//
//  Created by Nathan Crowther on 10/20/15.
//  Copyright © 2015 Nathan Crowther. All rights reserved.
//
#pragma once
#include "tuple.h"
#include "parameter.h"
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <sstream>


using namespace std;

class Relation {
    //Scheme describes a relation. Facts describe the contents of a relation
public:
    Relation(){}
    Relation(string key, vector<Parameter> parameters){
        relationKey = key;
        relationParameters = parameters;
    }
	Relation(string key, vector<Parameter> parameters, set<Tuple> relationSet) {
		relationKey = key;
		relationParameters = parameters;
		relations = relationSet;
	}
    ~Relation(){}
    
    void addRelation(Tuple relation);
    
	
//############################################### RELATION FUNCTIONS #################################
	set<Tuple> projection(set<Tuple> answerSet, vector<int> queryIDLocations, vector<string> queryIDList);
	set<Tuple> projection(Relation answerRel, vector<int> queryIDLocations, vector<string> queryIDList);
	
	set<Tuple> selectionV(vector<string> variables, vector<int> locations);
	Relation selectionV(vector<string> variables, vector<int> locations);
	
	set<Tuple> selectionL(vector<int> queryIDLocations, vector<string> queryIDs, set<Tuple> answerSet);
	Relation selectionL(vector<int> queryIDLocations, vector<string> queryIDs, Relation answerRel);

	void rename(vector<Parameter> PList);

	//############################################### HELPER FUNCTIONS #################################
	bool IDDuplicateChecker(vector<Parameter> queryList);
    
	
	
	//############################################### SIZE FUNCTIONS #################################
    int getSize();
    int getRelationParameterSize();
	
	
	//############################################### GET FUNCTIONS #################################
    string getRelationID();
	set<Tuple> getRelations();
	vector<Parameter> getRelationParameters();
	
	//############################################### PRINT FUNCTIONS #################################
	string printRelation(int answerSize, set<Tuple> answers, vector<Parameter> queryParameters, vector<string> queryIDs, vector<int> queryIDLocations);
	string printYes(set<Tuple> answers, vector<int> queryIDLocations, vector<string> queryIDs);
	
	void printQuery(vector<Parameter> queryParameters);
	string relationPrinter(set<Tuple> answers, vector<string> queryIDs);
	vector<string> IDPrintVector(vector<string> queryParameters);
 

private:
    string relationKey;
    vector<Parameter> relationParameters;
    set<Tuple> relations;
};
