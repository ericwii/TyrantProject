#pragma once

template<typename T>
struct Greater
{
	bool operator()(const T& aFirst, const T& aSecond);
};


template<typename T>
inline bool Greater<T>::operator()(const T& aFirst, const T& aSecond)
{
	return aFirst > aSecond;
}