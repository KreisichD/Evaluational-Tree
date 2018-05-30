#include "interface.h"

using namespace std;

/* returns code of instraction for line */
int CInterface::iGetInstruction(int & iInstrCode)
{
	string s_instruction = s_get_substring();  // take first word from s_line

	if (s_instruction == S_ENTER)		// and tries to match it witch available instructions
		iInstrCode = I_ENTER;
	else if (s_instruction == S_VARS)
		iInstrCode = I_VARS;
	else if (s_instruction == S_PRINT)
		iInstrCode = I_PRINT;
	else if (s_instruction == S_COMPUTE)
		iInstrCode = I_COMPUTE;
	else if (s_instruction == S_JOIN)
		iInstrCode = I_JOIN;
	else if (s_instruction == S_QUIT)
		iInstrCode = I_QUIT;
	//else if (s_instruction == S_PRINT_LEAF)
	//	iInstrCode = I_PRINT_LEAF;
	else return WRONG_INSTRUCTION;

	return NO_ERROR;
}

/* returns vector with iNumber arguments */
int CInterface::iGetArguments(vector<int> *vArguments)
{
	while (ui_iterator < s_line.length())
	{
		string s_part = s_get_substring();	// read part of instruction
		if (s_part.length() > 0)
			if (b_is_number(s_part))		// if it is a number then add it to vector
				(*vArguments).push_back(i_parse_to_int(s_part));
			else return WRONG_ARGUMENTS;
	}
	return NO_ERROR;		
}

/* returns expression from instruction */
string CInterface::sGetExpression()
{
	unsigned int ui_start = ui_iterator;
	ui_iterator = s_line.size();
	return s_line.substr(ui_start, ui_iterator);
}

/* returns first substring */
string CInterface::sGetString()
{
	return s_get_substring();
}

/* prints variables from vector */
void CInterface::vPrintVector(vector<string> v_vector, string s_separator)
{
	for (size_t ii = 0; ii < v_vector.size(); ii++)
		cout << v_vector[ii] << s_separator;
	cout << endl;
}

/* read another command */
void CInterface::vReadNext()
{
	getline(cin, s_line);
	ui_iterator = 0;
}

/* print s_text to console */
void CInterface::vPrint(string s_text)
{
	cout << s_text;
}

/* print error message */
void CInterface::vPrintError(int i_error_code)
{
	switch (i_error_code)
	{
	case WRONG_EXPRESSION:
		cout << WRONG_EXPRESSION_MESSAGE;
		break;
	case WRONG_VALUES:
		cout << WRONG_VALUES_MESSAGE;
		break;
	case DIVIDE_BY_ZERO:
		cout << DIVIDE_BY_ZERO_MESSAGE;
		break;
	case WRONG_INSTRUCTION:
		cout << WRONG_INSTRUCTION_MESSAGE;
		break;
	case WRONG_ARGUMENTS:
		cout << WRONG_ARGUMENTS_MESSAGE;
		break;
	case NO_TREE_CREATED:
		cout << NO_TREE_CREATED_MESSAGE;
		break;
	default:
		break;
	}
	cout << endl;
}

/* get next part of instruction */
string CInterface::s_get_substring()
{
	string s_result;

	while (ui_iterator < s_line.length() && s_line.at(ui_iterator) == SPACE)
		ui_iterator++;

	while (ui_iterator < s_line.length() && s_line.at(ui_iterator) != SPACE)
		s_result += s_line.at(ui_iterator++);

	return s_result;
}

/* chceck if s_line is numeric */
bool CInterface::b_is_number(string s_line)
{
	bool b_is_number = s_line.length() != 0;

	for (unsigned int ii = s_line.at(0) == ASCII_MINUS ? 1 : 0; ii < s_line.length() && b_is_number; ii++) {
		char c_sign = s_line.at(ii);
		if ((int)c_sign < ASCII_FIRST_DIGIT || (int)c_sign > ASCII_LAST_DIGIT)
			b_is_number = false;
	}

	return b_is_number;
}

/* parse s_number to int */
int CInterface::i_parse_to_int(string s_number)
{
	int i_result = 0;

	for (unsigned int ii = s_number.at(0) == ASCII_MINUS ? 1 : 0; ii < s_number.length(); ii++) {
		i_result *= DECIMAL_SYSTEM_BASE;
		i_result += (int)s_number.at(ii) - ASCII_FIRST_DIGIT;
	}

	return s_number.at(0) == ASCII_MINUS ? i_result*(-1) : i_result;
}
