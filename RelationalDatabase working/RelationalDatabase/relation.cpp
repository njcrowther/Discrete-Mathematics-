//
//  relation.cpp
//  RelationalDatabase
//
//  Created by Nathan Crowther on 10/23/15.
//  Copyright © 2015 Nathan Crowther. All rights reserved.
//

#include "relation.h"

using namespace std;

void Relation::addRelation(Tuple relation) {
    relations.insert(relation);
}

set<Tuple> Relation::getRelations() {
    return relations;
}