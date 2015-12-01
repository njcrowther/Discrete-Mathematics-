#include "LexAnalyzer.h"


		
vector<Tokens> LexAnalyzer::tokenize(){
/* 	
	1. creates outputVector
	2.	while the file isn't at the end
		i. run characters through smaller machines
		ii. increase line count
	3.	After the file is done being read, call decompose
		
		Each smaller machine checks what type of character it is, then calls a function to read until it reaches either
		what should be the end, or eof. Because we made the ifstream a global variable, each smaller function should be able
		to look at the next character and move the cursor. 
*/
	char c;

	//State return variables
	string commaReturn = "";
	string IDReturn = "";
	string commentReturn = "";
	string periodReturn = "";
	string questionReturn = "";
	string parenthesisReturn = "";
	string colonReturn = "";
	string operandReturn = "";
	string stringReturn = "";
	bool whiteSpaceReturn;

	while(FileStream->get(c)){
		
		updateLineNumber(c);

		IDReturn = IDMachine(c);
		commentReturn = commentMachine(c);
		commaReturn = commaMachine(c);
		periodReturn = periodMachine(c);
		questionReturn = questionMachine(c);
		parenthesisReturn = parenthesisMachine(c);
		colonReturn = colonMachine(c);
		operandReturn = operandMachine(c);
		stringReturn = stringMachine(c);
		whiteSpaceReturn = isWhiteSpace(c);

		string totalString = IDReturn + commentReturn + commaReturn + periodReturn + questionReturn + parenthesisReturn + colonReturn + operandReturn + stringReturn;

		if(totalString == "" && !whiteSpaceReturn){
			//create undefined token
			stringstream ss;
			ss << c;
			newTokenGenerator("UNDEFINED", ss.str(), lineNumber);
		}
	}

	newTokenGenerator("EOF","",lineNumber);
	return outputVector;
}




/*################################################################## STATE MACHINES #################################################################*/
string LexAnalyzer::IDMachine(char testCharacter){
	stringstream cs;
	char c;

	if(isLetter(testCharacter)){
		string IDTest = "";
		cs << testCharacter;

		//cout << "ID? " << cs.str() << endl;

		while(isalnum(FileStream->peek())){ //not symbols either
			//cout << "while? " << cs.str() << endl;
			FileStream->get(c);
			cs << c;
			
		}


		IDTest = cs.str();
		
		
		if(isKeyword(IDTest)){
			string keywordType = kWType(IDTest);
			newTokenGenerator(keywordType, IDTest, lineNumber);
			
			return IDTest;
		}
		else {
			newTokenGenerator("ID", IDTest, lineNumber);
			return IDTest;
		}
	}
	return "";
}

string LexAnalyzer::commentMachine(char testCharacter){
	stringstream cs;
	char c;
	int startLine = 0;
	string singleCommentString = "";
	string multiCommentString = "";	
	bool multiCommentBool = false;
	string returnString = "";
	startLine = lineNumber;

	if(testCharacter == '#'){
		// cs << testCharacter; //Grab #

		if(multiCommentBoolCheck()){
			cs << multiCommentMachine(testCharacter, startLine);	
		}
		else{
			cs << singleCommentMachine(testCharacter);	
		}
		
		returnString = cs.str();
	}
	return returnString; 	
}

string LexAnalyzer::multiCommentMachine(char testCharacter, int startLine){
	char c;
	bool endCommentCheck = false;
	stringstream cs;
	string multiCommentString = "";
		
	cs << testCharacter;

	while(!endCommentCheck && FileStream->get(c)){				
		updateLineNumber(c);

		if(c == '|'){
			if(FileStream->peek() == '#'){
				cs << c;
				FileStream->get(c);
				cs << c;
				endCommentCheck = true;
			}
			else {
				cs << c; //i.e. |# stuff | stuff |#
			}
		}
		else {
			cs << c; //Grab stuff inside comment
		}
	}
	
	if(FileStream->eof() && !endCommentCheck){
		newTokenGenerator("UNDEFINED", cs.str(), startLine);
	
		return cs.str();
	}
	else{
		multiCommentString = cs.str();
		//newTokenGenerator("COMMENT", multiCommentString, startLine);
		
		return multiCommentString;	
	}			
}

string LexAnalyzer::singleCommentMachine(char testCharacter){													
	char c;
	stringstream cs;
	string singleCommentString = "";

	cs << testCharacter;

	while(FileStream->peek() != '\n' && FileStream->get(c)){
		cs << c;
	}
	
	singleCommentString = cs.str();
	//newTokenGenerator("COMMENT",singleCommentString,lineNumber);
	
	return singleCommentString;
}

string LexAnalyzer::commaMachine(char testCharacter){
	if(testCharacter == ','){
		stringstream ss;
		ss << testCharacter;
		newTokenGenerator("COMMA", ",",lineNumber);
		
		return ss.str();
	}
	return "";
}

string LexAnalyzer::periodMachine(char testCharacter){
	if(testCharacter == '.'){
		stringstream ss;
		ss << testCharacter;
		newTokenGenerator("PERIOD", ".",lineNumber);
		
		return ss.str();
	}
	return "";
}

string LexAnalyzer::questionMachine(char testCharacter){
	if(testCharacter == '?'){
		stringstream ss;
		ss << testCharacter;
		newTokenGenerator("Q_MARK", "?",lineNumber);
		
		return ss.str();
	}
	return "";
}

string LexAnalyzer::parenthesisMachine(char testCharacter){
	if(testCharacter == '('){
		stringstream ss;
		ss << testCharacter;
		newTokenGenerator("LEFT_PAREN", "(", lineNumber);

		return ss.str();
	}
	else if(testCharacter == ')'){
		stringstream ss;
		ss << testCharacter;
		newTokenGenerator("RIGHT_PAREN", ")", lineNumber);
		
		return ss.str();
	}
	return "";
}

string LexAnalyzer::colonMachine(char testCharacter){
	stringstream cs;
	char c;
	if(testCharacter == ':'){
		cs << testCharacter;
		if(FileStream->peek() == '-'){
			FileStream->get(c);
			cs << c;
			newTokenGenerator("COLON_DASH", ":-", lineNumber);
			
			return cs.str();
		}
		else {
			newTokenGenerator("COLON", ":", lineNumber);
			
			return cs.str();
		}
	}
	return "";
}

string LexAnalyzer::operandMachine(char testCharacter){
	stringstream cs;
	char c;
	if(testCharacter == '*'){
		cs << c;
		newTokenGenerator("MULTIPLY", "*", lineNumber);
		
		return cs.str();
	}
	else if(testCharacter == '+'){
		cs << testCharacter;
		newTokenGenerator("ADD", "+", lineNumber);
		
		return cs.str();
	}
	return "";
}

string LexAnalyzer::stringMachine(char testCharacter){
	stringstream cs;
	char c;
	bool endCheck;
	bool doubleApostropheCheckVar;

	if(testCharacter == '\''){
		int startLine = lineNumber;
		cs << testCharacter; //grab beginning '
		
		while(FileStream->get(c) && !endStringCheck(c)){
			doubleApostropheCheckVar = doubleApostropheCheck(c);
			if(doubleApostropheCheckVar){ //grab ''
				cs << c;
				FileStream->get(c);
				cs << c;
				doubleApostropheCheckVar = false;
			}
			else{
				cs << c;	
				endCheck = endStringCheck(c);
				updateLineNumber(c);			
			}			
		}
		

		if(FileStream->eof() && !endCheck){
			newTokenGenerator("UNDEFINED", cs.str(), startLine);
			
			return cs.str();
		}
		else {
			cs << c; //Grab ending '
			newTokenGenerator("STRING", cs.str(), startLine);
			
			return cs.str();	
		}	
	}
	return "";
}







//Helper Functions
bool LexAnalyzer::isKeyword(string testString){
	if(testString == "Schemes" || testString == "Facts" || testString == "Rules" || testString == "Queries"){
		return true;
	}
	else return false;
}

bool LexAnalyzer::updateLineNumber(char testCharacter){
	if(testCharacter == '\n'){
		lineNumber++;
		return true;
	}
	else {
		return false;
	}
}

string LexAnalyzer::kWType(string testKeyword){
	if(testKeyword == "Schemes"){
		return "SCHEMES";
	}
	else if(testKeyword == "Facts"){
		return "FACTS";
	}
	else if(testKeyword == "Rules"){
		return "RULES";
	}
	else if(testKeyword == "Queries"){
		return "QUERIES";
	}
	else return "Not Keyword";
}

void LexAnalyzer::newTokenGenerator(string tokenType, string tokenValue, int lineNumber){
	Tokens newToken(tokenType, tokenValue, lineNumber);
	outputVector.push_back(newToken);
}

bool LexAnalyzer::endStringCheck(char testCharacter){
	if(testCharacter == '\'' && FileStream->peek() != '\''){
		return true;
	}
	else return false;
}

bool LexAnalyzer::doubleApostropheCheck(char testCharacter){
	
	if(testCharacter == '\'' && FileStream->peek() == '\''){ // return''s
		return true;
	}
	// else if(testCharacter == '\''){
	// 	return false;
	// }
	else return false;
}

bool LexAnalyzer::multiCommentBoolCheck(){
	if(FileStream->peek() == '|'){
		return true;
	}
	else return false;
}

//Basic Character Types
bool LexAnalyzer::isLetter(char testCharacter){
	if(isalpha(testCharacter)){
		return true;
	}
	else return false;
}

bool LexAnalyzer::isWhiteSpace(char testCharacter){
	if(isspace(testCharacter)){
		return true;
	}
	else return false;
}

bool LexAnalyzer::isNumber(char testCharacter){
	if(isdigit(testCharacter)){
		return true;
	}
	else return false;
}

/*################################ To String ###############################################
*/

string LexAnalyzer::toString(vector<Tokens> toStringVector){
	string outString = "";
	string addStringType = "";
	string addStringValue = "";
	string addStringLine = "";
	int tokenCount = 0;

	while(!toStringVector.empty()){
		tokenCount++;

		addStringType = toStringVector.begin()->getType();
		addStringValue = toStringVector.begin()->getValue();
		addStringLine = toStringVector.begin()->getLine();

		outString += "(" + addStringType + "," +  "\"" + addStringValue + "\"" + "," + addStringLine + ")" + "\n";
		//cout << endl;

		toStringVector.erase(toStringVector.begin());

	}

	stringstream ss;
	ss << tokenCount;



	outString += "Total Tokens = " + ss.str();

	return outString;
}