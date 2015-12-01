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

#include <vector>
#include <map>
#include <iostream>

using namespace std;

class database { //map of sets of relations
public:
    map<string,Relation> databaseMap;
    database(){}
    ~database(){}
    

    set<Tuple> queryAnswer(string ID, vector<Parameter> pList);

//    void newRelation(string SchemeID, Relation newRelation);
    
    
    
//    map<string, Relation> getDBMap() {
//        return databaseMap;
//    }

    
private:
//############################################### Private Functions #################################
    vector<Parameter> vectorAdder(vector<Parameter> vector, Parameter headP);
    bool checkIfSeen(string v);
    vector<string> queryStrings(vector<Parameter> queryList);
    vector<Parameter> queryIDs(Relation relation, vector<Parameter> PList);
    vector<int> queryListStringLocations(vector<Parameter> queryList);
    vector<int> queryListIDLocations(vector<Parameter> queryList);
	vector<string> queryIDs(vector<Parameter> queryList);

//############################################### Private Variables #################################
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> query;
	set<Tuple> seenSet;
    
//    set<string> seenSet;
};
