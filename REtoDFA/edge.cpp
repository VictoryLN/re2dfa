#pragma once
//ģ�������Ͷ�����ͬһ���ļ���
template <typename T>
class Edge
{
public:
	char rcv;
	T from;
	T to;
	Edge(char _rcv, T _from, T _to);
	Edge();
};

template<typename T>
Edge<T>::Edge(char _rcv, T _from, T _to)
{
	rcv = _rcv;
	from = _from;
	to = _to;
}

template<typename T>
Edge<T>::Edge()
{
}
