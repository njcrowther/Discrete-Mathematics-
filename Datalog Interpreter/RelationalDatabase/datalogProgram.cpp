#include "datalogProgram.h"

/*
 10/22 - I made a lot of changes regarding Parameters and expressions. If things are terribly wrong it's probably due to that.
 */


bool datalogProgram::parser() {
//	bool falseChecker = true;

	try {
		match("SCHEMES");
		match("COLON");
		parseScheme();
		parseSchemeList();

		match("FACTS");
		match("COLON");
		// parseFact();
		parseFactList();

		match("RULES");
		match("COLON");
		// parseRule();
		parseRuleList();
		
		//run rules from set here
		myDatabase.join(ruleVector);
		
		if (myDatabase.getTimeThrough() > 1) {
			cout << "Schemes populated after " << myDatabase.getTimeThrough() << " passes through the Rules." << endl;
		}
		else {
			cout << "Schemes populated after " << myDatabase.getTimeThrough() << " pass through the Rules." << endl;
		}
		
		match("QUERIES");
		match("COLON");
		parseQuery();
		parseQueryList();
	}
	catch(Tokens token) {
		cout << "Failure!" << endl << "  (" << token.getType() << ",\"" << token.getValue() << "\"," << token.getLine() << ")" << endl;
		return false;
	}

	

	return true;
}


/*########################################################################GRAMMAR FUNCTIONS############################################################*/
void datalogProgram::parseScheme() {

	//Get Return Objects and Parse Scheme
	string possibleID = match("ID");
	match("LEFT_PAREN");
	string possibleParameter = match("ID");
    Parameter firstParameter("ID", possibleParameter);
	parseIDList();
	match("RIGHT_PAREN");
    
//    cout << "Scheme: " << possibleID << " ," << possibleParameter << endl;
    
    //Combine firstParameter into the parameterList
    captureVector = vectorAdder(captureVector, firstParameter);

	//Create Predicate and empty the captureVector
	Predicate newPredicate = Predicate(possibleID, firstParameter, captureVector);
    
    //Create New Relation
    Relation newRelation(possibleID, captureVector);
    myDatabase.databaseMap[possibleID] = newRelation;
//    newRelation.printRelations();

    
    //	schemeVector.push_back(newPredicate);
	captureVector.erase(captureVector.begin(),captureVector.end());
    
}

void datalogProgram::parseSchemeList() { //scheme schemeList | lambda
	if(analyzedVector[vC].getType() != "ID") {
//        cout << endl << endl;
        return;
	}
	else {
		parseScheme();
		parseSchemeList();
	}
    
}

void datalogProgram::parseIDList() {	//idList  	->	COMMA ID idList | lambda
	if(analyzedVector[vC].getType() != "COMMA") {
		return;
	}
	else {
		match("COMMA");
		string possibleID = match("ID");
        Parameter pID("ID", possibleID);
		captureVector.push_back(pID);
		parseIDList();		
	}
}

void datalogProgram::parseFact() {	//fact    	-> 	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
	string possibleID = match("ID");
	match("LEFT_PAREN");
	string possibleParameter = match("STRING");
    Parameter firstParameter("STRING", possibleParameter);
	parseStringList();
	match("RIGHT_PAREN");
	match("PERIOD");

    //Add firstParameter to parameterList
    captureVector = vectorAdder(captureVector, firstParameter);
    
    //Add to Relation
    Tuple newTuple(captureVector);
    myDatabase.databaseMap[possibleID].addRelation(newTuple);
    
	//Create Predicate and empty the captureVector
	Predicate newPredicate = Predicate(possibleID, firstParameter, captureVector);
	factVector.push_back(newPredicate);
	captureVector.erase(captureVector.begin(),captureVector.end());
}

void datalogProgram::parseFactList() { 	//factList	->	fact factList | lambda
	if(analyzedVector[vC].getType() == "RULES") {

        return;
	}
	else if(analyzedVector[vC].getType() != "ID") {
		return;
	}
	else {
		parseFact();
		parseFactList();
	}
}

void datalogProgram::parseRule() {
	bool firstPred = true;
	Predicate possibleHP = parseHeadPredicate();
	match("COLON_DASH");
	Predicate possibleP = parsePredicate(firstPred);
	parsePredicateList();
	vector<Predicate> predicateList = ruleCaptureVector;
	match("PERIOD");
	
	/*Analyze rule
		1. combine possibleP with predicateList
		2. Perform joins while the predicate vector isn't empty
		3. Union with Head Predicate.
	*/
	
	//1.
//	predicateList = predVectorAdder(predicateList, possibleP);
	
	//2.
//	myDatabase.join(possibleHP, possibleP, predicateList);
	
	//3.
	//Create Rule and empty the ruleCaptureVector
	Rule newRule = Rule(possibleHP, possibleP, ruleCaptureVector);
	ruleVector.push_back(newRule);
	ruleCaptureVector.erase(ruleCaptureVector.begin(),ruleCaptureVector.end());
}

void datalogProgram::parseRuleList() {	//ruleList	->	rule ruleList | lambda	
	if(analyzedVector[vC].getType() == "QUERIES") {
		return;
	}
	else if(analyzedVector[vC].getType() != "ID") {
		return;
	}
	else {
		parseRule();
		parseRuleList();
	}	
}

Predicate datalogProgram::parseHeadPredicate() {	//headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
	string possibleID1 = match("ID");
	match("LEFT_PAREN");
	string possibleID2 = match("ID");
    Parameter firstParameter("ID", possibleID2); //create new parameter
	parseIDList();
	match("RIGHT_PAREN");

	//Create Predicate and empty the captureVector
	Predicate newHeadPredicate = Predicate(possibleID1, firstParameter, captureVector);

	captureVector.erase(captureVector.begin(),captureVector.end());
	
	return newHeadPredicate;
}

Predicate datalogProgram::parsePredicate(bool firstPred) {	//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	// cout << "Parse Predicate: " << endl;
	string possibleID1 = match("ID");
	// cout << "PossibleID1: " << possibleID1 << endl;
	match("LEFT_PAREN");
	Parameter possibleP = parseParameter(); //A
	// cout << "PossibleP is : " << possibleP << endl;
	parseParameterList();	//cV = ()
	match("RIGHT_PAREN");


	captureVector = vectorShaver(captureVector);


	Predicate newPredicate = Predicate(possibleID1, possibleP, captureVector);
	if(!firstPred) {
		ruleCaptureVector.push_back(newPredicate);
	}
	captureVector.erase(captureVector.begin(),captureVector.end());

	return newPredicate;
}

void datalogProgram::parsePredicateList() {	//predicateList	->	COMMA predicate predicateList | lambda
	// cout << "Parse Predicate List: " << endl;
	if(analyzedVector[vC].getType() != "COMMA") {
		return;
	}
	else {
		match("COMMA");
		parsePredicate(false);
		parsePredicateList();
	}		
}

Parameter datalogProgram::parseParameter() {	//parameter	->	STRING | ID | expression
	// cout << "Parse Parameter: " << endl;
	string returnValue = "";

//	if(analyzedVector[vC].getType() == "LEFT_PAREN") {
//		Parameter returnExpression = parseExpression();
//        
//        string rE = "(" + returnExpression.getP1() + returnExpression.getOp() + returnExpression.getP2() + ")";
//        
//        Parameter newParameter("EXPRESSION", returnExpression); //create new parameter
//		captureVector.push_back(newParameter);
//		return newParameter;
//	}
	if(analyzedVector[vC].getType() == "STRING"){
		returnValue = match("STRING");
       
        Parameter newParameter("STRING", returnValue); //create new parameter
        
		captureVector.push_back(newParameter);
		return newParameter;
	}	
	else if(analyzedVector[vC].getType() == "ID") {
		returnValue = match("ID");
		// cout << "ID: " << returnValue << endl;
        
        Parameter newParameter("ID", returnValue); //create new parameter
		captureVector.push_back(newParameter);


		return newParameter;
	}
	else {
		throw analyzedVector[vC];
	}
}

void datalogProgram::parseParameterList() { //parameterList	-> 	COMMA parameter parameterList | lambda
	if(analyzedVector[vC].getType() != "COMMA") {
		return;
	}
	else {
		match("COMMA");
		parseParameter();
		parseParameterList();
	}	
}

string datalogProgram::parseOperator() {	//operator	->	ADD | MULTIPLY
	string returnValue = "";
	if(analyzedVector[vC].getType() == "ADD"){
		returnValue = match("ADD");
		return returnValue;
	}
	else if(analyzedVector[vC].getType() == "MULTIPLY") {
		returnValue = match("MULTIPLY");
		return returnValue;
	}
	else {
		throw analyzedVector[vC];
	}	
}

void datalogProgram::parseQuery() {	//query	        ->      predicate Q_MARK
//    cout << "PARSE NEW QUERY" << endl;
    Predicate possibleP = parsePredicate(true);
	match("Q_MARK");

	queryVector.push_back(possibleP);
    
    //Reformat Predicate
    string ID = possibleP.getPredicateID();
    Parameter p1 = possibleP.getParameter();
    vector<Parameter> pList = possibleP.getParameterList();
    
    vector<Parameter> newPList = vectorAdder(pList, p1);
    
//cout << "QueryTest" << endl;
    //Answer the Query
//    Relation ansRel; //Create New Relation for the answer

//cout << "QueryTest1" << endl;
    Relation answerRel = myDatabase.queryAnswer(ID,newPList);
	vector<string> printIDs = answerRel.IDPrintVector(newPList);
	
	answerRel.printRelation(newPList, printIDs);
	
}

void datalogProgram::parseQueryList() {	//queryList	->	query queryList | lambda
	if(analyzedVector[vC].getType() != "ID") {
//        cout << endl << endl;
        return;
	}
	else {
		parseQuery();
		parseQueryList();
	}	
}

void datalogProgram::parseStringList() { //stringList	->	COMMA STRING stringList | lambda 
	if(analyzedVector[vC].getType() != "COMMA") {
		return;
	}
	else {
		match("COMMA");
		string possibleString = match("STRING");
        Parameter newP("STRING", possibleString);
		captureVector.push_back(newP);
		parseStringList();
	}
}

/*########################################################################HELPER FUNCTIONS############################################################*/
string datalogProgram::match(string matchItem) {
	if(analyzedVector[vC].getType() == matchItem) {
		// cout << "MatchItem is: " << matchItem << "!			At vC: " << analyzedVector[vC].getValue() << endl;
		string returnString = analyzedVector[vC].getValue();
		vC++;

		return returnString;
	}
	else {
		throw analyzedVector[vC];
	}
}

vector<Parameter> datalogProgram::vectorShaver(vector<Parameter> inputVector) {
	vector<Parameter> returnVector;
	

	for(int i=1; i < inputVector.size(); i++) {
		returnVector.push_back(inputVector[i]);
	
	}

	return returnVector;
}

vector<Parameter> datalogProgram::vectorAdder(vector<Parameter> oldVector, Parameter headP) {
    oldVector.insert(oldVector.begin(), headP);
    return oldVector;
}

vector<Predicate> datalogProgram::predVectorAdder(vector<Predicate> oldVector, Predicate headP) {
	oldVector.insert(oldVector.begin(), headP);
	return oldVector;
}


//########################################## PRINT SCHEMES, FACTS, AND RULES #####################
void datalogProgram::printSchemes() {
	cout << "Schemes(" << schemeVector.size() << "):" << endl;
	for(int i=0; i < schemeVector.size(); i++) {
		cout << "  " << schemeVector[i].schemeToString();
	}
}

void datalogProgram::printFacts() {
	cout << "Facts(" << factVector.size() << "):" << endl;
	for(int i=0; i < factVector.size(); i++) {
		cout << "  " << factVector[i].factToString();
	}
}

void datalogProgram::printRules() {
	cout << "Rules(" << ruleVector.size() << "):" << endl;
	for(int i=0; i < ruleVector.size(); i++) {
		cout << "  " << ruleVector[i].ruleToString() << endl;
	}
}
	
void datalogProgram::printQueries() {
	cout << "Queries(" << queryVector.size() << "):";
	for(int i=0; i < queryVector.size(); i++) {
		cout << queryVector[i].queryToString();
	}
	cout << endl;
}

void datalogProgram::printDomain() {
	set<Parameter>::iterator it = factStringsSet.begin();
	cout << "Domain(" << factStringsSet.size() << "):" << endl;
	for(it = factStringsSet.begin(); it != factStringsSet.end(); it++) {
        Parameter value = *it;
        string sV = value.getParameterValue();

        cout << "  " << sV << endl;
	}
}

//########################################## GET SCHEMES, FACTS, AND RULES #####################
vector<Predicate> datalogProgram::getSchemeVector() {
    return schemeVector;
}

vector<Predicate> datalogProgram::getFactVector() {
    return factVector;
}

vector<Rule> datalogProgram::getRuleVector() {
    return ruleVector;
}

vector<Predicate> datalogProgram::getQueryVector() {
    return queryVector;
}




