#include "Tree.h"

int CTree::iCreateTree(string sExpression)
{
	int i_error = NO_ERROR;
	unsigned int ui_iterator = 0;
	pc_root = new CNode();
	pc_root->vBuildConnections(sExpression, ui_iterator, i_error);
	if (sGetSubstring(ui_iterator, sExpression) != EMPTY_STRING)
		i_error = WRONG_EXPRESSION;
	return i_error;
}

CTree CTree::operator+(CTree & pcOther)
{
	if (pc_root != NULL)
	{
		CTree c_newTree(*this);
		CNode *pc_leaf = c_newTree.pc_root->cGetLastLeaf();
		pc_leaf->vCopy(*pcOther.pc_root);
		return c_newTree;
	}
	else
	{
		CTree c_newTree(pcOther);
		return c_newTree;
	}
}

CTree & CTree::operator=(CTree & pcOther)
{
	if (pc_root != NULL)
		delete pc_root;
	v_copy(pcOther);
	return *this;
}

string CTree::sPrintTree()
{
	string s_result = "";
	if (pc_root != NULL)
	{
		pc_root->vPreOrder(s_result);
	}
	return s_result;
}

vector<string> CTree::vGetVariables()
{
	vector<string> v_result;
	if (pc_root != NULL) 
	{
		pc_root->vSearchForVariables(v_result);
	}
		return v_result;
}

int CTree::iComputeExpression(vector<int> vValues, double & dResult)
{
	int i_error = NO_ERROR;
	if (pc_root != NULL)
	{
		vector<string> v_vars = vGetVariables();
		if (v_vars.size() == vValues.size())
			dResult = pc_root->dComputeValues(v_vars, vValues, i_error);
		else
			i_error = WRONG_ARGUMENTS;
	}
	else
		i_error = NO_TREE_CREATED;
	return i_error;
}

int CTree::iAmmountOfConstants()
{
	int i_result = 0;
	if (pc_root != NULL)
	{
		pc_root->countConstants(i_result);
		return i_result;
	}
	else
	{
		return 0;
	}
}

CNode::~CNode()
{
	for (unsigned int i = 0; i < v_children.size(); i++)
	{
		delete v_children.at(i);
	}
}

void CNode::vInitialize(string &sCurrent, int &iError)
{
	if (sCurrent != EMPTY_STRING)
	{
		s_value = sCurrent;
		v_check_type();
		if (i_type == VARIABLE)
		{
			if (!b_normalize())
			{
				if (s_value == EMPTY_STRING || b_is_constant())
					iError = WRONG_VALUES;
				else
				{
					iError = WRONG_EXPRESSION;
				}
			}
			else if (iError == WRONG_VALUES)
			{
				iError = WRONG_EXPRESSION;
			}
		}
		else if (iError == WRONG_VALUES)
		{
			iError = WRONG_EXPRESSION;
		}
	}
	else
	{
		v_set_basics();
		iError = WRONG_EXPRESSION;
	}
}

void CNode::vPreOrder(string & sResult)
{
	sResult += s_value + S_SPACE;
	for (unsigned int i = 0; i < v_children.size(); i++)
	{
		v_children.at(i) -> vPreOrder(sResult);
	}
}

void CNode::vBuildConnections(string & sExpression, unsigned int & uiIterator, int & iError)
{
	string s_current = sGetSubstring(uiIterator, sExpression);
	vInitialize(s_current, iError);
	while (iError == WRONG_VALUES)
	{
		s_current = sGetSubstring(uiIterator, sExpression);
		vInitialize(s_current, iError);
	}
	if (i_type == ADD || i_type == SUB || i_type == MUL || i_type == DIV)
	{
		for (int i = 0; i < ADD_SUB_MUL_DIV_ARG_NUM; i++)
		{
			CNode *pc_toAdd = new CNode();
			v_children.push_back(pc_toAdd);
			pc_toAdd -> vBuildConnections(sExpression, uiIterator, iError);
		}
	}
	else if (i_type == SIN || i_type == COS)
	{
		CNode *pc_toAdd = new CNode();
		v_children.push_back(pc_toAdd);
		pc_toAdd->vBuildConnections(sExpression, uiIterator, iError);
	}
}

void CNode::v_check_type()
{
	if (s_value == S_ADD)
		i_type = ADD;
	else if (s_value == S_SUB)
		i_type = SUB;
	else if (s_value == S_MUL)
		i_type = MUL;
	else if (s_value == S_DIV)
		i_type = DIV;
	else if (s_value == S_SIN)
		i_type = SIN;
	else if (s_value == S_COS)
		i_type = COS;
	else if (b_is_constant())
			i_type = CONSTANT;
	else
	{
		i_type = VARIABLE;
	}
}

bool CNode::b_is_constant()
{
	bool b_result = true;
	char c_curr;
	for (unsigned int i = 0; b_result && i < s_value.length(); i++)
	{
		c_curr = s_value.at(i);
		if (c_curr < ASCII_FIRST_DIGIT || c_curr > ASCII_LAST_DIGIT)
		{
			b_result = false;
		}
	}
	return b_result;
}

bool CNode::b_normalize()
{
	string s_helper = s_value;
	char c_curr;
	s_value = EMPTY_STRING;
	for (unsigned int i = 0; i < s_helper.length(); i++)
	{
		c_curr = s_helper.at(i);
		if ((c_curr >= ASCII_FIRST_CAPITAL && c_curr <= ASCII_LAST_CAPITAL) ||
			(c_curr >= ASCII_FIRST_SMALL && c_curr <= ASCII_LAST_SMALL) ||
			(c_curr >= ASCII_FIRST_DIGIT && c_curr <= ASCII_LAST_DIGIT))
		{
			s_value += c_curr;
		}
	}
	return s_helper == s_value;
}

void CNode::v_set_basics()
{
	i_type = CONSTANT;
	s_value = DEFAULT_CONSTANT;
}

int CNode::i_get_index(vector<string>& vVars)
{
	bool b_found = false;
	int i = 0;
	while (!b_found)
	{
		if (s_value == vVars.at(i))
		{
			b_found = true;
		}
		else
		{
			i++;
		}
	}
	return i;
}

void CNode::vCopy(CNode & pcOther)
{
	i_type = pcOther.i_type;
	s_value = pcOther.s_value;
	for (unsigned int i = 0; i < v_children.size(); i++)
	{
		delete v_children.at(i);
	}
	for (unsigned int i = 0; i < pcOther.v_children.size(); i++)
	{
		CNode *c_toAdd = new CNode();
		c_toAdd->vCopy(*pcOther.v_children.at(i));
		v_children.push_back(c_toAdd);
	}
}

void CNode::countConstants(int & iResult)
{
	if (i_type == CONSTANT)
	{
		iResult+=stoi(s_value);
	}
	for (unsigned int i = 0; i < v_children.size(); i++)
	{
		v_children.at(i)->countConstants(iResult);
	}
}

void CNode::vSearchForVariables(vector <string> &vResult)
{
	if (i_type == VARIABLE && !vectorContains(s_value, vResult))
	{
		vResult.push_back(s_value);
	}
	for (unsigned int i = 0; i < v_children.size(); i++)
	{
		v_children.at(i)->vSearchForVariables(vResult);
	}
}

double CNode::dComputeValues(vector<string>& vVars, vector<int>& vValues, int & iError)
{
	if (i_type == ADD)
		return (v_children.at(LEFT)->dComputeValues(vVars, vValues, iError) + v_children.at(RIGHT)->dComputeValues(vVars, vValues, iError));
	else if (i_type == SUB)
		return (v_children.at(LEFT)->dComputeValues(vVars, vValues, iError) - v_children.at(RIGHT)->dComputeValues(vVars, vValues, iError));
	else if (i_type == MUL)
		return (v_children.at(LEFT)->dComputeValues(vVars, vValues, iError) * v_children.at(RIGHT)->dComputeValues(vVars, vValues, iError));
	else if (i_type == DIV)
	{
		double d_helper1 = v_children.at(LEFT)->dComputeValues(vVars, vValues, iError);
		double d_helper2 = v_children.at(RIGHT)->dComputeValues(vVars, vValues, iError);
		if (d_helper2 == 0)
		{
			iError = DIVIDE_BY_ZERO;
			return 0;
		}
		else
		{
			return d_helper1 / d_helper2;
		}
	}
	else if (i_type == SIN)
		return sin(v_children.at(0)->dComputeValues(vVars, vValues, iError));
	else if (i_type == COS)
		return cos(v_children.at(0)->dComputeValues(vVars, vValues, iError));
	else if (i_type == CONSTANT)
		return stod(s_value);
	else
	{
		return vValues.at(i_get_index(vVars));
	}
}

CNode * CNode::cGetLastLeaf()
{
	int iChildren = v_children.size();
	if (iChildren > 0)
	{
		return (v_children.back()->cGetLastLeaf());
	}
	else
		return this;
}


string sGetSubstring(unsigned int & uiIterator, string &sLine)
{
	string s_result;

	while (uiIterator < sLine.length() && sLine.at(uiIterator) == SPACE)
		uiIterator++;

	while (uiIterator < sLine.length() && sLine.at(uiIterator) != SPACE)
		s_result += sLine.at(uiIterator++);

	return s_result;
}
template <class T>
bool vectorContains(T & cValue, vector <T> & vToCheck) //T must have == defined
{
	bool b_result = false;
	for (unsigned int i = 0; i < vToCheck.size() && !b_result; i++)
	{
		if (vToCheck.at(i) == cValue)
		{
			b_result = true;
		}
	}
	return b_result;
};