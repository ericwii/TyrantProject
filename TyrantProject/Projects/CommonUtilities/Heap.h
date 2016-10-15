#pragma once
#include "GrowingArray.h"
#include <iostream>

namespace CommonUtilities
{
	template<typename TYPE, typename COMPARER>
	class Heap
	{
	public:
		Heap() = default;
		Heap(const CommonUtilities::GrowingArray<TYPE,int> anArray);
		~Heap() = default;

		void Enqueue(const TYPE& someData);
		TYPE Dequeue();

		bool IsEmpty() const;
		void Print();

	private:
		GrowingArray<TYPE,int> myArray;
		COMPARER myComparer;

		void Swap(unsigned short aFirstIndex, unsigned short aSecondIndex);
		void MoveDown(unsigned short first, unsigned short last);
		void ArrangeArrayAsHeap();
	};

	template<typename TYPE, typename COMPARER>
	Heap<TYPE, COMPARER>::Heap(const CommonUtilities::GrowingArray<TYPE, int> anArray)
	{
		myArray = anArray;
		ArrangeArrayAsHeap();
	}

	template<typename TYPE, typename COMPARER>
	void Heap<TYPE, COMPARER>::Enqueue(const TYPE& someData)
	{	
		myArray.Add(someData);

		int currentIndex = myArray.Size() - 1;
		while (currentIndex > 0 && myComparer(myArray[currentIndex],myArray[(currentIndex - 1) / 2]) == true)
		{
			Swap((currentIndex - 1) / 2, currentIndex);
			currentIndex = (currentIndex - 1) / 2;
		}
	}

	template<typename TYPE, typename COMPARER>
	TYPE Heap<TYPE, COMPARER>::Dequeue()
	{
		assert(myArray.Size() != 0 && "Heap is empty, cannot dequeue");
		TYPE copy = myArray[0];
		myArray.RemoveCyclicAtIndex(0);

		int currentIndex = 0;
		int leafLevel = myArray.Size() / 2 - 1;

		while (currentIndex <= leafLevel
			&& currentIndex * 2 + 1 < myArray.Size() && (myComparer(myArray[currentIndex * 2 + 1], myArray[currentIndex]) == true
			|| currentIndex * 2 + 2 < myArray.Size() && myComparer(myArray[currentIndex * 2 + 2], myArray[currentIndex]) == true))
		{
			if (currentIndex * 2 + 2 < myArray.Size())
			{
				if (myComparer(myArray[currentIndex * 2 + 1], myArray[currentIndex * 2 + 2]) == true)
				{
					Swap(currentIndex, currentIndex * 2 + 1);
					currentIndex = currentIndex * 2 + 1;
				}
				else
				{
					Swap(currentIndex, currentIndex * 2 + 2);
					currentIndex = currentIndex * 2 + 2;
				}
			}
			else if (currentIndex * 2 + 1 < myArray.Size())
			{
				Swap(currentIndex, currentIndex * 2 + 1);
				currentIndex = currentIndex * 2 + 1;
			}
		}
		return copy;
	}

	template<typename TYPE, typename COMPARER>
	bool Heap<TYPE, COMPARER>::IsEmpty() const
	{
		return myArray.Size() == 0;
	}

	template<typename TYPE, typename COMPARER>
	void Heap<TYPE, COMPARER>::Print()
	{
		int currentRowIndex = 0;
		int currentRowLength = 1;

		for (int i = 0; i < myArray.Size(); ++i)
		{
			std::cout << myArray[i] << "  ";

			++currentRowIndex;

			if (currentRowIndex >= currentRowLength)
			{
				std::cout << "\n";
				currentRowIndex = 0;
				currentRowLength *= 2;
			}
		}
	}



	//Private methods

	template<typename TYPE, typename COMPARER>
	void Heap<TYPE, COMPARER>::Swap(unsigned short aFirstIndex, unsigned short aSecondIndex)
	{
		TYPE firstElementCopy = myArray[aFirstIndex];
		myArray[aFirstIndex] = myArray[aSecondIndex];
		myArray[aSecondIndex] = firstElementCopy;
	}

	template<typename TYPE, typename COMPARER>
	void Heap<TYPE, COMPARER>::MoveDown(unsigned short first, unsigned short last)
	{
		int largest = 2 * first + 1;

		while (largest <= last)
		{
			if (largest < last && myComparer(myArray[largest + 1], myArray[largest]) == true)
			{
				++largest;
			}

			if (myComparer(myArray[largest],myArray[first]) == true)
			{
				Swap(first, largest);
				first = largest;
				largest = 2 * first + 1;
			}
			else largest = last + 1;
		}
	}

	template<typename TYPE, typename COMPARER>
	void Heap<TYPE, COMPARER>::ArrangeArrayAsHeap()
	{
		int currentIndex = 0;
		int lastNoneLeaf = myArray.Size() / 2 - 1;

		for (int i = lastNoneLeaf; i >= 0; --i)
		{
			MoveDown(i, myArray.Size() - 1);
		}
	}
}