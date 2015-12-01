#include "datalogProgram.h"



bool datalogProgram::parser() {
	bool falseChecker = true;

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
	parseIDList();
	match("RIGHT_PAREN");

	//Create Predicate and empty the captureVector
	Predicate newPredicate = Predicate(possibleID, possibleParameter, captureVector);
	schemeVector.push_back(newPredicate);
	captureVector.erase(captureVector.begin(),captureVector.end());
}

void datalogProgram::parseSchemeList() { //scheme schemeList | lambda
	if(analyzedVector[vC].getType() != "ID") {
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
		captureVector.push_back(possibleID);
		parseIDList();		
	}
}

void datalogProgram::parseFact() {	//fact    	-> 	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
	string possibleID = match("ID");
	match("LEFT_PAREN");
	string possibleParameter = match("STRING");
	parseStringList();
	match("RIGHT_PAREN");
	match("PERIOD");

	//Add to Fact Set, then sort
	factStringsSet.insert(possibleParameter);
	for(int i=0; i < captureVector.size(); i++) {
		factStringsSet.insert(captureVector[i]);
	}

	//Create Predicate and empty the captureVector
	Predicate newPredicate = Predicate(possibleID, possibleParameter, captureVector);
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
	// 

	bool firstPred = true;
	Predicate possibleHP = parseHeadPredicate();
	match("COLON_DASH");
	Predicate possibleP = parsePredicate(firstPred);
	parsePredicateList();
	match("PERIOD");

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
	parseIDList();
	match("RIGHT_PAREN");

	//Create Predicate and empty the captureVector
	Predicate newHeadPredicate = Predicate(possibleID1, possibleID2, captureVector);
	//ruleCaptureVector.push_back(newHeadPredicate);
	captureVector.erase(captureVector.begin(),captureVector.end());
	
	return newHeadPredicate;
}

Predicate datalogProgram::parsePredicate(bool firstPred) {	//predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
	// cout << "Parse Predicate: " << endl;
	string possibleID1 = match("ID");
	// cout << "PossibleID1: " << possibleID1 << endl;
	match("LEFT_PAREN");
	string possibleP = parseParameter(); //A
	// cout << "PossibleP is : " << possibleP << endl;
	parseParameterList();	//cV = ()
	match("RIGHT_PAREN");

	//Create Predicate and empty the captureVector
	// cout << "captureVector: (" << endl;
	// for(int i=0; i < captureVector.size(); i++) {
	// 	cout << captureVector[i] << ",";
	// }
	// cout << ")" << endl;

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

string datalogProgram::parseParameter() {	//parameter	->	STRING | ID | expression
	// cout << "Parse Parameter: " << endl;
	string returnValue = "";

	if(analyzedVector[vC].getType() == "LEFT_PAREN") {
		returnValue = parseExpression();
		captureVector.push_back(returnValue);
		return returnValue;
	}
	else if(analyzedVector[vC].getType() == "STRING"){
		returnValue = match("STRING");
		captureVector.push_back(returnValue);
		return returnValue;
	}	
	else if(analyzedVector[vC].getType() == "ID") {
		returnValue = match("ID");
		// cout << "ID: " << returnValue << endl;
		captureVector.push_back(returnValue);

		// cout << "captureVector: (" << endl;
		// for(int i=0; i < captureVector.size(); i++) {
		// 	cout << captureVector[i] << ",";
		// }
		// cout << ")" << endl;

		return returnValue;
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

string datalogProgram::parseExpression() {	//expression	-> 	LEFT_PAREN parameter operator parameter RIGHT_PAREN
	match("LEFT_PAREN");
	string p1 = parseParameter();
	string op = parseOperator();
	string p2 = parseParameter();
	match("RIGHT_PAREN");

	return "(" + p1 + op + p2 + ")";
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
	Predicate possibleP = parsePredicate(true);
	match("Q_MARK");

	queryVector.push_back(possibleP);
}

void datalogProgram::parseQueryList() {	//queryList	->	query queryList | lambda
	if(analyzedVector[vC].getType() != "ID") {
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
		captureVector.push_back(possibleString);
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

vector<string> datalogProgram::vectorShaver(vector<string> inputVector) {
	vector<string> returnVector;
	

	for(int i=1; i < inputVector.size(); i++) {
		returnVector.push_back(inputVector[i]);
	
	}

	return returnVector;
}

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
	set<string>::iterator it = factStringsSet.begin();
	cout << "Domain(" << factStringsSet.size() << "):" << endl;
	for(it = factStringsSet.begin(); it != factStringsSet.end(); it++) {
		cout << "  " << *it << endl;
	}
}




