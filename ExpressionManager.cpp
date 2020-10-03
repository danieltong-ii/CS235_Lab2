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
	return "REPLACE";
}

int ExpressionManager::convertToInt(string token) {
	cout << "inside numToConvert function " << endl;
    cout << "I'm trying to convert: " << token << "into an integer" << endl;
    int convertedInt = stoi(token);
    return convertedInt;
}

char ExpressionManager::convertThistoChar(string token) {

}

bool ExpressionManager::isOperator(char token) {
                cout << "inside the isOperator" << endl;
                cout << "the token is " << token << endl;
    if (token == '+') {
        cout << "the token was +" << endl;
        return true;
    }
    else if (token == '-') {
        return true;
    }
    else if (token == '*') {
        return true;
    }
    else if (token == '/') {
        return true;
    }
    else if (token == '%') {
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
        //convert string to Cstring
        charInt = convertThistoChar(parsed[i]);
        cout << "CHANGE THIS FUNCTION"
        cout << "parsedVector this time is: " << parsed[i] << endl;
        cout << "our iterator is at: " << i << endl;
        cout << "charInt this time is: " << charInt << endl;

        if (isdigit(charInt[i])) {
            cout << "this was a digit: " << charInt << endl;
            cout << "inside the isdigit" << endl;
            numToConvert = parsed[i]; //this is a string that we need to convert into an integer
            hasBeenConverted = convertToInt(numToConvert);
            intStack.push(hasBeenConverted);
            cout << "just pushed hasBeenConverted" << endl;
            cout << "we just pushed: " << intStack.top() << endl;
        }
        else if (isOperator(charInt)){ // if operator
            cout << "back to isOperator in postfixEvaluate" << endl;
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



            if (charInt == '+'){
                cout << "inside charInt == '+'" << endl;
                answerInt = leftSide + rightSide;
                intStack.push(answerInt);
            }
            else if (charInt == '-'){
                answerInt = leftSide - rightSide;
                intStack.push(answerInt);
            }
            else if (charInt == '*'){
                answerInt = leftSide * rightSide;
                intStack.push(answerInt);
            }
            else if (charInt == '/'){
                answerInt = leftSide / rightSide;
                intStack.push(answerInt);
            }
            else if (charInt == '%'){
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
