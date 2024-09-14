#pragma once

#include "Node.h"

//template <typename T, typename DataType>
//concept ValidNode = std::derived_from<T, Node<DataType>>;

template<typename DataType>
class BidirectionalIterator
{
	using Node = typename Node<DataType>;
public:
	//BidirectionalIterator(const Node* _Node)
	//{
	//	NodePtr = const_cast<Node*>(_Node);
	//}
	//
	//BidirectionalIterator(Node&& _Node)
	//{
	//	NodePtr = _Node;
	//
	//	_Node.PrevNode = nullptr;
	//	_Node.NextNode = nullptr;
	//}
	//
	//const DataType& operator*()
	//{
	//	return NodePtr->Get();
	//}
	//
	//BidirectionalIterator& operator--()
	//{
	//	NodePtr = NodePtr->PrevNode;
	//	return *this;
	//}
	//
	//BidirectionalIterator operator--(int)
	//{
	//	Node* ReturnNode = NodePtr;
	//	NodePtr = NodePtr->PrevNode;
	//	return BidirectionalIterator(ReturnNode);
	//}
	//
	//BidirectionalIterator& operator++()
	//{
	//	NodePtr = NodePtr->NextNode;
	//	return *this;
	//}
	//
	//BidirectionalIterator operator++(int)
	//{
	//	Node* ReturnNode = NodePtr;
	//	NodePtr = NodePtr->NextNode;
	//	return BidirectionalIterator(ReturnNode);
	//}

private:
	Node* NodePtr = nullptr;
};