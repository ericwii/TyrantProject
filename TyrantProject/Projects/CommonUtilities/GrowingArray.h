#pragma once
#include "Assert.h"
#include <memory.h>


namespace CommonUtilities
{
	template<typename ObjectType>
	class GrowingArray
	{
	public:
		GrowingArray(); 
		GrowingArray(int aNrOfRecommendedItems, bool aUseMemoryCopying = false); 
		GrowingArray(const GrowingArray& aGrowingArray); 
		~GrowingArray(); 

		GrowingArray& operator=(const GrowingArray& aGrowingArray); 
		GrowingArray& operator+=(const GrowingArray& aGrowingArray); 

		inline void Allocate(int aNrOfRecommendedItems); 
		inline void ReAllocate(int aNrOfRecommendedItems); 

		inline ObjectType& operator[](const int aIndex);
		inline const ObjectType& operator[](const int aIndex) const; 

		inline void Add(const ObjectType& aObject); 
		inline void AddAtIndex(int aIndex, const ObjectType& aObject); 

		inline void DeleteCyclic(const ObjectType& aObject); 
		inline void DeleteCyclicAtIndex(const int anIndex); 
		inline void DeleteNonCyclic(const ObjectType& aObject);
		inline void DeleteNonCyclicAtIndex(const int anIndex);
		   
		inline void RemoveLast();
		inline void RemoveCyclic(const ObjectType& aObject); 
		inline void RemoveCyclicAtIndex(const int anIndex);
		inline void RemoveNonCyclic(const ObjectType& aObject);
		inline void RemoveNonCyclicAtIndex(const int anIndex);

		inline int FindIndex(const ObjectType& aObject);

		inline ObjectType& GetLast(); 
		inline const ObjectType& GetLast() const; 

		static const int FoundNone = -1;

		inline void RemoveAll();
		inline void DeleteAll(); 

		void OptimizeSize();
		inline void Reserve(const int aSize); 
		inline bool IsAllocated() const;
		__forceinline int Size() const; 

	private:
		inline void Resize(int aNewSize);

		bool myUseMemoryCopying;
		int myMaxSize;
		int myCurrentSize;
		ObjectType* myListPointer;
	};
}

namespace CU = CommonUtilities;



//Contructors\Destructor

template<typename ObjectType>
CU::GrowingArray<ObjectType>::GrowingArray()
{
	myUseMemoryCopying = false;
	myMaxSize = 0;
	myCurrentSize = 0;
	myListPointer = nullptr;
}

template<typename ObjectType>
CU::GrowingArray<ObjectType>::GrowingArray(int aNrOfRecommmendedItems, bool aUseMemoryCopying = true)
{
	DEBUG_ASSERT(aNrOfRecommmendedItems >= 1, "The number of recommended items cannot be less than 1");

	myUseMemoryCopying = aUseMemoryCopying;
	myMaxSize = aNrOfRecommmendedItems;
	myCurrentSize = 0;
	myListPointer = new ObjectType[aNrOfRecommmendedItems];
}

template<typename ObjectType>
CU::GrowingArray<ObjectType>::GrowingArray(const GrowingArray& aGrowingArray)
{
	DEBUG_ASSERT(aGrowingArray.myMaxSize > 0, "Cannot copy an array that has not allocated any memory");

	myUseMemoryCopying = aGrowingArray.myUseMemoryCopying;
	myMaxSize = aGrowingArray.myMaxSize;
	myListPointer = new ObjectType[aGrowingArray.myMaxSize];

	if (myUseMemoryCopying == false)
	{
		for (int i = 0; i < aGrowingArray.myCurrentSize; ++i)
		{
			myListPointer[i] = aGrowingArray.myListPointer[i];
		}
	}
	else
	{
		memcpy(myListPointer, aGrowingArray.myListPointer, sizeof(ObjectType) * aGrowingArray.myMaxSize);
	}

	myCurrentSize = aGrowingArray.myCurrentSize;
}

template<typename ObjectType>
CU::GrowingArray<ObjectType>::~GrowingArray()
{
	delete[] myListPointer;
	myCurrentSize = 0;
	myMaxSize = 0;
	myUseMemoryCopying = false;
}


//Allocation

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::Allocate(int aNrOfRecommendedItems)
{
	DEBUG_ASSERT(myMaxSize == 0, "Array is already allocated");
	DEBUG_ASSERT(aNrOfRecommendedItems >= 1, "The number of recommended items cannot be less than 1");

	myListPointer = new ObjectType[aNrOfRecommendedItems];
	myMaxSize = aNrOfRecommendedItems;
	myCurrentSize = 0;
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::ReAllocate(int aNrOfRecommendedItems)
{
	DEBUG_ASSERT(aNrOfRecommendedItems >= 1, "The number of recommended items cannot be less than 1");

	delete[] myListPointer;

	myListPointer = new ObjectType[aNrOfRecommendedItems];
	myMaxSize = aNrOfRecommendedItems;
	myCurrentSize = 0;
}


//Operators

template<typename ObjectType>
CU::GrowingArray<ObjectType>& CU::GrowingArray<ObjectType>::operator=(const GrowingArray& aGrowingArray)
{
	//DEBUG_ASSERT(aGrowingArray.myMaxSize > 0, "Operator '=' cannot copy an unallocated array");

	myUseMemoryCopying = aGrowingArray.myUseMemoryCopying;
	if (aGrowingArray.myMaxSize > 0)
	{
		delete[] myListPointer;
		myMaxSize = aGrowingArray.myMaxSize;
		myListPointer = new ObjectType[aGrowingArray.myMaxSize];

		if (myUseMemoryCopying == false)
		{
			for (int i = 0; i < aGrowingArray.myCurrentSize; ++i)
			{
				myListPointer[i] = aGrowingArray.myListPointer[i];
			}
		}
		else
		{
			memcpy(myListPointer, aGrowingArray.myListPointer, sizeof(ObjectType) * aGrowingArray.myMaxSize);
		}
		myCurrentSize = aGrowingArray.myCurrentSize;
	}

	return (*this);
}

template<typename ObjectType>
CU::GrowingArray<ObjectType>& CU::GrowingArray<ObjectType>::operator+=(const GrowingArray& aGrowingArray)
{
	DEBUG_ASSERT(myMaxSize > 0, "Cannot add items to an unallocated array");

	if (myCurrentSize + aGrowingArray.myCurrentSize > myMaxSize)
	{
		Resize(myMaxSize + aGrowingArray.myCurrentSize); 
	}

	if (myUseMemoryCopying == false)
	{
		for (int i = 0; i < aGrowingArray.myCurrentSize; ++i)
		{
			myListPointer[myCurrentSize + i] = aGrowingArray.myListPointer[i];
		}
	}
	else
	{
		memcpy(myListPointer + myCurrentSize, aGrowingArray.myListPointer, sizeof(ObjectType) * aGrowingArray.myCurrentSize);
	}

	myCurrentSize += aGrowingArray.myCurrentSize;
	return (*this);
}

template<typename ObjectType>
inline ObjectType& CU::GrowingArray<ObjectType>::operator[](const int aIndex)
{
	DEBUG_ASSERT(myMaxSize > 0, "operator '[]' cannot get an item from an unallocated Array");
	DEBUG_ASSERT(aIndex >= 0 && aIndex < myCurrentSize, "Index is out of range");

	return myListPointer[aIndex];
}

template<typename ObjectType>
inline const ObjectType& CU::GrowingArray<ObjectType>::operator[](const int aIndex) const
{
	DEBUG_ASSERT(myMaxSize > 0, "operator '[]' cannot get an item from an unallocated Array");
	DEBUG_ASSERT(aIndex >= 0 && aIndex < myCurrentSize, "Index is out of range");

	return myListPointer[aIndex];
}


//Resize/Reserve

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::Resize(int aNewSize)
{
	DEBUG_ASSERT(myMaxSize > 0, "Cannot Resize an unallocated array");
	DEBUG_ASSERT(aNewSize > 0, "The new size cannot be less than 1");

	ObjectType* aNewListPointer = new ObjectType[aNewSize];

	if (myUseMemoryCopying == false)
	{
		for (int i = 0; i < aNewSize; ++i)
		{
			if (i < myCurrentSize)
			{
				aNewListPointer[i] = myListPointer[i];
			}
			else
			{
				break;
			}
		}
	}
	else
	{
		memcpy(aNewListPointer, myListPointer, sizeof(ObjectType) * myCurrentSize);
	}

	delete[] myListPointer;

	myListPointer = aNewListPointer;
	myMaxSize = aNewSize;
	if (aNewSize < myCurrentSize)
	{
		myCurrentSize = aNewSize;
	}
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::Reserve(const int aSize)
{
	DEBUG_ASSERT(aSize > 0, "Cannot reserve memory for less than 1 object");
	
	Resize(myMaxSize + aSize);
}


//Utility functions

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::Add(const ObjectType& aObject)
{
	DEBUG_ASSERT(myMaxSize > 0, "Array is not initialized");

	if (myCurrentSize < myMaxSize)
	{
		myListPointer[myCurrentSize] = aObject;
	}
	else
	{
		Resize((myMaxSize * 2));
		myListPointer[myCurrentSize] = aObject;
	}
	++myCurrentSize;
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::AddAtIndex(int aIndex, const ObjectType& aObject)
{
	DEBUG_ASSERT(myMaxSize > 0, "Array is not initialized");
	DEBUG_ASSERT(aIndex >= 0 && aIndex <= myCurrentSize, "Index is out of range");

	if (myCurrentSize == myMaxSize)
	{
		Resize((myMaxSize * 2));
	}

	for (int i = myCurrentSize; i > aIndex; --i)
	{
		myListPointer[i] = myListPointer[i - 1];
	}

	myListPointer[aIndex] = aObject;
	++myCurrentSize;
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::DeleteCyclic(const ObjectType& aObject)
{
	DEBUG_ASSERT(myMaxSize > 0, "Array is not initialized");

	for (int i = 0; i < myCurrentSize; ++i)
	{
		if (myListPointer[i] == aObject)
		{
			delete myListPointer[i];
			myListPointer[i] = myListPointer[myCurrentSize - 1];
			--myCurrentSize;
			myListPointer[myCurrentSize] = nullptr;
			return;
		}
	}
	DEBUG_ASSERT(myMaxSize < myCurrentSize, "Object to delete was not found");
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::DeleteCyclicAtIndex(const int anIndex)
{
	DEBUG_ASSERT(myMaxSize > 0, "Array is not initialized");
	DEBUG_ASSERT(anIndex >= 0 && anIndex < myCurrentSize, "Index is out of range");

	delete myListPointer[anIndex];
	myListPointer[anIndex] = myListPointer[myCurrentSize - 1];
	--myCurrentSize;
	myListPointer[myCurrentSize] = nullptr;
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::DeleteNonCyclic(const ObjectType& aObject)
{
	DEBUG_ASSERT(myMaxSize > 0, "Array is not initialized");

	int objectIndex = -1;

	for (int i = 0; i < myCurrentSize; ++i)
	{
		if (myListPointer[i] == aObject)
		{
			objectIndex = i;
			break;
		}
	}

	DEBUG_ASSERT(objectIndex != -1, "Object to remove was not found");

	delete myListPointer[objectIndex];

	for (int i = 0; i < myCurrentSize - objectIndex - 1; ++i)
	{
		myListPointer[objectIndex + i] = myListPointer[objectIndex + i + 1];
	}
	--myCurrentSize;
	myListPointer[myCurrentSize] = nullptr;
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::DeleteNonCyclicAtIndex(const int anIndex)
{
	DEBUG_ASSERT(myMaxSize > 0, "Array is not initialized");
	DEBUG_ASSERT(anIndex >= 0 && anIndex < myCurrentSize, "Index is out of range");

	delete myListPointer[anIndex];

	for (int i = 0; i < myCurrentSize - anIndex - 1; ++i)
	{
		myListPointer[anIndex + i] = myListPointer[anIndex + i + 1];
	}
	--myCurrentSize;
	myListPointer[myCurrentSize] = nullptr;
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::RemoveLast()
{
	DEBUG_ASSERT(myMaxSize > 0, "Array is not initialized");
	DEBUG_ASSERT(myCurrentSize > 0, "No items to remove");
	--myCurrentSize;
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::RemoveCyclic(const ObjectType& aObject)
{
	DEBUG_ASSERT(myMaxSize > 0, "Array is not initialized");

	for (int i = 0; i < myCurrentSize; ++i)
	{
		if (myListPointer[i] == aObject)
		{
			myListPointer[i] = myListPointer[myCurrentSize - 1];
			--myCurrentSize;
			myListPointer[myCurrentSize] = 0;
			return;
		}
	}

	DEBUG_ASSERT(myMaxSize < myCurrentSize, "Object to remove was not found");
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::RemoveCyclicAtIndex(const int anIndex)
{
	DEBUG_ASSERT(myMaxSize > 0, "Array is not initialized");
	DEBUG_ASSERT(anIndex >= 0 && anIndex < myCurrentSize, "Index is out of range");

	myListPointer[anIndex] = myListPointer[myCurrentSize - 1];
	--myCurrentSize;
	//myListPointer[myCurrentSize] = 0;
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::RemoveNonCyclic(const ObjectType& aObject)
{
	DEBUG_ASSERT(myMaxSize > 0, "Array is not initialized");

	int objectIndex = -1;

	for (int i = 0; i < myCurrentSize; ++i)
	{
		if (myListPointer[i] == aObject)
		{
			objectIndex = i;
			break;
		}
	}

	DEBUG_ASSERT(objectIndex != -1, "Object to remove was not found");


	for (int i = 0; i < myCurrentSize - objectIndex - 1; ++i)
	{
		myListPointer[objectIndex + i] = myListPointer[objectIndex + i + 1];
	}
	--myCurrentSize;
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::RemoveNonCyclicAtIndex(const int anIndex)
{
	DEBUG_ASSERT(myMaxSize > 0, "Array is not initialized");
	DEBUG_ASSERT(anIndex >= 0 && anIndex < myCurrentSize, "Index is out of range");

	for (int i = 0; i < myCurrentSize - anIndex - 1; ++i)
	{
		myListPointer[anIndex + i] = myListPointer[anIndex + i + 1];
	}
	--myCurrentSize;
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::RemoveAll()
{
	myCurrentSize = 0;
}

template<typename ObjectType>
inline void CU::GrowingArray<ObjectType>::DeleteAll()
{
	for (int i = 0; i < myCurrentSize; ++i)
	{
		delete myListPointer[i];
		i = i;
	}
	myCurrentSize = 0;
}

template<typename ObjectType>
void CU::GrowingArray<ObjectType>::OptimizeSize()
{
	DEBUG_ASSERT(myMaxSize > 0,"Array is not initialized");

	Resize(myCurrentSize);
}

template<typename ObjectType>
inline int CU::GrowingArray<ObjectType>::FindIndex(const ObjectType& aObject)
{
	for (int i = 0; i < myCurrentSize; ++i)
	{
		if (myListPointer[i] == aObject)
		{
			return i;
		}
	}

	return FoundNone;
}

template<typename ObjectType>
inline ObjectType& CU::GrowingArray<ObjectType>::GetLast()
{
	return myListPointer[myCurrentSize - 1];
}

template<typename ObjectType>
inline const ObjectType& CU::GrowingArray<ObjectType>::GetLast() const
{
	return myListPointer[myCurrentSize - 1];
}

template<typename ObjectType>
inline bool CU::GrowingArray<ObjectType>::IsAllocated() const
{
	return myMaxSize > 0;
}

template<typename ObjectType>
__forceinline int CU::GrowingArray<ObjectType>::Size() const
{
	return myCurrentSize;
} 

