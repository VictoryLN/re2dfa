#pragma once
//接收一个后缀RE，返回一个NFA
#include <iostream>
#include "edge.cpp"
#include <vector>
#include <string>
#include <stack>
#define EP 'E'//ε无法输出，用E表示
using namespace std;
enum State//状态（拒绝或接收）
{
	REFUSE,
	ACCEPT
};

class Point
{
public:
	State state;
	int id;
	Point(State _state, int _id);
	Point();
};

class FAnode:public Point//FA节点
{
public:
	vector<Edge<FAnode*>> edges;//边集
	int edgeNum;//边数，纯记录
	FAnode(State _state, int _id, vector<Edge<FAnode*>> _edges, int _edgeNum);
	FAnode(State _state, int id);
	FAnode();
	void addEdgeto(char rcv,FAnode* to);//创建此状态接收特定字符到目标状态的边(转移函数)
	void show();
};
class NFA//不确定有限自动机
{
public:
	vector<FAnode*> nodes;//状态集
	FAnode* start;//起始状态
	FAnode* end;//终结状态
	NFA(vector<FAnode*> nodes,FAnode* start,FAnode* end);
	NFA();
	void addNode(FAnode* node,int pos);//于状态集中pos位置插入状态node
	void clearNodes();
	int nodeNum();//返回状态数目
	void show();
};

NFA getNFA(string postfix);//接收后缀RE，返回NFA
NFA closure(NFA nfa);//返回NFA的闭包
NFA joint(NFA pre, NFA next);//返回两NFA的连接
NFA select(NFA pre, NFA next);//返回两NFA的选择
NFA newMiniNFA(char c);//接收字符的基础NFA