//
//  database.cpp
//  RelationalDatabase
//
//  Created by Nathan Crowther on 10/22/15.
//  Copyright © 2015 Nathan Crowther. All rights reserved.
//

#include "database.h"
#include "predicate.h"



using namespace std;

void database::databaser() {
    databaseCreator();
    queryAnswer();
}


void database::databaseCreator() {
/*
 1. While the set of Schemes isn't empty, create new database.
 */
    
    for (int i=0; i < schemes.size(); i++) {
        string ID = schemes[i].getPredicateID();
        string headParameter = schemes[i].getParameter();
        vector<string> parameterList = schemes[i].getParameterList();
        
        parameterList = vectorAdder(parameterList, headParameter); //Insert headParameter into ParameterList

        Relation newRelation(ID, parameterList);
        
        databaseMap[ID] = newRelation;
    }
    
    for (int i=0; i < facts.size(); i++) {
        string ID = facts[i].getPredicateID();
        string headParameter = facts[i].getParameter();
        vector<string> parameterList = facts[i].getParameterList();
        
        parameterList = vectorAdder(parameterList, headParameter); //Insert headParameter into ParameterList
        
        Tuple newTuple(parameterList);
        
        databaseMap[ID].addRelation(newTuple);
    }

    
}

void database::queryAnswer() {
    for (int i=0; i<query.size(); i++) {
        string ID = query[i].getPredicateID();
        string headParameter = query[i].getParameter();
        vector<string> parameterList = query[i].getParameterList();
        
        parameterList = vectorAdder(parameterList, headParameter);
        
        selection(ID, parameterList);
        projection();
    }
    string parameterT = query[0].getParameterList().;
}

//############################################### HELPER FUNCTIONS #################################
vector<string> database::vectorAdder(vector<string> oldVector, string headP) {
    oldVector.insert(oldVector.begin(), headP);
    return oldVector;
}

void database::selection(string key, vector<string> parameters) {
    int size = databaseMap[key].getRelations().size();

    for (int i=0; i < size; i++) { //selection
        
    }
}

void database::projection() {
    
}

