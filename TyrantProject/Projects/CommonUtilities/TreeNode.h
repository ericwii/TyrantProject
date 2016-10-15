#pragma once
namespace CommonUtilities
{
	template<typename T>
	class BinaryTree;

	template<typename T>
	class TreeNode
	{
		template<typename T> friend class BinaryTree;
	public:
		TreeNode();
		TreeNode(const T someData);
		~TreeNode();


	private:
		TreeNode* myLeftNode;
		TreeNode* myRightNode;
		T myData;
	};
}

	template<typename T>
	CommonUtilities::TreeNode<T>::TreeNode()
	{
		myLeftNode = nullptr;
		myRightNode = nullptr;
	}

	template<typename T>
	CommonUtilities::TreeNode<T>::TreeNode(const T someData)
	{
		myData = someData;
		myLeftNode = nullptr;
		myRightNode = nullptr;
	}

	template<typename T>
	CommonUtilities::TreeNode<T>::~TreeNode()
	{
	}