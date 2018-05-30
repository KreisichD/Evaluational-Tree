#pragma once

#include "interface.h"
#include "Tree.h"
#include "constants.h"

class CTreeManager
{
public:
	CTreeManager();
	~CTreeManager();
	void vRun();

private:
	CTree *pc_tree;
	CInterface c_interface;
	//int i_instr_code;
	int i_error_code;

	/* functions supproting interface functions */
	void v_enter();
	void v_vars();
	void v_print();
	void v_comp();
	void v_join();
	//void v_print_leaf();

	/* additional functions */
	void v_do_instruction(int i_instruction);
	CTree* pc_create_tree(string s_expression);
	void v_chceck_if_created();
	//bool b_equal_expressions(string s_first, string s_second);
	//string s_remove_spaces(string s_line);
};

