#include "infix2postfix.h"

string infix2postfix::getPostfix(string infix)
{
	string postfix;
	for (int i = 0; i < infix.length(); i++)
	{
		char ch = infix[i];
		// if in chs
		if (inchs(ch))
			postfix += ch;
		// if in ops
		else if (isOp(ch))//push 
		{
			Op op = getOp(ch);
			CombDir dir = op.dir;
			int priority = op.priority;
			if (op.num == 1)//单目运算符直接输出
			{
				postfix += op.op;
				continue;
			}
			popOp(postfix, op);
			opstk.push(op);
		}
		// if in parens
		else if(isParen(ch))
		{
			if (ch == '(')
				opstk.push(Op('(', minPriority-2,NONE,0));
			else
			{
				popOp(postfix, Op(')', minPriority-1,NONE,0));
				if (opstk.empty())
					printf("too many ')'");
				else
					opstk.pop();//pop '('
			}
		}
	}
	while (!opstk.empty())
	{
		Op top = opstk.top();
		opstk.pop();
		postfix += top.op;
	}
	clearOpStack();
	return postfix;
}

void infix2postfix::clearOpStack()
{
	while (!opstk.empty())
	{
		opstk.pop();
	}
	//printf("stack is empty.\n");
}

void infix2postfix::popOp(string& postfix,Op op)
{
	Op top;
	while (!opstk.empty() && (top = opstk.top()) >= op)
	{
		if (top.dir == Right && top == op )
			break;
		opstk.pop();
		postfix += top.op;
	}
}

bool infix2postfix::isOp(char op)
{
	for (int i = 0; i < opNum; i++)
	{
		if (op == (ops + i)->op)
			return true;
	}
	return false;
}

Op infix2postfix::getOp(char ch)
{
	for (int i = 0; i < opNum; i++)
	{
		if (ch == (ops + i)->op)
			return *(ops + i);
	}
	return Op();
}

infix2postfix::infix2postfix(Op* _ops, int _opNum, string _chs)
{
	ops = _ops;
	opNum = _opNum;
	chs = _chs;
	clearOpStack();
	//get minPriority
	if (opNum >= 1)
		minPriority = ops->priority;
	for (int i = 1; i < opNum; i++)
	{
		if ((ops + i)->priority < minPriority)
			minPriority = (ops + i)->priority;
	}
}

int infix2postfix::getOpPriority(char op)
{
	for (int i = 0; i < opNum; i++)
	{
		if (op == (ops+i)->op)
			return ops->priority;
	}
	//error
	return -1;
}

bool infix2postfix::isParen(char c)
{
	return (c=='(' || c == ')');
}

bool infix2postfix::inchs(char c)
{
	for (int i = 0; i < chs.length(); i++)
	{
		if (c == chs[i])
			return true;
	}
	return false;
}

Op::Op(char _op, int _priority,CombDir _dir,int _opnum)
{
	op = _op;
	priority = _priority;
	dir = _dir;
	num = _opnum;
}

Op::Op()
{
	op = '?';
	priority = 0;
	dir = Left;
}
