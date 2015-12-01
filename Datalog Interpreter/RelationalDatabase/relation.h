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

//NOTE: recently changed Relation object to take things by reference. 

using namespace std;

class Relation {
    //Scheme describes a relation. Facts describe the contents of a relation
public:
    Relation(){}
    Relation(string key, vector<Parameter> parameters){
        relationKey = key;
        relationParameters = parameters;
		relAnswerSize = 0;
    }
	Relation(string key, vector<Parameter> parameters, set<Tuple> newRelations, int answerSize){
		relationKey = key;
		relationParameters = parameters;
		relations = newRelations;
		relAnswerSize = answerSize;
	}
    ~Relation(){}
    
    void addRelation(Tuple relation);
	
//############################################### NEW RELATION FUNCTIONS ##############################
	Relation selectionV(vector<string> queryStrings, vector<int> queryStringLocations);
	
	Relation selectionL(vector<int> queryIDLocations, vector<string> queryIDs, Relation answerRel);
	
	Relation newSelectionL(vector<int> queryIDLocations, vector<string> queryIDs, Relation answerRel);
	
	Relation projection(Relation answerRel, vector<int> queryIDLocations, vector<string> queryIDList);
	
	
	
//############################################### OLD RELATION FUNCTIONS ##############################
	
//    set<Tuple> selectionV(vector<string> variables, vector<int> locations);
//	
//	set<Tuple> selectionL(vector<int> queryIDLocations, vector<string> queryIDs, set<Tuple> answerSet);
//    
//    set<Tuple> projection(set<Tuple> answerSet, vector<int> queryIDLocations, vector<string> queryIDList);
	
    void rename(vector<Parameter> PList);
	
	
//	bool IDDuplicateChecker(vector<Parameter> queryList);
	



	
//############################################### SIZE FUNCTIONS #################################
    int getSize();
    int getRelationParameterSize();
	
	
//############################################### GET FUNCTIONS #################################
    string getRelationID();
	set<Tuple> getRelations();
	vector<Parameter> getRelationParameters();
	int getRelationAnswerSize();

//############################################### SET FUNCTIONS #################################	
	void setRelationParameter(int location, Parameter value);
	void setRelations(set<Tuple> newTuples);
	void setRelationAnswerSize(int answerSize);
	void insertRelation(Tuple newTuple);
	
//############################################### PRINT FUNCTIONS #################################
	string printRelation(vector<Parameter> queryParameters, vector<string> printIDs);
	string printYes(vector<string> queryParameters);
	
	void printQuery(vector<Parameter> queryParameters);
//	string relationPrinter(set<Tuple> answers, vector<string> queryIDs);
	vector<string> IDPrintVector(vector<Parameter> queryParameters);
	
 

private:
    string relationKey;
    vector<Parameter> relationParameters;
    set<Tuple> relations;
	int relAnswerSize;
};
