#pragma once
#include "Set_Iterator.h"

#include <string>

template<typename DataType>
class Set
{
private:
	using MyNode = typename TreeNode<DataType>;

public:
	using Iterator = typename Set_Iterator<DataType>;

public:
	Set()
	{
		NilNode = new MyNode();
		NilNode->Color = MyNode::NodeColor::Black;

		NilNode->LeftChild = NilNode;
		NilNode->RightChild = NilNode;
	}

	void Insert(const DataType& _Data)
	{
		MyNode* NewNode = InsertNewElement(_Data);

		if (NewNode == nullptr)
		{
			return;
		}

		MySize++;

		//더블레드발생
		while(NewNode != nullptr && NewNode != RootNode && (NewNode->Color == MyNode::NodeColor::Red && NewNode->Parent->Color == MyNode::NodeColor::Red))
		{
			NewNode = Balancing(NewNode);
		}
	}

private:
	MyNode* InsertNewElement(const DataType& _Data)
	{
		MyNode* NewNode = nullptr;

		if (RootNode == nullptr)
		{
			NewNode = CreateNewNode(_Data);

			RootNode = NewNode;
			RootNode->Parent = NilNode;
			RootNode->Color = MyNode::NodeColor::Black;
		}
		else
		{
			MyNode* CurNode = RootNode;

			while (true)
			{
				if (_Data < CurNode->Data)
				{
					if (CurNode->LeftChild == NilNode)
					{
						NewNode = CreateNewNode(_Data);

						CurNode->LeftChild = NewNode;
						NewNode->Parent = CurNode;

						break;
					}
					else
					{
						CurNode = CurNode->LeftChild;
					}
				}
				else if (_Data > CurNode->Data)
				{
					if (CurNode->RightChild == NilNode)
					{
						NewNode = CreateNewNode(_Data);

						CurNode->RightChild = NewNode;
						NewNode->Parent = CurNode;

						break;
					}
					else
					{
						CurNode = CurNode->RightChild;
					}
				}
				if (_Data == CurNode->Data)
				{
					return NewNode;
				}
			}
		}

		return NewNode;
	}

	MyNode* CreateNewNode(const DataType& _Data)
	{
		MyNode* NewNode = new MyNode();

		NewNode->Data = _Data;
		NewNode->Color = MyNode::NodeColor::Red;
		NewNode->LeftChild = NilNode;
		NewNode->RightChild = NilNode;
		
		return NewNode;
	}

	MyNode* Balancing(MyNode* _InsertedNode)
	{
		if (_InsertedNode->Parent == NilNode)
		{
			return _InsertedNode;
		}

		MyNode* UncleNode = nullptr;
		MyNode* ParentNode = _InsertedNode->Parent;
		MyNode* Ancestor = _InsertedNode->Parent->Parent;

		if (ParentNode == Ancestor->LeftChild)
		{
			UncleNode = Ancestor->RightChild;
		}
		else if (ParentNode == Ancestor->RightChild)
		{
			UncleNode = Ancestor->LeftChild;
		}

		MyNode* ReturnNode = nullptr;

		if (UncleNode->Color == MyNode::NodeColor::Black)
		{
			ReturnNode = Restructuring(_InsertedNode, UncleNode);
		}
		else if (UncleNode->Color == MyNode::NodeColor::Red)
		{
			ReturnNode = ReColoring(_InsertedNode, UncleNode);
		}

		return ReturnNode;
	}

	MyNode* ReColoring(MyNode* _InsertedNode, MyNode* _UncleNode)
	{
		_InsertedNode->Parent->Color = MyNode::NodeColor::Black;
		_UncleNode->Color = MyNode::NodeColor::Black;

		_InsertedNode->Parent->Parent->Color = MyNode::NodeColor::Red;

		RootNode->Color = MyNode::NodeColor::Black;

		return _InsertedNode->Parent->Parent;
	}

	MyNode* Restructuring(MyNode* _InsertedNode, MyNode* _UncleNode)
	{
		MyNode* ParentNode = _InsertedNode->Parent;
		MyNode* AncestorNode = _InsertedNode->Parent->Parent;

		if (ParentNode == AncestorNode->LeftChild && _InsertedNode == ParentNode->LeftChild)
		{
			if (ParentNode->RightChild != NilNode)
			{
				AncestorNode->LeftChild = ParentNode->RightChild;
				AncestorNode->LeftChild->Parent = AncestorNode;
			}

			ParentNode->RightChild = AncestorNode;
			ParentNode->Parent = AncestorNode->Parent;
			
			if (AncestorNode == RootNode)
			{
				RootNode = ParentNode;
			}
			else if (AncestorNode->Parent->LeftChild == AncestorNode)
			{
				AncestorNode->Parent->LeftChild = ParentNode;
			}
			else if (AncestorNode->Parent->RightChild == AncestorNode)
			{
				AncestorNode->Parent->RightChild = ParentNode;
			}

			AncestorNode->Parent = ParentNode;
			AncestorNode->LeftChild = NilNode;

			ParentNode->Color = MyNode::NodeColor::Black;
			ParentNode->LeftChild->Color = MyNode::NodeColor::Red;
			ParentNode->RightChild->Color = MyNode::NodeColor::Red;
		}
		else if (ParentNode == AncestorNode->LeftChild && _InsertedNode == ParentNode->RightChild)
		{
			_InsertedNode->LeftChild = ParentNode;
			_InsertedNode->RightChild = AncestorNode;

			ParentNode->RightChild = NilNode;
			AncestorNode->LeftChild = NilNode;

			_InsertedNode->Parent = AncestorNode->Parent;

			if (AncestorNode == RootNode)
			{
				RootNode = _InsertedNode;
			}
			else if (AncestorNode->Parent->LeftChild == AncestorNode)
			{
				AncestorNode->Parent->LeftChild = _InsertedNode;
			}
			else if (AncestorNode->Parent->RightChild == AncestorNode)
			{
				AncestorNode->Parent->RightChild = _InsertedNode;
			}

			ParentNode->Parent = _InsertedNode;
			AncestorNode->Parent = _InsertedNode;

			_InsertedNode->Color = MyNode::NodeColor::Black;
			_InsertedNode->LeftChild->Color = MyNode::NodeColor::Red;
			_InsertedNode->RightChild->Color = MyNode::NodeColor::Red;
		}
		else if (ParentNode == AncestorNode->RightChild && _InsertedNode == ParentNode->LeftChild)
		{
			_InsertedNode->LeftChild = AncestorNode;
			_InsertedNode->RightChild = ParentNode;

			ParentNode->LeftChild = NilNode;
			AncestorNode->RightChild = NilNode;

			_InsertedNode->Parent = AncestorNode->Parent;

			if (AncestorNode == RootNode)
			{
				RootNode = _InsertedNode;
			}
			else if (AncestorNode->Parent->LeftChild == AncestorNode)
			{
				AncestorNode->Parent->LeftChild = _InsertedNode;
			}
			else if (AncestorNode->Parent->RightChild == AncestorNode)
			{
				AncestorNode->Parent->RightChild = _InsertedNode;
			}

			ParentNode->Parent = _InsertedNode;
			AncestorNode->Parent = _InsertedNode;

			_InsertedNode->Color = MyNode::NodeColor::Black;
			_InsertedNode->LeftChild->Color = MyNode::NodeColor::Red;
			_InsertedNode->RightChild->Color = MyNode::NodeColor::Red;
		}
		else if (ParentNode == AncestorNode->RightChild && _InsertedNode == ParentNode->RightChild)
		{
			if (ParentNode->LeftChild != NilNode)
			{
				AncestorNode->RightChild = ParentNode->LeftChild;
				ParentNode->LeftChild->Parent = AncestorNode;
			}

			ParentNode->LeftChild = AncestorNode;
			ParentNode->Parent = AncestorNode->Parent;

			if (AncestorNode == RootNode)
			{
				RootNode = ParentNode;
			}
			else if (AncestorNode->Parent->LeftChild == AncestorNode)
			{
				AncestorNode->Parent->LeftChild = ParentNode;
			}
			else if (AncestorNode->Parent->RightChild == AncestorNode)
			{
				AncestorNode->Parent->RightChild = ParentNode;
			}

			AncestorNode->Parent = ParentNode;
			AncestorNode->RightChild = NilNode;

			ParentNode->Color = MyNode::NodeColor::Black;
			ParentNode->LeftChild->Color = MyNode::NodeColor::Red;
			ParentNode->RightChild->Color = MyNode::NodeColor::Red;
		}

		return nullptr;
	}

public:

	MyNode* NilNode = nullptr;
	MyNode* RootNode = nullptr;
	MyNode* EndNode = nullptr;

	size_t MySize = 0;
};