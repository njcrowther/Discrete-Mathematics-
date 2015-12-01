//
//  tuple.h
//  RelationalDatabase
//
//  Created by Nathan Crowther on 10/20/15.
//  Copyright © 2015 Nathan Crowther. All rights reserved.
//
#pragma once

using namespace std;

class Tuple: public vector<string> {
public:
    Tuple(vector<string> parameters) {
        p = parameters;
    }

private:
    vector<string> p;
};

