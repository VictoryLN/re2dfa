#pragma once
#include <iostream>
#include <stack>
#define MAX_PRIORITY 10
using namespace std;

/*
操作符: "*","|",".","(",")"
操作数:
优先级: "()" > "*" > "." > "|"
中缀表达式转后缀表达式的方法：
1.遇到操作数：直接输出（添加到后缀表达式中）
2.栈为空时，遇到运算符，直接入栈
3.遇到左括号：将其入栈
4.遇到右括号：执行出栈操作，并将出栈的元素输出，直到弹出栈的是左括号，左括号不输出。
5.遇到其他运算符：加减乘除：弹出所有优先级大于或者等于该运算符的栈顶元素，然后将该运算符入栈
6.最终将栈中的元素依次出栈，输出。
*/
//结合方向
enum CombDir
{
	Left,
	Right,
	NONE
};
//操作符
struct Op
{
	char op;//操作符
	int priority;//优先级
	int num;//操作数个数
	CombDir dir;//结合方向
	friend bool operator>(Op op1,Op op2)
	{
		return op1.priority > op2.priority;
	}
	friend bool operator<(Op op1, Op op2)
	{
		return op1.priority < op2.priority;
	}
	friend bool operator==(Op op1, Op op2)
	{
		return op1.priority == op2.priority;
	}
	friend bool operator>=(Op op1, Op op2)
	{
		return op1.priority >= op2.priority;
	}
	friend bool operator<=(Op op1, Op op2)
	{
		return op1.priority <= op2.priority;
	}
	Op(char _op, int _priority,CombDir _dir,int _opnum);
	Op();
};
//中缀转后缀
class infix2postfix
{
private:
	Op* ops;//操作符集
	int opNum;//操作符集长度
	int minPriority;//最小优先度
	string chs;//字符集
	stack<Op> opstk;//操作符栈
	int getOpPriority(char op);
	bool isParen(char c);//括号判断
	bool inchs(char c);//字符合法判断
	void popOp(string& postfix, Op op);
public:
	Op getOp(char c);
	infix2postfix(Op* _ops, int _opNum, string _chs);
	string getPostfix(string infix);//参数为中缀式，返回后缀式
	void clearOpStack();
	bool isOp(char op);
};