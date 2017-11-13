#pragma once
#include <iostream>
#include <stack>
#define MAX_PRIORITY 10
using namespace std;

/*
������: "*","|",".","(",")"
������:
���ȼ�: "()" > "*" > "." > "|"
��׺���ʽת��׺���ʽ�ķ�����
1.������������ֱ���������ӵ���׺���ʽ�У�
2.ջΪ��ʱ�������������ֱ����ջ
3.���������ţ�������ջ
4.���������ţ�ִ�г�ջ������������ջ��Ԫ�������ֱ������ջ���������ţ������Ų������
5.����������������Ӽ��˳��������������ȼ����ڻ��ߵ��ڸ��������ջ��Ԫ�أ�Ȼ�󽫸��������ջ
6.���ս�ջ�е�Ԫ�����γ�ջ�������
*/
//��Ϸ���
enum CombDir
{
	Left,
	Right,
	NONE
};
//������
struct Op
{
	char op;//������
	int priority;//���ȼ�
	int num;//����������
	CombDir dir;//��Ϸ���
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
//��׺ת��׺
class infix2postfix
{
private:
	Op* ops;//��������
	int opNum;//������������
	int minPriority;//��С���ȶ�
	string chs;//�ַ���
	stack<Op> opstk;//������ջ
	int getOpPriority(char op);
	bool isParen(char c);//�����ж�
	bool inchs(char c);//�ַ��Ϸ��ж�
	void popOp(string& postfix, Op op);
public:
	Op getOp(char c);
	infix2postfix(Op* _ops, int _opNum, string _chs);
	string getPostfix(string infix);//����Ϊ��׺ʽ�����غ�׺ʽ
	void clearOpStack();
	bool isOp(char op);
};