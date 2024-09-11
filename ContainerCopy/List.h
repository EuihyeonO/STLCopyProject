#pragma once
#include "ExceptionFunction.h"
#include "Iterator.h"

template <typename DataType>
class List
{
	class Node;
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
	void Push_Back(const DataType& _Data)
	{
		Node* NewNode = new Node();
		NewNode->DataPtr = _Data;

		Node* CurBackNode = Tail->PrevNode;
		CurBackNode->NextNode = NewNode;

		NewNode->PrevNode = CurBackNode;
		NewNode->NextNode = Tail;

		Tail->PrevNode = NewNode;

		MySize++;
	}

	void Push_Back(DataType&& _Data)
	{
		Node* NewNode = new Node();
		NewNode->DataPtr = _Data;

		Node* CurBackNode = Tail->PrevNode;
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

private:
	class Node
	{
	public:
		void operator=(const Node* _Node)
		{
			DataPtr = _Node->DataPtr;
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

		DataType* DataPtr = nullptr;
		Node* PrevNode = nullptr;
		Node* NextNode = nullptr;
	};

private:
	void CreateDummyNode()
	{
		Node* DummyHead = new Node();
		Node* DummyTail = new Node();

		Head = DummyHead;
		Tail = DummyTail;

		DummyTail->PrevNode = Head;
		DummyHead->NextNode = Tail;
	}

private:
	Node* Head = nullptr;
	Node* Tail = nullptr;
	
	size_t MySize = 0;
};