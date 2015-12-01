//
//  tuple.h
//  RelationalDatabase
//
//  Created by Nathan Crowther on 10/20/15.
//  Copyright © 2015 Nathan Crowther. All rights reserved.
//
#pragma once
#include <vector>
#include "parameter.h"

using namespace std;

class Tuple : public vector<string> {
public:
    Tuple(){}
    Tuple(vector<Parameter> parameters) {
        for(int i=0; i< parameters.size(); i++) {
            push_back(parameters[i].getParameterValue());
        }
//		size = parameters.size();
		originalParameters = parameters;
    }
	
//	string tuplePrint() {
//		for (int i=0; i < size; i++) {
//			Parameter tupleValue = originalParameters[i];
//			
//		}
//		
//		return "bob";
//	}
	
private:
//	int size;
	vector<Parameter> originalParameters;
};

