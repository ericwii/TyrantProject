#include "DoubleLinkedListNode.h"
#include <assert.h>

namespace CommonUtilities
{
	template <typename T>
	class DoubleLinkedList
	{ 
	public:
		DoubleLinkedList();
		~DoubleLinkedList();

		DoubleLinkedListNode<T>* GetFirstNode() const;
		DoubleLinkedListNode<T>* GetLastNode() const;
		DoubleLinkedListNode<T>* Find(const T& aValue);

		void InsertNodeBeforeNode(DoubleLinkedListNode<T>* aNode, DoubleLinkedListNode<T>* aNodeToInsert);
		void InsertNodeAfterNode(DoubleLinkedListNode<T>* aNode, DoubleLinkedListNode<T>* aNodeToInsert);
		void InsertNodeSorted(DoubleLinkedListNode<T>*  aNodeToInsert);
		void InsertNodeSorted(const T& aValueToinsert);
		void DeleteNode(DoubleLinkedListNode<T>* aNodeToDelete);
		void DeleteNode(const T& aValueToDelete);

	private:
		DoubleLinkedListNode<T>* myFirstNode;
		DoubleLinkedListNode<T>* myLastNode;

		void DoubleLinkedList<T>::InsertNode(DoubleLinkedListNode<T>* aPlaceInList, DoubleLinkedListNode<T>* aNodeToInsert);
	};



	template <typename T>
	DoubleLinkedList<T>::DoubleLinkedList()
	{
		myFirstNode = nullptr;
		myLastNode = nullptr;
	}

	template <typename T>
	DoubleLinkedList<T>::~DoubleLinkedList()
	{
		DoubleLinkedListNode<T>* lastNode = myFirstNode;
		DoubleLinkedListNode<T>* nextNode = lastNode;

		while (nextNode != nullptr)
		{
			lastNode = nextNode;
			nextNode = nextNode->Next;
			delete lastNode;
		}
		myFirstNode = nullptr;
		myLastNode = nullptr;
	}



	template <typename T>
	DoubleLinkedListNode<T>* DoubleLinkedList<T>::GetFirstNode() const
	{
		return myFirstNode;
	}

	template <typename T>
	DoubleLinkedListNode<T>* DoubleLinkedList<T>::GetLastNode() const
	{
		return myLastNode;
	}

	template <typename T>
	DoubleLinkedListNode<T>* DoubleLinkedList<T>::Find(const T& aValue)
	{
		DoubleLinkedListNode<T>* currentNode = myFirstNode;

		while (currentNode != nullptr && currentNode->GetData() != aValue)
		{
			currentNode = currentNode->Next;
		}

		return currentNode;
	}



	template <typename T>
	void DoubleLinkedList<T>::InsertNodeBeforeNode(DoubleLinkedListNode<T>* aNode, DoubleLinkedListNode<T>* aNodeToInsert)
	{
		assert(myFirstNode != nullptr && "DoubleLinkedList does not have any nodes");

		DoubleLinkedListNode<T>* currentNode = myFirstNode;

		while (currentNode != nullptr && currentNode != aNode)
		{
			currentNode = currentNode->Next;
		}

		if (currentNode != nullptr)
		{
			DoubleLinkedListNode<T>* previousNode = currentNode->Previous;

			if (aNodeToInsert == previousNode || aNodeToInsert == currentNode)
			{
				aNodeToInsert = new DoubleLinkedListNode<T>(aNodeToInsert->GetData());
			}

			aNodeToInsert->Previous = previousNode;
			if (previousNode != nullptr)
			{
				previousNode->Next = aNodeToInsert;
			}
			else
			{
				myFirstNode = aNodeToInsert;
			}

			aNodeToInsert->Next = currentNode;
			currentNode->Previous = aNodeToInsert;
		}
	}

	template <typename T>
	void DoubleLinkedList<T>::InsertNodeAfterNode(DoubleLinkedListNode<T>* aNode, DoubleLinkedListNode<T>* aNodeToInsert)
	{
		assert(myFirstNode != nullptr && "DoubleLinkedList does not have any nodes");

		DoubleLinkedListNode<T>* currentNode = myFirstNode;

		while (currentNode != nullptr && currentNode != aNode)
		{
			currentNode = currentNode->Next;
		}

		if (currentNode != nullptr)
		{
			DoubleLinkedListNode<T>* nextNode = currentNode->Next;

			if (nextNode != nullptr)
			{
				aNodeToInsert->Next = nextNode;
				nextNode->Previous = aNodeToInsert;
			}
			else
			{
				myLastNode = aNodeToInsert;
			}

			aNodeToInsert->Previous = currentNode;
			currentNode->Next = aNodeToInsert;
		}
	}

	template <typename T>
	void DoubleLinkedList<T>::InsertNodeSorted(DoubleLinkedListNode<T>* aNodeToInsert)
	{
		if (myFirstNode != nullptr)
		{
			DoubleLinkedListNode<T>* currentNode = myFirstNode;

			T currentNodeValue = currentNode->GetData();
			T nodeToInsertValue = aNodeToInsert->GetData();
			while (currentNode != nullptr && currentNode->GetData() >= aNodeToInsert->GetData())
			{
				currentNode = currentNode->Next;
				if (currentNode != nullptr) currentNodeValue = currentNode->GetData();
			}

			if (currentNode != nullptr) //if aNodeToInsert->GetData > currentNode->GetData()
			{
				DoubleLinkedListNode<T>* previousNode = currentNode->Previous;

				currentNode->Previous = aNodeToInsert;

				if(previousNode != nullptr) previousNode->Next = aNodeToInsert;

				aNodeToInsert->Next = currentNode;
				aNodeToInsert->Previous = previousNode;

				if (aNodeToInsert->Previous == nullptr)
				{
					myFirstNode = aNodeToInsert;
				}
			}
			else
			{
				myLastNode->Next = aNodeToInsert;
				aNodeToInsert->Previous = myLastNode;
				myLastNode = aNodeToInsert;
			}
		}
		else
		{
			myFirstNode = aNodeToInsert;
			myLastNode = aNodeToInsert;
		}
	}

	template <typename T>
	void DoubleLinkedList<T>::InsertNodeSorted(const T& aValueToInsert)
	{
		DoubleLinkedListNode<T>* aNodeToInsert = new DoubleLinkedListNode<T>(aValueToInsert);
		InsertNodeSorted(aNodeToInsert);
	}

	template <typename T>
	void DoubleLinkedList<T>::DeleteNode(DoubleLinkedListNode<T>* aNodeToDelete)
	{
		DoubleLinkedListNode<T>* currentNode = myFirstNode;

		while (currentNode != nullptr && aNodeToDelete != currentNode)
		{
			currentNode = currentNode->Next;
		}

		if (currentNode != nullptr)
		{
			DoubleLinkedListNode<T>* previousNode = currentNode->Previous;
			DoubleLinkedListNode<T>* nextNode = currentNode->Next;

			if (previousNode != nullptr)
			{
				previousNode->Next = currentNode->Next;
			}
			if (nextNode != nullptr)
			{
				nextNode->Previous = currentNode->Previous;
			}
			if (currentNode == myLastNode)
			{
				myLastNode = currentNode->Previous;
			}
			if (currentNode == myFirstNode)
			{
				myFirstNode = myFirstNode->Next;
			}
		}
		delete currentNode;
	}

	template <typename T>
	void DoubleLinkedList<T>::DeleteNode(const T& aValueToDelete)
	{
		DoubleLinkedListNode<T>* aNodeToDelete = myFirstNode;

		while (aNodeToDelete != nullptr && aNodeToDelete->GetData() != aValueToDelete)
		{
			aNodeToDelete = aNodeToDelete->Next;
		}

		DeleteNode(aNodeToDelete);
	}



	//Private methods

	template <typename T>
	void DoubleLinkedList<T>::InsertNode(DoubleLinkedListNode<T>* aPlaceInList, DoubleLinkedListNode<T>* aNodeToInsert)
	{
		if (aPlaceInList != nullptr)
		{
			DoubleLinkedListNode<T>* previousNode = aPlaceInList->Previous;
			DoubleLinkedListNode<T>* nextNode = aPlaceInList->Next;

			if (previousNode != nullptr)
			{
				previousNode->Next = aNodeToInsert;
				aNodeToInsert->Previous = previousNode;
			}
			if (nextNode != nullptr)
			{
				nextNode->Previous = aNodeToInsert;
				aNodeToInsert->Next = nextNode;
			}
		}
	}
}



