#pragma once

template<typename DataType>
class Node
{
public:
	void operator=(const Node* _Node)
	{
		Data = _Node->Data;
		PrevNode = _Node->PrevNode;
		NextNode = _Node->NextNode;
	}

	const Node* operator++()
	{
		*this = NextNode;
		return *this;
	}

	const Node operator++(int)
	{
		Node ReturnNode = NextNode;
		++(*this);
		return ReturnNode;
	}

	const Node* operator--()
	{
		*this = PrevNode;
		return *this;
	}

	const Node* operator--(int)
	{
		Node ReturnNode = PrevNode;
		--(*this);
		return ReturnNode;
	}

	DataType Data;
	Node* PrevNode = nullptr;
	Node* NextNode = nullptr;
};

template<typename DataType>
class BidirectionalIterator
{
	using Node = typename Node<DataType>;
public:
	BidirectionalIterator(const Node* _Node)
	{
		NodePtr = const_cast<Node*>(_Node);
	}
	
	BidirectionalIterator(Node&& _Node)
	{
		NodePtr = _Node;

		_Node.PrevNode = nullptr;
		_Node.NextNode = nullptr;
	}

	const DataType& operator*()
	{
		return NodePtr->Data;
	}

	BidirectionalIterator& operator--()
	{
		NodePtr = NodePtr->PrevNode;
		return *this;
	}

	BidirectionalIterator operator--(int)
	{
		Node* ReturnNode = NodePtr;
		NodePtr = NodePtr->PrevNode;
		return BidirectionalIterator(ReturnNode);
	}

	BidirectionalIterator& operator++()
	{
		NodePtr = NodePtr->NextNode;
		return *this;
	}

	BidirectionalIterator operator++(int)
	{
		Node* ReturnNode = NodePtr;
		NodePtr = NodePtr->NextNode;
		return BidirectionalIterator(ReturnNode);
	}

private:
	Node* NodePtr = nullptr;
};