//
//  relation.h
//  RelationalDatabase
//
//  Created by Nathan Crowther on 10/20/15.
//  Copyright © 2015 Nathan Crowther. All rights reserved.
//
#pragma once
#include "tuple.h"
#include <string>
#include <vector>
#include <set>


using namespace std;

class Relation {
    //Scheme describes a relation. Facts describe the contents of a relation
public:
    Relation(string key, vector<string> parameters){
        relationKey = key;
        relationParameters = parameters;
    }
    ~Relation(){}
    
    void addRelation(Tuple relation);
    
    set<Tuple> getRelations();

private:
    string relationKey;
    vector<string> relationParameters;
    set<Tuple> relations;
};
