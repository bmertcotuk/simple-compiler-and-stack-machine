#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>			// string conversions
#include <string>     		// std::string
#include <vector>

using namespace std;

// makes all functions visible to each other
void opt_stms();
void stmt_list();
void expr();
void moreterms();
void term();
void morefactors();
void factor();

// global array
vector<string> tokens;

// output file
ofstream output;

// global index
int current;

bool is_number(const std::string& s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it))
		++it;
	return !s.empty() && it == s.end();
}

bool is_id(string s) {
	return !is_number(s.substr(0, 1));
}

vector<string> tokenize(string whole) {

	vector<string> tempTokens;
	stringstream ss(whole);
	string temp;
	while (ss >> temp) {
		tempTokens.push_back(temp);
	}
	return tempTokens;

}

void match(string expected) {

	if (current < tokens.size()) {
		if (tokens[current] == expected) {
			current++;
		} else {
			cout << "ERROR: '" << expected << "' was expected. found '"
					<< tokens[current] << "'." << endl;
			exit(0);
		}
	}
}

void stm() {

	if (tokens[current] == "begin") {

		match("begin");
		opt_stms();
		match("end");

	} else if (tokens[current] == "print") {

		match("print");
		expr();
		output << "print" << endl;

	} else if (tokens[current] == "if") {

		match("if");

		expr();

		int label = current;
		output << "gofalse " << label << endl;

		match("then");

		stm();

		output << "label " << label << endl;

	} else if (tokens[current] == "while") {

		match("while");

		int label = current;
		output << "label t" << label << endl;

		expr();

		output << "gofalse o" << label << endl;
		match("do");

		stm();

		output << "goto t" << label << endl;
		output << "label o" << label << endl;

	} else if (is_id(tokens[current])) {

		match(tokens[current]);
		output << "lvalue " << tokens[current - 1] << endl;
		match(":=");
		expr();
		output << ":=" << endl;

	} else {

		cout << "ERROR: Missing 'stm'." << endl;
		exit(0);
	}
}

void opt_stms() {
	stmt_list();
}

void stmt_list() {

	stm();
	if (tokens[current] == ";") {
		match(";");
		stmt_list();
	}
}

void expr() {

	term();
	moreterms();

}

void moreterms() {

	if (tokens[current] == "+") {
		match("+");
		term();
		output << "+" << endl;
		moreterms();
	} else if (tokens[current] == "-") {
		match("-");
		term();
		output << "-" << endl;
		moreterms();
	}
}

void term() {

	factor();
	morefactors();

}

void morefactors() {

	if (tokens[current] == "*") {
		match("*");
		factor();
		morefactors();
		output << "*" << endl;
	} else if (tokens[current] == "/") {
		match("/");
		factor();
		morefactors();
		output << "/" << endl;
	} else if (tokens[current] == "div") {
		match("div");
		factor();
		morefactors();
		output << "div" << endl;
	} else if (tokens[current] == "mod") {
		match("mod");
		factor();
		morefactors();
		output << "mod" << endl;
	}
}

void factor() {

	if (tokens[current] == "(") {
		match("(");
		expr();
		match(")");
	} else if (is_id(tokens[current])) {
		//output << "id: " << tokens[current] << endl;
		output << "rvalue " << tokens[current] << endl;
		match(tokens[current]);
	} else if (is_number(tokens[current])) {
		//output << "num: " << tokens[current] << endl;
		output << "push " << tokens[current] << endl;
		match(tokens[current]);
	} else {
		cout << "ERROR: Missing 'factor'." << endl;
		exit(0);
	}
}

int main(int argc, char *argv[]) {					// exe, file input

	// opens file
	ifstream input(argv[1]);							// argv[1]
	if (!input.is_open()) {
		cout << "ERROR: This file cannot be opened.";
		exit(EXIT_FAILURE);
	}

	// output file
	string outName = argv[1];
	outName = outName.substr(0, outName.length() - 1);
	outName += string("m");
	output.open(outName.c_str());

	// reads file as a single whole string
	string whole;
	string line;
	for (line; getline(input, line);) {
		whole += (line + "\n");
	}

	// parses all
	tokens = tokenize(whole);
	current = 0;

	stm();

	if (current < tokens.size()) {
		cout << "ERROR: Illegal end of file." << endl;
	}

	output << "halt" << endl;
	output.close();

	return 0;
}
