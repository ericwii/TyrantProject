#pragma once
#include "Assert.h"

namespace CommonUtilities
{
	template <typename T, unsigned int Size>
	class StaticArray
	{
	public:
		StaticArray();
		StaticArray(const StaticArray& aStaticArray);

		~StaticArray();

		StaticArray& operator=(const StaticArray& aStaticArray);

		inline const T& operator[](const unsigned int& aIndex) const;
		inline T& operator[](const unsigned int& aIndex);


		// Utility functions
		inline void Insert(unsigned int aIndex, const T& aObject);
		inline void DeleteAll();

	private:
		T myList[Size];
	};
}




namespace CU = CommonUtilities;


template <typename T, unsigned int Size>
CU::StaticArray<T, Size>::StaticArray()
{
};

template <typename T, unsigned int Size>
CU::StaticArray<T, Size>::StaticArray(const StaticArray& aStaticArray)
{
	for (unsigned int i = 0; i < Size; ++i)
	{
		myList[i] = aStaticArray.myList[i];
	}
};

template <typename T, unsigned int Size>
CU::StaticArray<T, Size>::~StaticArray()
{
};



template <typename T, unsigned int Size>
CU::StaticArray<T, Size>& CU::StaticArray<T, Size>::operator=(const StaticArray& aStaticArray)
{
	for (unsigned int i = 0; i < Size; ++i)
	{
		myList[i] = aStaticArray.myList[i];
	}

	return (*this);
};

template <typename T, unsigned int Size>
inline T& CU::StaticArray<T, Size>::operator[](const unsigned int& aIndex)
{
	DEBUG_ASSERT(aIndex < Size, "Index is out of bounds");

	return myList[aIndex];
};

template <typename T, unsigned int Size>
inline const T& CU::StaticArray<T, Size>::operator[](const unsigned int& aIndex) const
{
	DEBUG_ASSERT(aIndex < Size, "Index is out of bounds");

	return myList[aIndex];
};



template <typename T, unsigned int Size>
inline void CU::StaticArray<T, Size>::Insert(unsigned int aIndex, const T& aObject)
{
	DEBUG_ASSERT(aIndex < Size, "Index is out of bounds");

	for (unsigned int i = Size - 2; i > aIndex; --i)
	{
		myList[i + 1] = myList[i];
	}
	myList[aIndex] = aObject;
};

template <typename T, unsigned int Size>
inline void CU::StaticArray<T, Size>::DeleteAll()
{
	for (int i = Size - 1; i >= 0; --i)
	{
		delete myList[i];
		myList[i] = nullptr;
	}
};