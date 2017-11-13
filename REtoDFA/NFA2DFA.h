#pragma once
//����һ��NFA��������DFA(δ��С��)
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

class DFA//ȷ�������Զ���
{
public:
	string chs;//���յ��ַ���
	void tryAddNode(set<FAnode*>);//�������ϵ�״̬��ӳ�䣬������������¼ӽڵ�
	vector<FAnode*> nodes;//״̬��
	map<set<FAnode*>, FAnode*> set2node;//NFA״̬����DFA״̬��ӳ��
	void addTran(char ch, set<FAnode*> from, set<FAnode*> to);//���״̬����״̬�����ת�ƺ���(��)
	FAnode* start;
	void show();
	DFA();
};

struct SetwithFlag//����Ǽ���
{
	set<FAnode*> s;
	bool flag;
	SetwithFlag(set<FAnode*> s, bool flag);
	bool operator==(SetwithFlag sf);
	bool operator()(const SetwithFlag& a, const SetwithFlag& b);
	bool operator<(const SetwithFlag& a) const;//���붨��˺���set������
};

DFA getDFA(NFA nfa,string chs);//����nfa���ַ��������dfa
set<FAnode*> e_closure(set<FAnode*> s);//e�հ�����
set<FAnode*> move(set<FAnode*> s, char ch);//״̬�������ַ�ת�ƺ��״̬��
bool getUnmark(set<SetwithFlag>& u, set<FAnode*>& sn);//�����׸�δ��ǵļ��ϣ��������棻û�ҵ��򷵻ؼ�