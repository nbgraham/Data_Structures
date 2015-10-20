#pragma once

template <typename DataType>
class Node
{
public:
	DataType data;
	Node<DataType>* next;

	Node(DataType _data);
	Node(DataType _data, Node<DataType>* _next);
	~Node() {};
};

template<typename DataType>
Node<DataType>::Node(DataType _data)
{
	data = _data;
	next = nullptr;
}

template<typename DataType>
Node<DataType>::Node(DataType _data, Node<DataType>* _next)
{
	data = _data;
	next = _next;
}