#pragma once

#include "Assert.h"
#include <memory.h>

#define VectorOnStackTemplate template <typename T, int MaxSize, typename CountType, bool UseSafeModeFlag>
#define VectorOnStackTemplateDec template <typename T, int MaxSize, typename CountType = int, bool UseSafeModeFlag = true>

namespace CommonUtilities
{
	VectorOnStackTemplateDec
	class VectorOnStack
	{
	public:
		VectorOnStack();
		VectorOnStack(const VectorOnStack& aVectorOnStack);

		~VectorOnStack();

		VectorOnStack & operator=(const VectorOnStack & aVectorOnStack);

		inline const T& operator[](const CountType & aIndex) const;
		inline T& operator[](const CountType & aIndex);

		inline void Add(const T& aObject);
		inline void Insert(CountType aIndex, T& aObject);
		inline void DeleteCyclic(T& aObject);
		inline void DeleteCyclicAtIndex(CountType aItemNumber);
		inline void RemoveCyclic(const T& aObject);
		inline void RemoveCyclicAtIndex(CountType aItemNumber);
		inline void RemoveNonCyclic(const T& aObject);
		inline void RemoveNonCyclicAtIndex(CountType aItemNumber);
		inline T& GetLast();

		inline bool IsFull() const;

		inline void Clear();
		inline void DeleteAll();

		inline CountType Size() const;

	private:
		T myList[MaxSize];
		CountType myCurrentSize;
	};
}


namespace CU = CommonUtilities;

//Constructors\Destructor

VectorOnStackTemplate
CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::VectorOnStack()
{
	myCurrentSize = 0;
};

VectorOnStackTemplate
CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::VectorOnStack(const VectorOnStack& aVectorOnStack)
{
	if (UseSafeModeFlag == true)
	{
		for (int i = 0; i < aVectorOnStack.myCurrentSize; i++)
		{
			myList[i] = aVectorOnStack.myList[i];
		}
	}
	else
	{
		memcpy(myList, aVectorOnStack.myList, sizeof(T) * aVectorOnStack.myCurrentSize);
	}
	myCurrentSize = aVectorOnStack.myCurrentSize;
};

VectorOnStackTemplate
CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::~VectorOnStack()
{
	myCurrentSize = 0;
};


//Operators

VectorOnStackTemplate
CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>&
CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::operator=(const VectorOnStack& aVectorOnStack)
{
	for (int i = 0; i < aVectorOnStack.myCurrentSize; i++)
	{
		myList[i] = aVectorOnStack.myList[i];
	}

	myCurrentSize = aVectorOnStack.myCurrentSize;

	return (*this);
};


VectorOnStackTemplate
inline T& CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::operator[](const CountType & aIndex)
{
	DEBUG_ASSERT(aIndex < myCurrentSize, "Index is out of bounds");

	return myList[aIndex];
}


VectorOnStackTemplate
inline const T& CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::operator[](const CountType & aIndex) const
{
	DEBUG_ASSERT(aIndex < myCurrentSize, "Index is out of bounds");

	return myList[aIndex];
}



//Utility methods

VectorOnStackTemplate
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::Add(const T& aObject)
{
	DEBUG_ASSERT(myCurrentSize < MaxSize, "VectorOnStack list is already full");

	myList[myCurrentSize] = aObject;
	++myCurrentSize;
}


VectorOnStackTemplate
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::Insert(CountType aIndex, T& aObject)
{
	DEBUG_ASSERT(aIndex < myCurrentSize, "Index is out of bounds");

	if (myCurrentSize >= MaxSize)
	{
		--myCurrentSize;
	}

	for (unsigned int i = myCurrentSize; i > aIndex; --i)
	{
		myList[i] = myList[i - 1];
	}
	myList[aIndex] = aObject;
	++myCurrentSize;
}


VectorOnStackTemplate
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::DeleteCyclic(T& aObject)
{
	for (unsigned int i = 0; i < myCurrentSize; ++i)
	{
		if (myList[i] == aObject)
		{
			delete myList[i];
			myList[i] = myList[myCurrentSize - 1];
			--myCurrentSize;
		}
	}
}


VectorOnStackTemplate
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::DeleteCyclicAtIndex(CountType aItemNumber)
{
	DEBUG_ASSERT(aItemNumber < myCurrentSize, "Index is out of bounds");

	delete myList[aItemNumber];
	myList[aItemNumber] = myList[myCurrentSize - 1];
	--myCurrentSize;
}


VectorOnStackTemplate
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::RemoveCyclic(const T& aObject)
{
	for (unsigned int i = 0; i < myCurrentSize; ++i)
	{
		if (myList[i] == aObject)
		{
			myList[i] = myList[myCurrentSize - 1];
			--myCurrentSize;
		}
	}
}


VectorOnStackTemplate
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(CountType anIndex)
{
	DEBUG_ASSERT(aItemNumber < myCurrentSize, "Index is out of bounds");

	myList[anIndex] = myList[myCurrentSize - 1];
	--myCurrentSize;
}

VectorOnStackTemplate
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::RemoveNonCyclic(const T& aObject)
{
	int objectIndex = -1;

	for (int i = 0; i < myCurrentSize; ++i)
	{
		if (myList[i] == aObject)
		{
			objectIndex = i;
			break;
		}
	}

	DEBUG_ASSERT(objectIndex != -1, "Object to remove was not found");

	for (int i = 0; i < myCurrentSize - objectIndex - 1; ++i)
	{
		myList[objectIndex + i] = myList[objectIndex + i + 1];
	}
	--myCurrentSize;
}

VectorOnStackTemplate
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::RemoveNonCyclicAtIndex(CountType anIndex)
{
	DEBUG_ASSERT(aItemNumber < myCurrentSize, "Index is out of bounds");

	for (int i = 0; i < myCurrentSize - anIndex - 1; ++i)
	{
		myList[anIndex + i] = myListPointer[anIndex + i + 1];
	}
	--myCurrentSize;
}


VectorOnStackTemplate
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::Clear()
{
	myCurrentSize = 0;
}

VectorOnStackTemplate
inline bool CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::IsFull() const
{
	return myCurrentSize >= MaxSize;
}

VectorOnStackTemplate
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::DeleteAll()
{
	for (int i = myCurrentSize - 1; i >= 0; --i)
	{
		delete myList[i];
	}
	myCurrentSize = 0;
}


VectorOnStackTemplate
inline CountType CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::Size() const
{
	return myCurrentSize;
}

VectorOnStackTemplate
inline T& CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::GetLast()
{
	return myList[myCurrentSize - 1];
}