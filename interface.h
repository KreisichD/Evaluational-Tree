#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "constants.h"

using namespace std;

class CInterface
{
public:
	//CInterface();
	//~CInterface();
	int iGetInstruction(int & iInstrCode);  // returns code of instraction for line
	int iGetArguments(vector<int> *vArguments);		// returns vector with iNumber arguments
	string sGetExpression();	// returns expression from instruction
	string sGetString();	// returns first substring
	void vPrintVector(vector<string> v_vector, string s_seprarator); // prints variables from vector
	void vReadNext();	// reset 
	void vPrint(string s_text);	// print s_text
	void vPrintError(int i_error_code);	// print error message

private:
	string s_line;
	unsigned int ui_iterator;

	string s_get_substring();
	bool b_is_number(string s_line);
	int i_parse_to_int(string s_number);
};

