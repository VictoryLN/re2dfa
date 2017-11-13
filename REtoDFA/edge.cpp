#pragma once
//模板声明和定义在同一个文件中
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
