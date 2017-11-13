#pragma once
//接收一个NFA，返回其DFA(未最小化)
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <iomanip>
#include "edge.cpp"
#include "postfixRE2NFA.h"
using namespace std;
extern char* states[];

class DFA//确定有限自动机
{
public:
	string chs;//接收的字符集
	void tryAddNode(set<FAnode*>);//搜索集合到状态的映射，如果不存在则新加节点
	vector<FAnode*> nodes;//状态集
	map<set<FAnode*>, FAnode*> set2node;//NFA状态集到DFA状态的映射
	void addTran(char ch, set<FAnode*> from, set<FAnode*> to);//添加状态集到状态集间的转移函数(边)
	FAnode* start;
	void show();
	DFA();
};

struct SetwithFlag//带标记集合
{
	set<FAnode*> s;
	bool flag;
	SetwithFlag(set<FAnode*> s, bool flag);
	bool operator==(SetwithFlag sf);
	bool operator()(const SetwithFlag& a, const SetwithFlag& b);
	bool operator<(const SetwithFlag& a) const;//必须定义此函数set才能用
};

DFA getDFA(NFA nfa,string chs);//输入nfa与字符集，输出dfa
set<FAnode*> e_closure(set<FAnode*> s);//e闭包运算
set<FAnode*> move(set<FAnode*> s, char ch);//状态集接收字符转移后的状态集
bool getUnmark(set<SetwithFlag>& u, set<FAnode*>& sn);//查找首个未标记的集合，并返回真；没找到则返回假