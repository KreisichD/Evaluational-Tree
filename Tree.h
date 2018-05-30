#pragma once
#include <vector>
#include <string>
#include "constants.h"
#include <math.h>
using namespace std;



class CNode {
public:
	CNode() { s_value = EMPTY_STRING; };
	CNode(CNode &pcOther) { vCopy(pcOther); };
	~CNode();
	void vInitialize(string &sCurrent, int &iError);
	void vPreOrder(string &sResult);
	void vBuildConnections(string &sExpression, unsigned int &uiIterator, int &iError);
	void vSearchForVariables(vector <string> &vResult);
	double dComputeValues(vector <string> &vVars, vector<int> &vValues, int &iError);
	CNode * cGetLastLeaf();
	void vCopy(CNode &pcOther);
	void countConstants(int & iResult);
private:
	int i_type;
	string s_value;
	vector <CNode*> v_children;

	void v_check_type();
	bool b_is_constant();
	bool b_normalize();
	void v_set_basics();

	int i_get_index(vector <string> &vVars);
	

};
class CTree {
public:
	CTree() { pc_root = NULL; }
	CTree(CTree &pcOther) { v_copy(pcOther);}
	~CTree() { delete pc_root; }
	int iCreateTree(string sExpression);
	CTree operator+(CTree &pcOther);
	CTree & operator=(CTree &pcOther);
	string sPrintTree();
	vector <string> vGetVariables();
	int iComputeExpression(vector<int> vValues, double &dResult);
	int iAmmountOfConstants();
private:
	CNode *pc_root;

	void v_copy(CTree &pcOther) { if (pcOther.pc_root != NULL) pc_root = new CNode(*pcOther.pc_root); else pc_root = NULL; };
};

string sGetSubstring(unsigned int &uiIterator, string &sLine);
template <class T> bool vectorContains(T & cValue, vector <T> & vToCheck);;