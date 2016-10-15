#pragma once
#include <assert.h>
#include <iostream>
#include "TreeNode.h"

namespace CommonUtilities
{
	template<typename T>
	class BinaryTree
	{
	public:
		BinaryTree();
		~BinaryTree();

		TreeNode<T>* GetRootNode();
		TreeNode<T>* Find(T aValueToFind);

		void InsertNode(TreeNode<T>* aNodeToInsert);
		void InsertNode(T aValueToInsert);
		void DeleteNode(TreeNode<T>* aNodeToDelete);
		void DeleteNode(T aValueToDelete);

		void PostOrderTraverse();
		void InOrderTraverse();

	private:
		TreeNode<T>* myRootNode;

		TreeNode<T>* FindPlaceToInsertNode(TreeNode<T>* aCurrentNode, const T& aValue);
		TreeNode<T>* FindNodeParent(TreeNode<T>* aChildNode,TreeNode<T>* aCurrentNode);
		void PrintNode(TreeNode<T>* aNode);
		void TraverseNodeInOrder(TreeNode<T>* aCurrentNode);
		void TraverseNodePostOrder(TreeNode<T>* aCurrentNode);
		void DeleteNodeWith2Childs(TreeNode<T>* aNodeToDelete);
		void DeleteNodeWith1Child(TreeNode<T>* aNodeToDelete);
		void DeleteLeafNode(TreeNode<T>* aNodeToDelete);
	};
}

namespace CU = CommonUtilities;



//Constructor/Desctructor

template<typename T>
CU::BinaryTree<T>::BinaryTree()
{
	myRootNode = nullptr;
}

template<typename T>
CU::BinaryTree<T>::~BinaryTree()
{
}




//Public methods

template<typename T>
CU::TreeNode<T>* CU::BinaryTree<T>::GetRootNode()
{
	return myRootNode;
}

template<typename T>
CU::TreeNode<T>* CU::BinaryTree<T>::Find(T aValueToFind)
{
	if (myRootNode != nullptr)
	{
		CU::TreeNode<T>* currentNode = myRootNode;

		while (currentNode != nullptr)
		{
			if (aValueToFind < currentNode->myData)
			{
				currentNode = currentNode->myLeftNode;
			}
			else if (aValueToFind > currentNode->myData)
			{
				currentNode = currentNode->myRightNode;
			}
			else return currentNode;
		}
	}
	
	return nullptr;
}

template<typename T>
void CU::BinaryTree<T>::InsertNode(CU::TreeNode<T>* aNodeToInsert)
{
	assert(aNodeToInsert != nullptr && "The node to insert is nullptr");

	if (myRootNode != nullptr)
	{
		CU::TreeNode<T>* nodeParent = FindPlaceToInsertNode(myRootNode, aNodeToInsert->myData);

		if (nodeParent != nullptr)
		{
			if (aNodeToInsert->myData < nodeParent->myData)
			{
				nodeParent->myLeftNode = aNodeToInsert;
			}
			else
			{
				nodeParent->myRightNode = aNodeToInsert;
			}
		}
	}
	else
	{
		myRootNode = aNodeToInsert;
	}
}

template<typename T>
void CU::BinaryTree<T>::InsertNode(T aValueToInsert)
{
	CU::TreeNode<T>* treeNodeToAdd = new CU::TreeNode<T>(aValueToInsert);

	InsertNode(treeNodeToAdd);
}

template<typename T>
void CU::BinaryTree<T>::DeleteNode(TreeNode<T>* aNodeToDelete)
{
	DeleteNode(aNodeToDelete->myData);
}

template<typename T>
void CU::BinaryTree<T>::DeleteNode(T aValueToDelete)
{
	TreeNode<T>* nodeToDelete = Find(aValueToDelete);

	assert(nodeToDelete != nullptr && "Could not find node to delete");

	if (nodeToDelete->myLeftNode != nullptr && nodeToDelete->myRightNode != nullptr)
	{
		DeleteNodeWith2Childs(nodeToDelete);
	}
	else if (nodeToDelete->myLeftNode != nullptr || nodeToDelete->myRightNode != nullptr)
	{
		DeleteNodeWith1Child(nodeToDelete);
	}
	else
	{
		DeleteLeafNode(nodeToDelete);
	}
}

template<typename T>
void CU::BinaryTree<T>::InOrderTraverse()
{
	if (myRootNode != nullptr)
	{
		TraverseNodeInOrder(myRootNode);
	}
}

template<typename T>
void CU::BinaryTree<T>::PostOrderTraverse()
{
	if (myRootNode != nullptr)
	{
		TraverseNodePostOrder(myRootNode);
	}
}




//Private methods

template<typename T>
CU::TreeNode<T>* CU::BinaryTree<T>::FindPlaceToInsertNode(CU::TreeNode<T>* aCurrentNode, const T& aValue)
{
	assert(aCurrentNode != nullptr && "CurrentNode is nullptr");
	if (aValue < aCurrentNode->myData)
	{
		if (aCurrentNode->myLeftNode == nullptr)
		{
			return aCurrentNode;
		}
		else
		{
			return FindPlaceToInsertNode(aCurrentNode->myLeftNode,aValue);
		}
	}
	if (aValue > aCurrentNode->myData)
	{
		if (aCurrentNode->myRightNode == nullptr)
		{
			return aCurrentNode;
		}
		else
		{
			return FindPlaceToInsertNode(aCurrentNode->myRightNode, aValue);
		}
	}
	return nullptr;
}

template<typename T>
CU::TreeNode<T>* CU::BinaryTree<T>::FindNodeParent(TreeNode<T>* aChildNode, TreeNode<T>* aCurrentNode)
{
	TreeNode<T>* parentNode = nullptr;
	if (aCurrentNode->myLeftNode == aChildNode) return aCurrentNode;
	if (aCurrentNode->myRightNode == aChildNode) return aCurrentNode;

	if (aCurrentNode->myLeftNode != nullptr)
	{
		parentNode = FindNodeParent(aChildNode, aCurrentNode->myLeftNode);
	}
	if (parentNode == nullptr && aCurrentNode->myRightNode != nullptr)
	{
		parentNode = FindNodeParent(aChildNode, aCurrentNode->myRightNode);
	}
	return parentNode;
}

template<typename T>
void CU::BinaryTree<T>::PrintNode(TreeNode<T>* aNode)
{
	std::cout << aNode->myData << " , ";
}

template<typename T>
void CU::BinaryTree<T>::TraverseNodeInOrder(TreeNode<T>* aCurrentNode)
{
	assert(aCurrentNode != nullptr && "currentNode is nullptr");

	if (aCurrentNode->myLeftNode != nullptr)
	{
		TraverseNodeInOrder(aCurrentNode->myLeftNode);
	}

	PrintNode(aCurrentNode);

	if (aCurrentNode->myRightNode != nullptr)
	{
		TraverseNodeInOrder(aCurrentNode->myRightNode);
	}
}

template<typename T>
void CU::BinaryTree<T>::TraverseNodePostOrder(TreeNode<T>* aCurrentNode)
{
	assert(aCurrentNode != nullptr && "currentNode is nullptr");

	if (aCurrentNode->myLeftNode != nullptr)
	{
		TraverseNodePostOrder(aCurrentNode->myLeftNode);
	}
	if (aCurrentNode->myRightNode != nullptr)
	{
		TraverseNodePostOrder(aCurrentNode->myRightNode);
	}

	PrintNode(aCurrentNode);
}

template<typename T>
void CU::BinaryTree<T>::DeleteNodeWith2Childs(TreeNode<T>* aNodeToDelete)
{
	CU::TreeNode<T>* nodeToReplaceWith = aNodeToDelete->myLeftNode;

	while (nodeToReplaceWith->myRightNode != nullptr)
		nodeToReplaceWith = nodeToReplaceWith->myRightNode;

	aNodeToDelete->myData = nodeToReplaceWith->myData;

	if (nodeToReplaceWith->myLeftNode != nullptr)
	{
		DeleteNodeWith1Child(nodeToReplaceWith);
	}
	else DeleteLeafNode(nodeToReplaceWith);
}

template<typename T>
void CU::BinaryTree<T>::DeleteNodeWith1Child(TreeNode<T>* aNodeToDelete)
{
	CU::TreeNode<T>* parentNode = FindNodeParent(aNodeToDelete, myRootNode);

	if (parentNode != nullptr)
	{
		if (parentNode->myLeftNode == aNodeToDelete)
		{
			if (aNodeToDelete->myLeftNode != nullptr)
			{
				parentNode->myLeftNode = aNodeToDelete->myLeftNode;
			}
			else
			{
				parentNode->myLeftNode = aNodeToDelete->myRightNode;
			}
		}
		else if (parentNode->myRightNode == aNodeToDelete)
		{
			if (aNodeToDelete->myLeftNode != nullptr)
			{
				parentNode->myRightNode = aNodeToDelete->myLeftNode;
			}
			else
			{
				parentNode->myRightNode = aNodeToDelete->myRightNode;
			}
		}
	}
	delete aNodeToDelete;
}

template<typename T>
void CU::BinaryTree<T>::DeleteLeafNode(TreeNode<T>* aNodeToDelete)
{
	CU::TreeNode<T>* parentNode = FindNodeParent(aNodeToDelete, myRootNode);
	
	if (parentNode != nullptr)
	{
		if (parentNode->myLeftNode == aNodeToDelete)
		{
			parentNode->myLeftNode = nullptr;
		}
		else if (parentNode->myRightNode == aNodeToDelete)
		{
			parentNode->myRightNode = nullptr;
		}
	}

	if (aNodeToDelete == myRootNode)
	{
		myRootNode = nullptr;
	}
	delete aNodeToDelete;
}