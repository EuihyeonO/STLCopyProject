#pragma once

template<typename DataType>
class ListNode
{
public:
	ListNode()
	{
		Data = DataType();

		PrevNode = nullptr;
		NextNode = nullptr;
	}

	ListNode(const ListNode<DataType>* _Node)
	{
		Data = _Node->Data;
		PrevNode = _Node->PrevNode;
		NextNode = _Node->NextNode;
	}

	void operator=(const ListNode<DataType>* _Node)
	{
		Data = _Node->Data;
		PrevNode = _Node->PrevNode;
		NextNode = _Node->NextNode;
	}

	ListNode<DataType>* operator++()
	{
		*this = NextNode;
		return this;
	}

	ListNode<DataType>* operator++(int)
	{
		++(*this);
		return PrevNode;
	}

	ListNode<DataType>* operator--()
	{
		*this = PrevNode;
		return this;
	}

	ListNode<DataType>* operator--(int)
	{
		--(*this);
		return NextNode;
	}

	DataType& operator*()
	{
		return Data;
	}

	const DataType& Get()
	{
		return Data;
	}

	DataType Data;
	ListNode<DataType>* PrevNode = nullptr;
	ListNode<DataType>* NextNode = nullptr;
};