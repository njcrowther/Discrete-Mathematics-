//
//  database.h
//  RelationalDatabase
//
//  Created by Nathan Crowther on 10/20/15.
//  Copyright © 2015 Nathan Crowther. All rights reserved.
//
#pragma once
#include "datalogProgram.h"
#include "relation.h"
#include "predicate.h"
#include "tuple.h"

#include <vector>
#include <map>

using namespace std;

class database { //map of sets of relations
public:
    database(datalogProgram inDL){
        schemes = inDL.getSchemeVector();
        facts = inDL.getFactVector();
        query = inDL.getQueryVector();
    }
    ~database(){}
    
    void databaser();
    
    void databaseCreator();
    void queryAnswer();

    void newRelation(string SchemeID, Relation newRelation);
    


    
private:
//############################################### Private Functions #################################
    void selection(string key, vector<string> parameters);
    void projection();
    vector<string> vectorAdder(vector<string> vector, string headP);
//############################################### Private Variables #################################
    vector<Predicate> schemes;
    vector<Predicate> facts;
    vector<Predicate> query;
    map<string,Relation> databaseMap;
};
