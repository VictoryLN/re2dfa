#include "infix2postfix.h"
#include "NFA2DFA.h"
#include "postfixRE2NFA.h"
#include <iostream>
#include <string>
using namespace std;
bool inchs(string chs,char c)
{
	for (int i = 0; i < chs.length(); i++)
	{
		if (c == chs[i])
			return true;
	}
	return false;
}

bool isSelectSyb(char c)
{
	return c == '|';
}
string addJiontSybol(string re,string chs)
{
	string infix;
	int pre = -1;
	bool needSyb = false;
	bool orSyb = false;
	for (int i = 0; i < re.length(); i++)
	{
		if (inchs(chs, re[i]) && !needSyb)
		{
			needSyb = true;
			pre = i;
		}
		else if (isSelectSyb(re[i]))
		{
			needSyb = false;
		}
		else if (inchs(chs, re[i]) && needSyb)
		{//add jiont
			if (re[i - 1] == '(')
				infix.insert(infix.length()-1, ".");
			else
				infix += '.';
			pre = i;
		}
		infix += re[i];
	}
	return infix;
}
int main()
{
	Op ops[3] = { Op('*',3,Right,1),Op('|',2,Left,2),Op('.',1,Left,2) };
	string chs = "abc";//字符集别用E，E用来表示epsilon
	string re;
	string infix;
	string postfix;
	cin >> re;
	infix = addJiontSybol(re,chs);
	cout << "infix: " << infix << endl;
	infix2postfix i2p = infix2postfix(ops, 3, chs);
	postfix = i2p.getPostfix(infix);
	cout <<"postfix:"<< postfix<<endl;
	NFA nfa = getNFA(postfix);
	nfa.show();
	DFA dfa = getDFA(nfa,chs);
	dfa.show();
}