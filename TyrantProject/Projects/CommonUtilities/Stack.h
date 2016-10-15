#pragma once
#include "GrowingArray.h"

template<typename T>
class Stack
{
public:
	Stack();
	~Stack();

	T Pop();
	T Top();
	int Size();
	void Push(const T& aValue);

private:
	CommonUtilities::GrowingArray<T, int> myList;
};


template<typename T>
Stack<T>::Stack()
{
	myList.Init(2);
}

template<typename T>
Stack<T>::~Stack()
{
}


template<typename T>
T Stack<T>::Pop()
{
	assert(myList.Size() > 0 && "Cannot pop an empty stack");
	T dataToReturn = myList[myList.Size() - 1];
	myList.RemoveCyclicAtIndex(myList.Size() - 1);

	return dataToReturn;
}

template<typename T>
T Stack<T>::Top()
{
	assert(myList.Size() > 0 && "Cannot return top of an empty stack");
	return myList[myList.Size() - 1];
}

template<typename T>
int Stack<T>::Size()
{
	return myList.Size();
}

template<typename T>
void Stack<T>::Push(const T& aValue)
{
	myList.Add(aValue);
}