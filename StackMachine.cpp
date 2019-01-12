#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stack>
#include <vector>
#include <sstream>			// string conversions
#include <string>     		// std::string
#include <map>
#include <math.h>       	// floor
using namespace std;

// the stack
stack<string> s;

// data
map<string, string> data;

// instructions
vector<string> instructions;

// tokens
vector<vector<string> > tokens;

// conversions
double stringToNum(string str) {
	istringstream istr(str);
	double num;
	istr >> num;
	return num;
}

string numToString(double num) {
	ostringstream ostr;
	ostr << num;
	string str = ostr.str();
	return str;
}

// pops two elements from the stack, operates them, pushes the result
void add() {
	double y = stringToNum(s.top());
	s.pop();
	double x = stringToNum(s.top());
	s.pop();
	//cout << "x-y pair : " << x << " " << y << endl;
	s.push(numToString(x + y));
	//cout << "x+y = : " << numToString(x + y) << endl;
}

void substract() {
	double y = stringToNum(s.top());
	s.pop();
	double x = stringToNum(s.top());
	s.pop();
	//cout << "x-y pair : " << x << " " << y << endl;
	s.push(numToString(x - y));
	//cout << "x-y = : " << numToString(x - y) << endl;
}

void multiply() {
	double y = stringToNum(s.top());
	s.pop();
	double x = stringToNum(s.top());
	s.pop();
	s.push(numToString(x * y));
}

void normalDivide() {
	double y = stringToNum(s.top());
	s.pop();
	double x = stringToNum(s.top());
	s.pop();
	s.push(numToString((double) x / y));
}

void intDivide() {
	double y = stringToNum(s.top());
	s.pop();
	double x = stringToNum(s.top());
	s.pop();
	s.push(numToString(floor(x / y)));
}

void mod() {
	double y = stringToNum(s.top());
	s.pop();
	double x = stringToNum(s.top());
	s.pop();
	s.push(numToString((int) x % (int) y));			// ATTENTION
}

void push(string v) {
	s.push(v);
}

void pop() {
	s.pop();
}

void copy() {
	string temp = s.top();
	s.push(temp);
}

void print() {
	cout << s.top() << endl;
	s.pop();
}

void halt() {
	exit(0);
}

void rvalue(string l) {
	s.push(data[l]);
}

void lvalue(string l) {
	if (data[l].empty())
		data[l] = "";
	s.push(l);
}

void assign() {
	string value = s.top();
	s.pop();
	string address = s.top();
	s.pop();

	data[address] = value;
	//cout << "data address = " << address << " value " << value << endl;
}

// records the current line number of the label with the key (label)
void label(string l, int &lineNumber) {
	data[l] = numToString(lineNumber);
}

// changes the index of the instruction array in the loop
void goToo(string l, int &currentLine) {
	currentLine = stringToNum(data[l]);
}

// changes the index of the instruction array if the value is zero
void goFalse(string l, int &currentLine) {
	if (stringToNum(s.top()) == 0) {
		currentLine = stringToNum(data[l]);
	}
	s.pop();
}

int main(int argc, char *argv[]) {

	// opens file
	ifstream input(argv[1]);
	if (!input.is_open()) {
		cout << "ERROR: This file cannot be opened." << endl;
		exit(EXIT_FAILURE);
	}

	// reads file line by line and gets the instructions
	string line;
	for (line; getline(input, line);) {
		instructions.push_back(line);
	}

	tokens.resize(instructions.size());

	for (int i = 0; i < instructions.size(); i++) {
		stringstream ss(instructions[i]);
		string current;
		while (ss >> current) {
			tokens[i].push_back(current);
		}
	}


	// first reads labels
	for (int i = 0; i < tokens.size(); i++) {
		for (int j = 0; j < tokens[i].size(); j++) {
			if (tokens[i][j] == "label") {
				j++;
				label(tokens[i][j], i);
			}
		}
	}

	// reads tokens and executes them
	for (int i = 0; i < tokens.size(); i++) {
		for (int j = 0; j < tokens[i].size(); j++) {
			if (tokens[i][j] == "+")
				add();
			else if (tokens[i][j] == "-")
				substract();
			else if (tokens[i][j] == "*")
				multiply();
			else if (tokens[i][j] == "/")
				normalDivide();
			else if (tokens[i][j] == "div")
				intDivide();
			else if (tokens[i][j] == "mod")
				mod();
			else if (tokens[i][j] == "push") {
				j++;
				push(tokens[i][j]);
			} else if (tokens[i][j] == "rvalue") {
				j++;
				rvalue(tokens[i][j]);
			} else if (tokens[i][j] == "lvalue") {
				j++;
				lvalue(tokens[i][j]);
			} else if (tokens[i][j] == "pop")
				pop();
			else if (tokens[i][j] == ":=")
				assign();
			else if (tokens[i][j] == "copy")
				copy();
			else if (tokens[i][j] == "print")
				print();
			else if (tokens[i][j] == "goto") {
				j++;
				goToo(tokens[i][j], i);
			} else if (tokens[i][j] == "gofalse") {
				j++;
				goFalse(tokens[i][j], i);
			} else if (tokens[i][j] == "halt")
				halt();
		}
	}


	// closes file and terminates
	input.close();
	return 0;
}
