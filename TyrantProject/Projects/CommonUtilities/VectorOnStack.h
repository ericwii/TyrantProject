#pragma once

#include "Assert.h"
#include <memory.h>

namespace CommonUtilities
{
	template <typename T, const unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
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

template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::VectorOnStack()
{
	myCurrentSize = 0;
};

template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
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

template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::~VectorOnStack()
{
	myCurrentSize = 0;
};


//Operators

template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
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


template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
inline T& CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::operator[](const CountType & aIndex)
{
	DEBUG_ASSERT(aIndex < myCurrentSize, "Index is out of bounds");

	return myList[aIndex];
}


template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
inline const T& CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::operator[](const CountType & aIndex) const
{
	DEBUG_ASSERT(aIndex < myCurrentSize, "Index is out of bounds");

	return myList[aIndex];
}



//Utility methods

template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::Add(const T& aObject)
{
	DEBUG_ASSERT(myCurrentSize < MaxSize, "VectorOnStack list is already full");

	myList[myCurrentSize] = aObject;
	++myCurrentSize;
}


template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
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


template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
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


template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::DeleteCyclicAtIndex(CountType aItemNumber)
{
	DEBUG_ASSERT(aItemNumber < myCurrentSize, "Index is out of bounds");

	delete myList[aItemNumber];
	myList[aItemNumber] = myList[myCurrentSize - 1];
	--myCurrentSize;
}


template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
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


template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::RemoveCyclicAtIndex(CountType aItemNumber)
{
	DEBUG_ASSERT(aItemNumber < myCurrentSize, "Index is out of bounds");

	myList[aItemNumber] = myList[myCurrentSize - 1];
	--myCurrentSize;
}


template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::Clear()
{
	myCurrentSize = 0;
}


template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
inline void CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::DeleteAll()
{
	for (int i = myCurrentSize - 1; i >= 0; --i)
	{
		delete myList[i];
	}
	myCurrentSize = 0;
}


template <typename T, unsigned int MaxSize, typename CountType = unsigned short, bool UseSafeModeFlag = true>
inline CountType CU::VectorOnStack<T, MaxSize, CountType, UseSafeModeFlag>::Size() const
{
	return myCurrentSize;
}