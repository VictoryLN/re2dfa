#include "NFA2DFA.h"

void DFA::tryAddNode(set<FAnode*> node)
{
	if (set2node.find(node) == set2node.end())//not find
	{
		State state = REFUSE;
		int id;
		vector<Edge<FAnode*>> edges;
		edges.clear();
		int edgeNum;
		edgeNum = 0;
		for (auto i : node)//find state
		{
			if (i->state == ACCEPT)
			{
				state = ACCEPT;
			}
		}
		set2node[node] = new FAnode(state,nodes.size(),edges,edgeNum);//map建立映射
		nodes.push_back(set2node[node]);
	}
}

void DFA::addTran(char ch, set<FAnode*> from, set<FAnode*> to)
{
	
	tryAddNode(from);
	tryAddNode(to);
	set2node[from]->addEdgeto(ch, set2node[to]);
}

void DFA::show()
{
	printf("showDFA\n");
	//cout << "start: " << start->id << endl;
	//cout << endl;
	//for (int i = 0; i < nodes.size(); i++)
	//{
	//	nodes[i]->show();
	//}
	int dig = 0;
	for (int i = nodes.size(); i > 0; i /= 10)
		dig++;
	for (int i = 0; i <= dig; i++)
		printf(" ");
	for (auto c : chs)
	{
		cout << "|" << setw(dig+1) << c;
	}
	cout << endl;
	for (auto i : nodes)
	{
		cout << setw(dig+1) << i->id;
		for (auto c : chs)
		{
			int id;
			bool find = false;
			for (auto ch : i->edges)
			{
				if (ch.rcv == c)
				{
					id = ch.to->id;
					find = true;
					break;
				}
			}
			if (find)
				cout << "|" << setw(dig + 1) << id;
			else
				cout << "|" << setw(dig + 1) << "";
		}
		cout << endl;
	}
}

DFA::DFA()
{
}

bool getUnmark(set<SetwithFlag>& u,set<FAnode*>& um)
{
	for (auto i : u)
	{
		if (i.flag == false)
		{
			//set中元素不能直接更改
			SetwithFlag t(i.s, true);
			u.erase(i);
			u.insert(t);
			um = t.s;
			return true;
		}
	}
	return false;
}

DFA getDFA(NFA nfa, string chs)
{
	DFA dfa;
	FAnode* start = nfa.start;
	bool fst = true;
	set<SetwithFlag> u;
	set<FAnode*> s0;
	s0.insert(start);
	s0 = e_closure(s0);
	SetwithFlag sf(s0,false);
	u.insert(sf);
	set<FAnode*> s;
	while (getUnmark(u,s))
	{
		for (auto c : chs)
		{
			set<FAnode*> m = e_closure(move(s, c));
			if (!m.empty())
			{
				SetwithFlag t(m, false);
				if (u.find(t) == u.end())
				{
					u.insert(t);
				}
				//add D[s,a] = temp
				dfa.addTran(c, s, t.s);
				if (fst)
				{
					dfa.chs = chs;
					dfa.start = dfa.set2node[s];
					fst = false;
				}
			}
			
		}
	}
	return dfa;
}

set<FAnode*> e_closure(set<FAnode*> s)
{
	stack<FAnode*> stk;
	set<FAnode*> rlt;
	for (auto i : s)
		stk.push(i);
	while (!stk.empty())
	{
		FAnode* top = stk.top();
		stk.pop();
		rlt.insert(top);
		for (auto i : top->edges)
		{
			if (i.rcv == EP)
			{
				rlt.insert(i.to);
				stk.push(i.to);
			}
		}
	}
	return rlt;
}

set<FAnode*> move(set<FAnode*> s, char ch)
{	
	set<FAnode*> rlt;
	//for(set<FAnode>::iterator it = s.begin();it!=s.end();it++)
	for (auto it : s)
	{
		for (auto i : it->edges)
		{
			if (i.rcv == ch)
			{
				//if (rlt.find(i.to) == rlt.end())
				//	printf("node %d in set.\n", i.to->id);
				rlt.insert(i.to);
			}
		}
	}
	return rlt;
}

SetwithFlag::SetwithFlag(set<FAnode*> _s, bool _flag):s(_s),flag(_flag)
{
}

bool SetwithFlag::operator==(SetwithFlag sf)
{
	return s == sf.s;
}

bool SetwithFlag::operator()(const SetwithFlag & a, const SetwithFlag & b)
{
	return a.s < b.s;
}

bool SetwithFlag::operator<(const SetwithFlag& a) const
{
	return s<a.s;
}
