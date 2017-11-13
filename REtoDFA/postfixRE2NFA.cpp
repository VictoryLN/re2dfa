#include "postfixRE2NFA.h"
char* states[2] = { "Refuse","Accept" };
NFA::NFA(vector<FAnode*> _nodes, FAnode* _start, FAnode* _end)
{
	nodes = _nodes;
	start = _start;
	end = _end;
}

NFA::NFA()
{
}

void NFA::addNode(FAnode* node,int pos)
{
	nodes.insert(nodes.begin()+pos, node);
}

void NFA::clearNodes()
{
	nodes.clear();
}

int NFA::nodeNum()
{
	return nodes.size();
}

void NFA::show()
{
	printf("NFAshow\n");
	cout << "start: " << start->id<<endl;
	cout << "end: " << end->id << endl;
	cout << endl;
	for (int i = 0; i < nodeNum(); i++)
	{
		nodes[i]->show();
	}
}

FAnode::FAnode(State _state, int _id, vector<Edge<FAnode*>> _edges, int _edgeNum)
{
	state = _state;
	id = _id;
	edges = _edges;
	edgeNum = _edgeNum;
}

FAnode::FAnode(State _state, int _id)
{
	state = _state;
	id = _id;
	edges.clear();
	edgeNum = 0;
}

FAnode::FAnode()
{
}

void FAnode::addEdgeto(char rcv,FAnode* to)
{
	edges.push_back(Edge<FAnode*>(rcv, this, to));
	edgeNum++;
}

void FAnode::show()
{
	printf("FAnodeShow\n");
	printf("node: %5d state: %s\n", id, states[state]);
	cout << "edge number: " << edgeNum << endl;
	cout<< "edges:\n";
	for (int i = 0; i < edges.size(); i++)
	{
		cout << "node " << edges[i].from->id << " -" << edges[i].rcv << "-> node " << edges[i].to->id<<endl;
	}
	cout << endl;
}

Point::Point(State _state, int _id)
{
	state = _state;
	id = _id;
}

Point::Point()
{
}

NFA closure(NFA nfa)
{
	//新建头尾状态
	FAnode* start = new FAnode(REFUSE, 0);
	FAnode* end = new FAnode(ACCEPT, 0);
	//连接4条边
	start->addEdgeto(EP, nfa.start);
	nfa.end->addEdgeto(EP, nfa.start);
	nfa.end->addEdgeto(EP, end);
	start->addEdgeto(EP,end);
	//将新状态加入nfa
	nfa.addNode(start, 0);
	nfa.addNode(end, nfa.nodeNum());
	//更新start end
	nfa.start = start;
	nfa.end = end;
	return nfa;
}

NFA joint(NFA pre, NFA next)
{
	//左NFA尾部连接右NFA头部
	pre.end->addEdgeto(EP, next.start);
	//NFA合并
	for (int i = 0; i < next.nodeNum(); i++)
	{
		pre.addNode(next.nodes[i], pre.nodeNum());
	}
	//更新end
	pre.end = next.end;
	return pre;
}

NFA select(NFA pre, NFA next)
{
	//关键点与closure和joint的类似
	NFA nfa;
	FAnode* start = new FAnode(REFUSE,0);
	FAnode* end = new FAnode(ACCEPT,0);
	start->addEdgeto(EP, pre.start);
	start->addEdgeto(EP, next.start);
	pre.end->addEdgeto(EP, end);
	next.end->addEdgeto(EP, end);
	nfa.start = start;
	nfa.end = end;
	nfa.addNode(start, 0);
	for (int i = 0; i < pre.nodeNum(); i++)
	{
		nfa.addNode(pre.nodes[i], nfa.nodeNum());
	}
	for (int i = 0; i < next.nodeNum(); i++)
	{
		nfa.addNode(next.nodes[i], nfa.nodeNum());
	}
	nfa.addNode(end, nfa.nodeNum());
	return nfa;
}

NFA newMiniNFA(char c)
{
	vector<FAnode*> nodes;
	FAnode* next = new FAnode(ACCEPT, 1);
	FAnode* pre = new FAnode(REFUSE, 0);
	pre->addEdgeto(c, next);
	nodes.push_back(pre);
	nodes.push_back(next);
	NFA nfa = NFA(nodes, pre, next);
	return nfa;
}

NFA getNFA(string postfix)
{
	//用栈“计算”后缀RE
	stack<NFA> stk;
	for (int i = 0; i < postfix.length(); i++)
	{
		char c = postfix[i];
		switch (c)
		{
		case '*':
		{
			NFA nfa = stk.top();
			stk.pop();
			stk.push(closure(nfa));
			break;
		}
		case '|':
		{
			NFA next = stk.top();
			stk.pop();
			NFA pre = stk.top();
			stk.pop();
			stk.push(select(pre, next));
			break;
		}
		case '.':
		{
			NFA next = stk.top();
			stk.pop();
			NFA pre = stk.top();
			stk.pop();
			stk.push(joint(pre, next));
			break;
		}
		default:
		{//说明是字符，单独建nfa
			NFA nfa = newMiniNFA(c);
			stk.push(nfa);
			break;
		}
		}
	}
	NFA rlt = stk.top();
	//赋值id并更新状态的接收情况
	for (int i = 0; i < rlt.nodeNum(); i++)
	{
		if (rlt.end == rlt.nodes[i])
			rlt.nodes[i]->state = ACCEPT;
		else
			rlt.nodes[i]->state = REFUSE;
		rlt.nodes[i]->id = i;
	}
	stk.pop();
	if (!stk.empty())
		printf("Error\n");
	return rlt;
}
