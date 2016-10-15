#pragma once

template<typename T>
struct Lesser
{
	bool operator()(const T& aFirst,const T& aSecond);
};


template<typename T>
inline bool Lesser<T>::operator()(const T& aFirst, const T& aSecond)
{
	return aFirst < aSecond;
}