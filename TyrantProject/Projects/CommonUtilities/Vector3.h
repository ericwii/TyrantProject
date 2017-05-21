#pragma once

#include "Vector2.h"

template<typename TYPE>
class Vector3
{
public:
	Vector3(TYPE aX = 0, TYPE aY = 0, TYPE aZ = 0);
	Vector3(const Vector3<TYPE>& aVector3);
	Vector3(const Vector2<TYPE>& aVector2, TYPE aZ = 0);
	~Vector3();

	bool operator==(const Vector3<TYPE>& aVector3) const;

	const Vector3<TYPE> operator+(const Vector3<TYPE>& aVector3) const;
	const Vector3<TYPE> operator+(const Vector2<TYPE>& aVector2) const;
	const Vector3<TYPE> operator+(const TYPE& aScalar) const;
	Vector3<TYPE>& operator+=(const Vector3<TYPE>& aVector3);
	Vector3<TYPE>& operator+=(const Vector2<TYPE>& aVector2);
	Vector3<TYPE>& operator+=(const TYPE& aScalar);

	const Vector3<TYPE> operator-(const Vector3<TYPE>& aVector3) const;
	const Vector3<TYPE> operator-(const Vector2<TYPE>& aVector2) const;
	const Vector3<TYPE> operator-(const TYPE& aScalar) const;
	Vector3<TYPE>& operator-=(const Vector3<TYPE>& aVector3);
	Vector3<TYPE>& operator-=(const Vector2<TYPE>& aVector2);
	Vector3<TYPE>& operator-=(const TYPE& aScalar);

	const Vector3<TYPE> operator*(const Vector3<TYPE>& aVector3) const;
	const Vector3<TYPE> operator*(const Vector2<TYPE>& aVector2) const;
	const Vector3<TYPE> operator*(const TYPE& aScalar) const;
	Vector3<TYPE>& operator*=(const Vector3<TYPE>& aVector3);
	Vector3<TYPE>& operator*=(const Vector2<TYPE>& aVector2);
	Vector3<TYPE>& operator*=(const TYPE& aScalar);

	const Vector3<TYPE> operator/(const Vector3<TYPE>& aVector3) const;
	const Vector3<TYPE> operator/(const Vector2<TYPE>& aVector2) const;
	const Vector3<TYPE> operator/(const TYPE& aScalar) const;
	Vector3<TYPE>& operator/=(const Vector3<TYPE>& aVector3);
	Vector3<TYPE>& operator/=(const Vector2<TYPE>& aVector2);
	Vector3<TYPE>& operator/=(const TYPE& aScalar);


	template<typename T>
	operator Vector3<T>() const;
	template<typename T>
	operator Vector2<T>() const;
	
	Vector2<TYPE> AsVector2() const;

	void Set(TYPE aX, TYPE aY, TYPE aZ);
	void Set(const Vector3<TYPE> aVector3);
	void Set(const Vector2<TYPE> aVector2);
	const TYPE Length() const;
	const TYPE Length2() const;
	void Normalize();
	void Inverse();
	const Vector3<TYPE> GetInversed() const;
	const Vector3<TYPE> GetNormalized() const;
	const TYPE Dot(Vector3<TYPE> aVector3) const;
	const Vector3<TYPE> Cross(Vector3<TYPE>& aVector3) const;

	static const Vector3<TYPE> Lerp(const Vector3<TYPE>& aVector3, const Vector2<TYPE>& aSecondVector3, TYPE aLerpVal);

	union
	{
		struct { TYPE x, y, z; };
		TYPE array[3];
	};
};




/* Constructors/Destructor */

template<typename TYPE>
Vector3<TYPE>::Vector3(TYPE aX = 0, TYPE aY = 0, TYPE aZ = 0)
{
	x = aX;
	y = aY;
	z = aZ;
}

template<typename TYPE>
Vector3<TYPE>::Vector3(const Vector3<TYPE>& aVector3)
{
	x = aVector3.x;
	y = aVector3.y;
	z = aVector3.z;
}

template<typename TYPE>
Vector3<TYPE>::Vector3(const Vector2<TYPE>& aVector2, TYPE aZ = 0)
{
	x = aVector2.x;
	y = aVector2.y;
	z = aZ;
}

template<typename TYPE>
Vector3<TYPE>::~Vector3()
{

}



/* Operators */

//Operator ==

template<typename TYPE>
bool Vector3<TYPE>::operator==(const Vector3<TYPE>& aVector3) const
{
	if (aVector3.x == x && aVector3.y == y && aVector3.z == z)
	{
		return true;
	}

	return false;
}


//Operator +

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator+(const Vector3<TYPE>& aVector3) const
{
	Vector3<TYPE> aVector(x + aVector3.x, y + aVector3.y, z + aVector3.z);

	return aVector;
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator+(const Vector2<TYPE>& aVector2) const
{
	Vector3<TYPE> aVector(x + aVector2.x, y + aVector2.y, z);

	return aVector;
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator+(const TYPE& aScalar) const
{
	Vector3<TYPE> aVector(x + aScalar, y + aScalar, z + aScalar);

	return aVector;
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator+=(const Vector3<TYPE>& aVector3)
{
	x += aVector3.x;
	y += aVector3.y;
	z += aVector3.z;

	return (*this);
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator+=(const Vector2<TYPE>& aVector2)
{
	x += aVector2.x;
	y += aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator+=(const TYPE& aScalar)
{
	x += aScalar;
	y += aScalar;
	z += aScalar;

	return (*this);
}


//Operator -

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator-(const Vector3<TYPE>& aVector3) const
{
	Vector3<TYPE> aVector(x - aVector3.x, y - aVector3.y, z - aVector3.z);

	return aVector;
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator-(const Vector2<TYPE>& aVector2) const
{
	Vector3<TYPE> aVector(x - aVector2.x, y - aVector2.y, z);

	return aVector;
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator-(const TYPE& aScalar) const
{
	Vector3<TYPE> aVector(x - aScalar, y - aScalar, z - aScalar);

	return aVector;
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator-=(const Vector3<TYPE>& aVector3)
{
	x -= aVector3.x;
	y -= aVector3.y;
	z -= aVector3.z;

	return (*this);
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator-=(const Vector2<TYPE>& aVector2)
{
	x -= aVector2.x;
	y -= aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator-=(const TYPE& aScalar)
{
	x -= aScalar;
	y -= aScalar;
	z -= aScalar;

	return (*this);
}


//Operator *

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator*(const Vector3<TYPE>& aVector3) const
{
	Vector3<TYPE> aVector(x * aVector3.x, y * aVector3.y, z * aVector3.z);

	return aVector;
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator*(const Vector2<TYPE>& aVector2) const
{
	Vector3<TYPE> aVector(x * aVector2.x, y * aVector2.y, z);

	return aVector;
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator*(const TYPE& aScalar) const
{
	Vector3<TYPE> aVector(x * aScalar, y * aScalar, z * aScalar);

	return aVector;
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator*=(const Vector3<TYPE>& aVector3)
{
	x *= aVector3.x;
	y *= aVector3.y;
	z *= aVector3.z;

	return (*this);
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator*=(const Vector2<TYPE>& aVector2)
{
	x *= aVector2.x;
	y *= aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator*=(const TYPE& aScalar)
{
	x *= aScalar;
	y *= aScalar;
	z *= aScalar;

	return (*this);
}


//Operator /

template<typename TYPE>
template<typename T>
Vector3<TYPE>::operator Vector3<T>() const
{
	return Vector3<T>(static_cast<T>(x), static_cast<T>(y), static_cast<T>(z));
}

template<typename TYPE>
template<typename T>
Vector3<TYPE>::operator Vector2<T>() const
{
	return Vector2<T>(static_cast<T>(x), static_cast<T>(y));
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator/(const Vector3<TYPE>& aVector3) const
{
	Vector3<TYPE> aVector(x / aVector3.x, y / aVector3.y, z / aVector3.z);

	return aVector;
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator/(const Vector2<TYPE>& aVector2) const
{
	Vector3<TYPE> aVector(x / aVector2.x, y / aVector2.y, z);

	return aVector;
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::operator/(const TYPE& aScalar) const
{
	Vector3<TYPE> aVector(z / aScalar, y / aScalar, z / aScalar);

	return aVector;
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator/=(const Vector3<TYPE>& aVector3)
{
	x /= aVector3.x;
	y /= aVector3.y;
	z /= aVector3.z;

	return (*this);
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator/=(const Vector2<TYPE>& aVector2)
{
	x /= aVector2.x;
	y /= aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector3<TYPE>& Vector3<TYPE>::operator/=(const TYPE& aScalar)
{
	x /= aScalar;
	y /= aScalar;
	z /= aScalar;

	return (*this);
}



/* Utility methods */

template<typename TYPE>
Vector2<TYPE> Vector3<TYPE>::AsVector2() const
{
	return Vector2<TYPE>(x, y);
}

template<typename TYPE>
void Vector3<TYPE>::Set(TYPE aX, TYPE aY, TYPE aZ)
{
	x = aX;
	y = aY;
	z = aZ;
}

template<typename TYPE>
void Vector3<TYPE>::Set(const Vector3<TYPE> aVector3)
{
	x = aVector3.x;
	y = aVector3.y;
	z = aVector3.z;
}

template<typename TYPE>
void Vector3<TYPE>::Set(const Vector2<TYPE> aVector2)
{
	x = aVector2.x;
	y = aVector2.y;
}

template<typename TYPE>
const TYPE Vector3<TYPE>::Length() const
{
	TYPE lenght = static_cast<TYPE>(sqrt(x * x + y * y + z * z));

	return lenght;
}

template<typename TYPE>
const TYPE Vector3<TYPE>::Length2() const
{
	TYPE lenght2 = x * x + y * y + z * z;

	return lenght2;
}

template<typename TYPE>
void Vector3<TYPE>::Normalize()
{
	TYPE lenght = Length();
	x /= lenght;
	y /= lenght;
	z /= lenght;
}

template<typename TYPE>
void Vector3<TYPE>::Inverse()
{
	x = 1 / x;
	y = 1 / y;
	z = 1 / z;
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::GetInversed() const
{
	return Vector3<TYPE>(1 /x, 1 / y, 1 / z);
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::GetNormalized() const
{
	Vector3<TYPE> vector(x, y, z);

	vector.Normalize();

	return vector;
}

template<typename TYPE>
const TYPE Vector3<TYPE>::Dot(Vector3<TYPE> aVector3) const
{
	TYPE product = 0;

	product += (x * aVector3.x);
	product += (y * aVector3.y);
	product += (z * aVector3.z);

	return product;
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::Cross(Vector3<TYPE>& aVector3) const
{
	Vector3<TYPE> vector;

	vector.x = (y * aVector3.z - z * aVector3.y);
	vector.y = (z * aVector3.x - x * aVector3.z);
	vector.z = (x * aVector3.y - y * aVector3.x);

	return vector;
}

template<typename TYPE>
const Vector3<TYPE> Vector3<TYPE>::Lerp(const Vector3<TYPE>& aVector3, const Vector2<TYPE>& aSecondVector3, TYPE aLerpVal)
{
	Vector3<TYPE> lerpedVector;

	lerpedVector.x = aVector3.x + (aSecondVector3.x - aVector3.x) * aLerpVal;
	lerpedVector.y = aVector3.y + (aSecondVector3.y - aVector3.y) * aLerpVal;
	lerpedVector.z = aVector3.z + (aSecondVector3.z - aVector3.z) * aLerpVal;
	return lerpedVector;
}