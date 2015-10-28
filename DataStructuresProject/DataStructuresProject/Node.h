#pragma once

template <typename DataType>
class Node
{
public:
	DataType data;
	Node<DataType>* next;

	/*
	Constructor*/
	Node(DataType& _data);
	/*
	Constructor*/
	Node(DataType& _data, Node<DataType>* _next);
	/*
	Empty destructor*/
	~Node() {};
};

template<typename DataType>
Node<DataType>::Node(DataType& _data)
{
	data = _data;
	next = nullptr;
}

template<typename DataType>
Node<DataType>::Node(DataType& _data, Node<DataType>* _next)
{
	data = _data;
	next = _next;
}