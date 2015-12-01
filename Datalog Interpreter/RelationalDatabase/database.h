//
//  database.h
//  RelationalDatabase
//
//  Created by Nathan Crowther on 10/20/15.
//  Copyright © 2015 Nathan Crowther. All rights reserved.
//
#pragma once
//#include "datalogProgram.h"
#include "relation.h"
#include "predicate.h"
#include "tuple.h"
#include "rule.h"


#include <vector>
#include <map>
#include <iostream>

using namespace std;

class database { //map of sets of relations
public:
    map<string,Relation> databaseMap;
    database(){
		timeThrough = 0;
	}
    ~database(){}
    

    Relation queryAnswer(string ID, vector<Parameter> pList);
	
	void join(vector<Rule> ruleVector);
//	void join(Predicate headPredicate, Predicate firstPredicate, vector<Predicate> predicateList);
	

	int getTimeThrough();


    
private:
//############################################### Private Functions #################################

//############################################### JOIN Functions #################################
	Relation relationJoiner(Relation rel1, Relation rel2);
	
	vector<Parameter> parameterJoiner(Relation rel1, Relation rel2);
	
	bool isJoinable(Tuple tup1, Tuple tup2, vector<Parameter> scheme1, vector<Parameter> scheme2);
	
	Tuple joinTuples(Tuple tup1, Tuple tup2, vector<Parameter> scheme1, vector<Parameter> scheme2);
	
	set<Tuple> tupleJoiner(Relation rel1, Relation rel2);

	bool variableCheck(Relation rel1, Relation rel2);
	
	bool changeCheck(int startSize, int endSize);
	
	
//############################################### VECTOR Functions #################################
	vector<Parameter> vectorAdder(vector<Parameter> vector, Parameter headP);
	
	vector<Predicate> vectorPredAdder(vector<Predicate> vector, Predicate firstP);
	
	
	
	
//############################################### QUERY Functions #################################
	vector<string> queryStrings(vector<Parameter> queryList);
	vector<Parameter> queryIDs(Relation relation, vector<Parameter> PList);
	vector<int> queryListStringLocations(vector<Parameter> queryList);
	vector<int> queryListIDLocations(vector<Parameter> queryList);
	vector<string> queryIDs(vector<Parameter> queryList);
	
	
	

	

	
	

	bool Union(Predicate headPredicate, Relation newRelation);
	set<Tuple> tupleAdder(Relation headRelation, Relation ansRel);
	vector<int> unionIDLocations(vector<Parameter> headParameters, vector<Parameter> predParameters);
	vector<string> unionIDs(vector<Parameter> headParameters, vector<Parameter> predParameters);

	void setTimeThrough();
	
	
//	bool checkIfSeen(string v);
	


//############################################### Private Variables #################################
	int timeThrough;
 
	vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> query;
	set<Tuple> seenSet;
    
//    set<string> seenSet;
};
