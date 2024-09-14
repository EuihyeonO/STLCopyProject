#pragma once

template<typename DataType>
class Node
{
public:
	virtual void operator=(const Node<DataType>* _Node) = 0;

	virtual Node<DataType>* operator++() = 0;
	virtual Node<DataType>* operator++(int) = 0;
	virtual Node<DataType>* operator--() = 0;
	virtual Node<DataType>* operator--(int) = 0;

	virtual const DataType& Get() = 0;
};

template<typename DataType>
class ListNode : public Node<DataType>
{
public:
	void operator=(const Node<DataType>* _Node)
	{
		const ListNode<DataType>* CastedNode = dynamic_cast<const ListNode<DataType>*>(_Node);

		Data = CastedNode->Data;
		PrevNode = CastedNode->PrevNode;
		NextNode = CastedNode->NextNode;
	}

	ListNode<DataType>* operator++() override
	{
		*this = NextNode;
		return this;
	}

	ListNode<DataType>* operator++(int) override
	{
		++(*this);
		return PrevNode;
	}

	ListNode<DataType>* operator--() override
	{
		*this = PrevNode;
		return this;
	}

	ListNode<DataType>* operator--(int) override
	{
		--(*this);
		return NextNode;
	}

	const DataType& Get() override
	{
		return Data;
	}

	DataType Data;
	ListNode<DataType>* PrevNode = nullptr;
	ListNode<DataType>* NextNode = nullptr;
};

template<typename DataType>
class TreeNode : public Node<DataType>
{
public:
	enum NodeColor
	{
		None,
		Red,
		Black,
	};

	void operator=(const Node<DataType>* _Node)
	{
		//const TreeNode<DataType>* CastedNode = dynamic_cast<const TreeNode<DataType>*>(_Node);

		//Data = CastedNode->Data;
		//PrevNode = CastedNode->PrevNode;
		//NextNode = CastedNode->NextNode;
	}

	TreeNode<DataType>* operator++() override
	{
		//*this = NextNode;
		return this;
	}

	TreeNode<DataType>* operator++(int) override
	{
		//++(*this);
		return nullptr;
	}

	TreeNode<DataType>* operator--() override
	{
		//*this = PrevNode;
		return nullptr;
	}

	TreeNode<DataType>* operator--(int) override
	{
		//--(*this);
		return nullptr;
	}

	const DataType& Get() override
	{
		return Data;
	}

	DataType Data;
	
	NodeColor Color = NodeColor::None;

	TreeNode<DataType>* Parent = nullptr;
	TreeNode<DataType>* LeftChild = nullptr;
	TreeNode<DataType>* RightChild = nullptr;
};