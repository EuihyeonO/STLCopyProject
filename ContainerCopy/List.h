#pragma once
#include "ExceptionFunction.h"
#include "Iterator.h"

template <typename DataType>
class List
{
private:
	using MyNode = typename ListNode<DataType>;

public:
	using Iterator = typename BidirectionalIterator<DataType>;

public:

	List()
	{
		CreateDummyNode();
	}

	List(size_t _Size)
	{
		CreateDummyNode();
		
		for (int i = 0; i < _Size; i++)
		{
			Push_Back(DataType());
		}
	}

	List(size_t _Size, const DataType& _Data)
	{
		CreateDummyNode();

		for (int i = 0; i < _Size; i++)
		{
			Push_Back(_Data);
		}
	}

	List(size_t _Size, DataType&& _Data)
	{
		CreateDummyNode();

		for (int i = 0; i < _Size; i++)
		{
			Push_Back(_Data);
		}
	}

public:
	Iterator Begin()
	{
		return Iterator(Head->NextNode);
	}

	Iterator End()
	{
		return Iterator(Tail);
	}

public:
	void Push_Back(const DataType& _Data)
	{
		MyNode* NewNode = new MyNode();
		NewNode->DataPtr = _Data;

		MyNode* CurBackNode = Tail->PrevNode;
		CurBackNode->NextNode = NewNode;

		NewNode->PrevNode = CurBackNode;
		NewNode->NextNode = Tail;

		Tail->PrevNode = NewNode;

		MySize++;
	}

	void Push_Back(DataType&& _Data)
	{
		MyNode* NewNode = new MyNode();
		NewNode->Data = _Data;

		MyNode* CurBackNode = Tail->PrevNode;
		CurBackNode->NextNode = NewNode;

		NewNode->PrevNode = CurBackNode;
		NewNode->NextNode = Tail;

		Tail->PrevNode = NewNode;

		MySize++;
	}

	const DataType& Front()
	{
		ExceptionFunction::CheckException(Head->NextNode == nullptr, true, typeid(*this).name(), ExceptionType::OutOfRange);
		return Head->NextNode->DataPtr;
	}

	const DataType& Back()
	{
		ExceptionFunction::CheckException(Tail->PrevNode == nullptr, true, typeid(*this).name(), ExceptionType::OutOfRange);
		return Tail->PrevNode->DataPtr;
	}
	
	size_t Size()
	{
		return MySize;
	}

private:
	void CreateDummyNode()
	{
		MyNode* DummyHead = new MyNode();
		MyNode* DummyTail = new MyNode();

		Head = DummyHead;
		Tail = DummyTail;

		DummyTail->PrevNode = Head;
		DummyHead->NextNode = Tail;
	}

private:
	MyNode* Head = nullptr;
	MyNode* Tail = nullptr;
	
	size_t MySize = 0;
};