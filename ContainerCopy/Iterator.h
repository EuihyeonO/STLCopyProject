#pragma once
#include <concepts>

/************ Tag ************/
struct Bidirectional_Iterator_Tag {};
struct RandomAccess_Iterator_Tag : Bidirectional_Iterator_Tag {};

/************ Iterator ************/



/************ Node ************/


//
//template<typename DataType>
//class TreeNode
//{
//public:
//	enum NodeColor
//	{
//		None,
//		Red,
//		Black,
//	};
//
//	void operator=(const TreeNode<DataType>* _Node)
//	{
//	}
//
//	TreeNode<DataType>* operator++() override
//	{
//		return this;
//	}
//
//	TreeNode<DataType>* operator++(int) override
//	{
//		return nullptr;
//	}
//
//	TreeNode<DataType>* operator--() override
//	{
//		return nullptr;
//	}
//
//	TreeNode<DataType>* operator--(int) override
//	{
//		return nullptr;
//	}
//
//	const DataType& Get() override
//	{
//		return Data;
//	}
//
//	DataType Data;
//
//	NodeColor Color = NodeColor::None;
//
//	TreeNode<DataType>* Parent = nullptr;
//	TreeNode<DataType>* LeftChild = nullptr;
//	TreeNode<DataType>* RightChild = nullptr;
//};