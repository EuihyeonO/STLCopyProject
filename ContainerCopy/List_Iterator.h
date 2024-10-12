#pragma once
#include "ListNode.h"
#include "Iterator.h"

template <typename DataType>
class List_Iterator
{
public:
	using Iterator_Category = typename Bidirectional_Iterator_Tag;

public:
	List_Iterator(const ListNode<DataType>* _Node)
	{
		NodePtr = const_cast<ListNode<DataType>*>(_Node);
	}

	List_Iterator(const List_Iterator& _Other)
	{
		NodePtr = _Other.NodePtr;
	}

	List_Iterator& operator=(const List_Iterator& _Other)
	{
		NodePtr = _Other.NodePtr;
		return *this;
	}

	List_Iterator& operator=(List_Iterator&& _Other) noexcept
	{
		NodePtr = _Other.NodePtr;
		_Other.NodePtr = nullptr;

		return *this;
	}

	bool operator==(const List_Iterator& _Other) const
	{
		return (NodePtr == _Other.NodePtr);
	}

	bool operator!=(const List_Iterator& _Other) const
	{
		return !(*this == _Other);
	}

	List_Iterator& operator++()
	{
		NodePtr = NodePtr->NextNode;
		return *this;
	}

	List_Iterator operator++(int)
	{
		List_Iterator ReturnIter(*this);
		++(*this);
		return ReturnIter;
	}

	List_Iterator& operator--()
	{
		NodePtr = NodePtr->PrevNode;
		return *this;
	}

	List_Iterator operator--(int)
	{
		List_Iterator ReturnIter(*this);
		--(*this);
		return ReturnIter;
	}

	DataType& operator*()
	{
		return *(*NodePtr);
	}

protected:
	ListNode<DataType>* NodePtr = nullptr;
};
