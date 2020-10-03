#include "ExpressionManager.h"

// Splitting Strings into parseTokens

vector<string> ExpressionManager::parseTokens(string expression) {
    cout << "Inside parseTokens" << endl;
        stringstream ss(expression);
        string token;
        vector<string> tokens;
        while(getline(ss, token, ' '))
        {
        tokens.push_back(token);
        }
        return tokens;
}

bool ExpressionManager::isLeftParen(string token) {
        cout << "Inside isLeftParen" << endl;
        cout << "current token" << token << endl;
	if (token == "[") {
		return true;
	}
	else if (token == "(") {
		return true;
	}
	else if (token == "{") {
        cout << "I found it. It's {" << endl;
		return true;
	}
	else {
		return false;
	}
}
bool ExpressionManager::isRightParen(string token) {
    cout << "Inside isRightParen" << endl;
	if (token == "]") {
		return true;
	}
	else if (token == ")") {
		return true;
	}
	else if (token == "}") {
		return true;
	}
	else {
		return false;
	}
}

string ExpressionManager::convert(string token) {
    cout << "Inside convert" << endl;
    string converted;

    if (token == "[") {
        converted = "]";
		return converted;
	}
	else if (token == "(") {
        converted = ")";
		return converted;
	}
	else if (token == "{") {
        converted = "}";
		return converted;
	}
    return converted;
}

bool ExpressionManager::isBalanced(string expression){
    cout << "Hi!" << endl;
	stack <string> stackA;
	vector <string> parsed = parseTokens(expression);
	//check if parseTokens worked:
	cout << parsed.size();
	bool is_balanced = true;
	int i = 0;

	while ((is_balanced == true) && (i < expression.length()))  {

		if (isLeftParen(parsed[i]) == true) {
			stackA.push(parsed[i]);
            cout << "I'm back inside the is_balanced function" << endl;
            cout << "The top of the stack is " << stackA.top() << endl;
		}
		else if (isRightParen(parsed[i]) == true) {
			//First we check if the stack is empty, if it ISN'T, then compare the top char with the parsed
			//If it's matching type, then pop
			if (!stackA.empty()){
                string nextChar = stackA.top();
				if (convert(nextChar) == parsed[i]) {
					stackA.pop();
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}

        ++i;
	}
	cout << "isBalanced: " << expression << endl;
    if ((!stackA.empty()) && (is_balanced == true)){
        return false;
    }
    else {
        return true;
    }
}

string ExpressionManager::postfixToInfix(string postfixExpression){
	cout << "postfixToInfix: " << postfixExpression << endl;
    vector <string> parsed = parseTokens(postfixExpression);
    stack <string> stackC;
    string finalExpression = "";

    for (int i = 0; i < (parsed.size()); i++) {
        string parsedString = parsed[i];
        int n = parsedString.length();
        string S_IntwOperator;


        char char_array[n+1];
        strcpy(char_array,parsedString.c_str());

        if(isdigit(char_array[0])){
//int convertedInteger = convertToInt(char_array[0]);
        //if char_array[0] {parsed[i]} is integer, then push parsed[i] since that's the string
                stackC.push(parsed[i]);
        }
        else if (isOperator(char_array[0])) {
            string rightSide;
            string leftSide;

            if (!stackC.empty()){
                rightSide = stackC.top();
                    stackC.pop();
            }
            else {
                return "error";
            }
            if (!stackC.empty()){
                leftSide = stackC.top();
                    stackC.pop();
            }
            else {
                return "error";
            }
        //now we need the operator placed in between

            if (char_array[0] == '+'){
                cout << "inside charInt == '+'" << endl;
                S_IntwOperator = "( " + leftSide + " + " + rightSide + " )";
                stackC.push(S_IntwOperator);
            }
            else if (char_array[0] == '-'){
                cout << "inside charInt == '-'" << endl;
                S_IntwOperator = "( " + leftSide + " - " + rightSide + " )";
                stackC.push(S_IntwOperator);
            }
            else if (char_array[0] == '*'){
                cout << "inside charInt == '*'" << endl;
                S_IntwOperator = "( " + leftSide + " * " + rightSide + " )";
                stackC.push(S_IntwOperator);
            }
            else if (char_array[0] == '/'){
                cout << "inside charInt == '/'" << endl;
                S_IntwOperator = "( " + leftSide + " / " + rightSide + " )";
                stackC.push(S_IntwOperator);
            }
            else if (char_array[0] == '%'){
                cout << "inside charInt == '%'" << endl;
                S_IntwOperator = "( " + leftSide + " % " + rightSide + " )";
                stackC.push(S_IntwOperator);
            }
            else {
                return "error";
            }
        }
    }

        if (stackC.size() == 1) {
            finalExpression = stackC.top();
        }
        else {
            return "error";
        }
	return finalExpression;
}

int ExpressionManager::convertToInt(string token) {
	cout << "inside numToConvert function " << endl;
    cout << "I'm trying to convert: " << token << "into an integer" << endl;
    int convertedInt = stoi(token);
    return convertedInt;
}

bool ExpressionManager::isOperator(char token) {
                cout << "inside the isOperator" << endl;
                cout << "the token is " << token << endl;
    if (token == '+') {
        cout << "the token was +" << endl;
        return true;
    }
    else if (token == '-') {
        cout << "the token was -" << endl;
        return true;
    }
    else if (token == '*') {
        cout << "the token was *" << endl;
        return true;
    }
    else if (token == '/') {
        cout << "the token was /" << endl;
        return true;
    }
    else if (token == '%') {
        cout << "the token was %" << endl;
        return true;
    }
    else {
        return false;
    }
}

string ExpressionManager::postfixEvaluate(string postfixExpression){
    cout << "inside postfixEvaluate" << endl;
    stack <int> intStack;
    string numToConvert;
    int hasBeenConverted;
    char charInt = '0';

	vector <string> parsed = parseTokens(postfixExpression);
    cout << "this is the size of the vector: " << parsed.size();
    for (int i = 0; i < (parsed.size()); i++) {

        string parsedString = parsed[i];
        // Convert String to Char Array
        int n = parsedString.length();
        char char_array[n + 1];

        strcpy(char_array,parsedString.c_str());

// for (int i = 0; i < n; i++) {
//     cout << char_array[i];
// }
// Convert String to Char Array

//charInt = convertThistoChar(parsed[i]);
// cout << "CHANGE THIS FUNCTION";
// cout << "parsedVector this time is: " << parsed[i] << endl;
// cout << "our iterator is at: " << i << endl;
// cout << "charInt this time is: " << charInt << endl;
        //Checks the first char of the token to see if its a number
        if (isdigit(char_array[0])) {
// cout << "this was a digit: " << charInt << endl;
// cout << "inside the isdigit" << endl;

            //Convert integer(string) into integer(int)
            numToConvert = parsed[i];
            hasBeenConverted = convertToInt(numToConvert);
            //Convert integer(string) into integer(int)

            intStack.push(hasBeenConverted);
// cout << "just pushed hasBeenConverted" << endl;
// cout << "we just pushed: " << intStack.top() << endl;
        }

        else if (isOperator(char_array[0])){ // if operator
            int answerInt;
            int rightSide;
            int leftSide;

            if (!intStack.empty()){
                rightSide = intStack.top();
                cout << "just got from rightside: " << rightSide;
                intStack.pop();
            }
            else {
                return "This was empty";
            }

            if (!intStack.empty()){
                leftSide = intStack.top();
                cout << "just got from leftside: " << leftSide << endl;
                intStack.pop();
            }
            else {
                return "This was empty";
            }

            if (char_array[0] == '+'){
                cout << "inside charInt == '+'" << endl;
                answerInt = leftSide + rightSide;
                intStack.push(answerInt);
            }
            else if (char_array[0] == '-'){
                answerInt = leftSide - rightSide;
                intStack.push(answerInt);
            }
            else if (char_array[0] == '*'){
                cout << "inside charInt == '*'" << endl;
                answerInt = leftSide * rightSide;
                intStack.push(answerInt);
            }
            else if (char_array[0] == '/'){
                answerInt = leftSide / rightSide;
                intStack.push(answerInt);
            }
            else if (char_array[0] == '%'){
                answerInt = leftSide % rightSide;
                intStack.push(answerInt);
            }
        }
        else {
            cout << "Error" << endl;
        }
    }

	cout << "left the for loop "<< endl;
    if (!intStack.empty()){
        cout << "the stack is this" << intStack.top() << endl;
    }
cout << "test 1 " << endl;
    string finalizedString = "";
    int addThisInt;
    string addThisString;
cout << "test 2 " << endl;
    while (!intStack.empty()) {
        cout << "test 3 " << endl;
        addThisInt = intStack.top();
        addThisString = to_string(addThisInt);
        intStack.pop();
        finalizedString = finalizedString + addThisString;
    }
cout << "test 4 " << endl;
	cout << "postfixEvaluate: " << postfixExpression << endl;
	cout << "this is the finalizedString" << finalizedString;
	return finalizedString;
}

string ExpressionManager::infixToPostfix(string infixExpression){
	cout << "infixToPostfix: " << infixExpression << endl;
	return "REPLACE";
}
