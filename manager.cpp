#include "manager.h"

CTreeManager::CTreeManager()
{
	pc_tree = NULL;
}


CTreeManager::~CTreeManager()
{
	if (pc_tree != NULL) delete pc_tree;
}

void CTreeManager::vRun()
{
	int i_instruction = 0;

	while (i_instruction != I_QUIT)
	{
		i_error_code = NO_ERROR;
		c_interface.vReadNext();	// tell intercace to read command
		i_error_code = c_interface.iGetInstruction(i_instruction);	// get instruction from command

		if (i_error_code == NO_ERROR)	// if it is correct - do it
			v_do_instruction(i_instruction);

		if (i_error_code != NO_ERROR)	// if there was error during execution of instruction - send it to interface to be printed
			c_interface.vPrintError(i_error_code);
	}
}

void CTreeManager::v_enter()
{
	string s_expression = c_interface.sGetExpression();
	if (pc_tree != NULL) delete pc_tree;
	pc_tree = pc_create_tree(s_expression);
}

void CTreeManager::v_vars()
{
	v_chceck_if_created();
	if (i_error_code == NO_ERROR) {
		if (c_interface.sGetString() == EMPTY_STRING)
			c_interface.vPrintVector(pc_tree->vGetVariables(), S_SPACE);
		else i_error_code = WRONG_ARGUMENTS;
	}
}

void CTreeManager::v_print()
{
	v_chceck_if_created();
	if (i_error_code == NO_ERROR) {
		if (c_interface.sGetString() == EMPTY_STRING)
			c_interface.vPrint(pc_tree->sPrintTree() + NEW_LINE);
		else i_error_code = WRONG_ARGUMENTS;
	}
}

void CTreeManager::v_comp()
{
	v_chceck_if_created();
	if (i_error_code == NO_ERROR) {
		vector<int> v_values;
		i_error_code = c_interface.iGetArguments(&v_values);

		if (i_error_code == NO_ERROR)
		{
			double d_result;
			i_error_code = pc_tree->iComputeExpression(v_values, d_result);

			if (i_error_code == NO_ERROR)
				c_interface.vPrint(to_string(d_result) + NEW_LINE);
		}
	}
}

void CTreeManager::v_join()
{
	v_chceck_if_created();
	if (i_error_code == NO_ERROR) 
	{
		string s_expression = c_interface.sGetExpression();

		if (s_expression != EMPTY_STRING) 
		{
			CTree *pc_tmp = pc_create_tree(s_expression);
			*pc_tree = *pc_tree + *pc_tmp;
			delete pc_tmp;
		}
		else i_error_code = WRONG_ARGUMENTS;
	}
}

//void CTreeManager::v_print_leaf()
//{
//	v_chceck_if_created();
//	if (i_error_code == NO_ERROR)
//		if (c_interface.sGetString() == EMPTY_STRING)
//			c_interface.vPrintVector(pc_tree->vPrintLeaf(), NEW_LINE);
//		else i_error_code = WRONG_ARGUMENTS;
//
//}

/* choose method to execute instruction */
void CTreeManager::v_do_instruction(int i_instruction)
{
	switch (i_instruction)
	{
	case I_ENTER:
		v_enter();
		break;
	case I_VARS:
		v_vars();
		break;
	case I_PRINT:
		v_print();
		break;
	case I_COMPUTE:
		v_comp();
		break;
	case I_JOIN:
		v_join();
		break;
	//case I_PRINT_LEAF:
	//	v_print_leaf();
	//	break;
	default:
		break;
	}
}

/* additional function which create new tree from expression and returns poiner to this tree */
CTree * CTreeManager::pc_create_tree(string s_expression)
{
	CTree *pc_tmp = NULL;

	if (s_expression != EMPTY_STRING)
	{
		pc_tmp = new CTree();
		i_error_code = pc_tmp->iCreateTree(s_expression);
		if (i_error_code != NO_ERROR)
			c_interface.vPrint(pc_tmp->sPrintTree());
	}
	else i_error_code = WRONG_ARGUMENTS;

	return pc_tmp;
}

/* check if there is tree created */
void CTreeManager::v_chceck_if_created()
{
	if (pc_tree == NULL)
		i_error_code = NO_TREE_CREATED;
}
/*
bool CTreeManager::b_equal_expressions(string s_first, string s_second)
{
	s_first = s_remove_spaces(s_first);
	s_second = s_remove_spaces(s_second);

	bool b_result = s_first.size() == s_second.size();

	for (unsigned int ii = 0; b_result && ii < s_first.size(); ii++)
		b_result = s_first[ii] == s_second[ii];

	return b_result;
}

string CTreeManager::s_remove_spaces(string s_line)
{
	unsigned int ui_begin = 0;

	while (s_line.at(ui_begin) == SPACE)
		ui_begin++;

	unsigned int ui_end = s_line.size();

	while (ui_end > 0 && s_line.at(ui_end - 1) == SPACE)
		ui_end--;

	return s_line.substr(ui_begin, ui_end - ui_begin);
}
*/