#pragma once
//����һ����׺RE������һ��NFA
#include <iostream>
#include "edge.cpp"
#include <vector>
#include <string>
#include <stack>
#define EP 'E'//���޷��������E��ʾ
using namespace std;
enum State//״̬���ܾ�����գ�
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

class FAnode:public Point//FA�ڵ�
{
public:
	vector<Edge<FAnode*>> edges;//�߼�
	int edgeNum;//����������¼
	FAnode(State _state, int _id, vector<Edge<FAnode*>> _edges, int _edgeNum);
	FAnode(State _state, int id);
	FAnode();
	void addEdgeto(char rcv,FAnode* to);//������״̬�����ض��ַ���Ŀ��״̬�ı�(ת�ƺ���)
	void show();
};
class NFA//��ȷ�������Զ���
{
public:
	vector<FAnode*> nodes;//״̬��
	FAnode* start;//��ʼ״̬
	FAnode* end;//�ս�״̬
	NFA(vector<FAnode*> nodes,FAnode* start,FAnode* end);
	NFA();
	void addNode(FAnode* node,int pos);//��״̬����posλ�ò���״̬node
	void clearNodes();
	int nodeNum();//����״̬��Ŀ
	void show();
};

NFA getNFA(string postfix);//���պ�׺RE������NFA
NFA closure(NFA nfa);//����NFA�ıհ�
NFA joint(NFA pre, NFA next);//������NFA������
NFA select(NFA pre, NFA next);//������NFA��ѡ��
NFA newMiniNFA(char c);//�����ַ��Ļ���NFA