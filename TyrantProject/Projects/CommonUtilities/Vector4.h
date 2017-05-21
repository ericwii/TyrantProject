#pragma once

#include "Vector3.h"

template<typename TYPE>
class Vector4
{
public:
	Vector4(TYPE aX = 0, TYPE aY = 0, TYPE aZ = 0, TYPE aW = 0);
	Vector4(const Vector4<TYPE>& aVector4);
	Vector4(const Vector3<TYPE>& aVector3, TYPE aW = 0);
	Vector4(const Vector2<TYPE>& aVector2, TYPE aZ = 0, TYPE aW = 0);
	~Vector4();

	bool operator==(const Vector4<TYPE>& aVector4) const;

	const Vector4<TYPE> operator+(const Vector4<TYPE>& aVector4) const;
	const Vector4<TYPE> operator+(const Vector3<TYPE>& aVector3) const;
	const Vector4<TYPE> operator+(const Vector2<TYPE>& aVector2) const;
	const Vector4<TYPE> operator+(const TYPE& aScalar) const;
	Vector4<TYPE>& operator+=(const Vector4<TYPE>& aVector4);
	Vector4<TYPE>& operator+=(const Vector3<TYPE>& aVector3);
	Vector4<TYPE>& operator+=(const Vector2<TYPE>& aVector2);
	Vector4<TYPE>& operator+=(const TYPE& aScalar);

	const Vector4<TYPE> operator-(const Vector4<TYPE>& aVector4) const;
	const Vector4<TYPE> operator-(const Vector3<TYPE>& aVector3) const;
	const Vector4<TYPE> operator-(const Vector2<TYPE>& aVector2) const;
	const Vector4<TYPE> operator-(const TYPE& aScalar) const;
	Vector4<TYPE>& operator-=(const Vector4<TYPE>& aVector4);
	Vector4<TYPE>& operator-=(const Vector3<TYPE>& aVector3);
	Vector4<TYPE>& operator-=(const Vector2<TYPE>& aVector2);
	Vector4<TYPE>& operator-=(const TYPE& aScalar);

	const Vector4<TYPE> operator*(const Vector4<TYPE>& aVector4) const;
	const Vector4<TYPE> operator*(const Vector3<TYPE>& aVector3) const;
	const Vector4<TYPE> operator*(const Vector2<TYPE>& aVector2) const;
	const Vector4<TYPE> operator*(const TYPE& aScalar) const;
	Vector4<TYPE>& operator*=(const Vector4<TYPE>& aVector4);
	Vector4<TYPE>& operator*=(const Vector3<TYPE>& aVector3);
	Vector4<TYPE>& operator*=(const Vector2<TYPE>& aVector2);
	Vector4<TYPE>& operator*=(const TYPE& aScalar);

	const Vector4<TYPE> operator/(const Vector4<TYPE>& aVector4) const;
	const Vector4<TYPE> operator/(const Vector3<TYPE>& aVector3) const;
	const Vector4<TYPE> operator/(const Vector2<TYPE>& aVector2) const;
	const Vector4<TYPE> operator/(const TYPE& aScalar) const;
	Vector4<TYPE>& operator/=(const Vector4<TYPE>& aVector4);
	Vector4<TYPE>& operator/=(const Vector3<TYPE>& aVector3);
	Vector4<TYPE>& operator/=(const Vector2<TYPE>& aVector2);
	Vector4<TYPE>& operator/=(const TYPE& aScalar);


	template<typename T>
	operator Vector4<T>() const;
	template<typename T>
	operator Vector3<T>() const;
	template<typename T>
	operator Vector2<T>() const;

	const Vector3<TYPE> AsVector3() const;
	const Vector2<TYPE> AsVector2() const;
	void Set(TYPE aX, TYPE aY = y, TYPE aZ = z, TYPE aW = w);
	void Set(const Vector4<TYPE> aVector4);
	void Set(const Vector3<TYPE> aVector3);
	void Set(const Vector2<TYPE> aVector2);
	const TYPE Dot(const Vector4<TYPE>& aVector4) const;
	const Vector4<TYPE> GetNormalized() const;
	const Vector4<TYPE> GetInversed() const;
	const TYPE Length() const;
	const TYPE Length2() const;
	void Normalize();
	void Inverse();

	static const Vector4<TYPE> Lerp(const Vector4<TYPE>& aVector4, const Vector4<TYPE>& aSecondVector4, TYPE aLerpVal);

	union
	{
		struct { TYPE x, y, z, w; };
		TYPE array[4];
	};
};



/* Constructors/Destructor */

template<typename TYPE>
Vector4<TYPE>::Vector4(TYPE aX = 0, TYPE aY = 0, TYPE aZ = 0, TYPE aW = 0)
{
	x = aX;
	y = aY;
	z = aZ;
	w = aW;
}

template<typename TYPE>
Vector4<TYPE>::Vector4(const Vector4<TYPE>& aVector4)
{
	x = aVector4.x;
	y = aVector4.y;
	z = aVector4.z;
	w = aVector4.w;
}

template<typename TYPE>
Vector4<TYPE>::Vector4(const Vector3<TYPE>& aVector3, TYPE aW = 0)
{
	x = aVector3.x;
	y = aVector3.y;
	z = aVector3.z;
	w = aW;
}

template<typename TYPE>
Vector4<TYPE>::Vector4(const Vector2<TYPE>& aVector2, TYPE aZ = 0, TYPE aW = 0)
{
	x = aVector2.x;
	y = aVector2.y;
	z = aZ;
	w = aW;
}

template<typename TYPE>
Vector4<TYPE>::~Vector4()
{

}


/* Operators */

//Operator ==

template<typename TYPE>
bool Vector4<TYPE>::operator==(const Vector4<TYPE>& aVector4) const
{
	if (x == aVector4.X && y == aVector4.Y && z == aVector4.Z && w == aVector4.W)
	{
		return true;
	}

	return false;
}


//Operator +

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator+(const Vector4<TYPE>& aVector4) const
{
	Vector4<TYPE> vector(x + aVector4.x, y + aVector4.y, z + aVector4.z, w + aVector4.w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator+(const Vector3<TYPE>& aVector3) const
{
	Vector4<TYPE> vector(x + aVector3.x, y + aVector3.y, z + aVector3.z, w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator+(const Vector2<TYPE>& aVector2) const
{
	Vector4<TYPE> vector(x + aVector2.x, y + aVector2.y, z, w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator+(const TYPE& aScalar) const
{
	Vector4<TYPE> vector(x + aScalar, y + aScalar, z + aScalar, w + aScalar);

	return vector;
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator+=(const Vector4<TYPE>& aVector4)
{
	x += aVector4.x;
	y += aVector4.y;
	z += aVector4.z;
	w += aVector4.w;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator+=(const Vector3<TYPE>& aVector3)
{
	x += aVector3.x;
	y += aVector3.y;
	z += aVector3.z;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator+=(const Vector2<TYPE>& aVector2)
{
	x += aVector2.x;
	y += aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator+=(const TYPE& aScalar)
{
	x += aScalar;
	y += aScalar;
	z += aScalar;
	w += aScalar;

	return (*this);
}


//Operator -

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator-(const Vector4<TYPE>& aVector4) const
{
	Vector4<TYPE> vector(x - aVector4.x, y - aVector4.y, z - aVector4.z, w - aVector4.w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator-(const Vector3<TYPE>& aVector3) const
{
	Vector4<TYPE> vector(x - aVector3.x, y - aVector3.y, z - aVector3.z, w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator-(const Vector2<TYPE>& aVector2) const
{
	Vector4<TYPE> vector(x - aVector2.x, y - aVector2.y, z, w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator-(const TYPE& aScalar) const
{
	Vector4<TYPE> vector(x - aScalar, y - aScalar, z - aScalar, w - aScalar);

	return vector;
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator-=(const Vector4<TYPE>& aVector4)
{
	x -= aVector4.x;
	y -= aVector4.y;
	z -= aVector4.z;
	w -= aVector4.w;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator-=(const Vector3<TYPE>& aVector3)
{
	x -= aVector3.x;
	y -= aVector3.y;
	z -= aVector3.z;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator-=(const Vector2<TYPE>& aVector2)
{
	x -= aVector2.x;
	y -= aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator-=(const TYPE& aScalar)
{
	x -= aScalar;
	y -= aScalar;
	z -= aScalar;
	w -= aScalar;

	return (*this);
}


//Operator *

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator*(const Vector4<TYPE>& aVector4) const
{
	Vector4<TYPE> vector(x * aVector4.x, y * aVector4.y, z * aVector4.z, w * aVector4.w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator*(const Vector3<TYPE>& aVector3) const
{
	Vector4<TYPE> vector(x * aVector3.x, y * aVector3.y, z * aVector3.z, w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator*(const Vector2<TYPE>& aVector2) const
{
	Vector4<TYPE> vector(x * aVector2.x, y * aVector2.y, z, w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator*(const TYPE& aScalar) const
{
	Vector4<TYPE> vector(x * aScalar, y * aScalar, z * aScalar, w * aScalar);

	return vector;
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator*=(const Vector4<TYPE>& aVector4)
{
	x *= aVector4.x;
	y *= aVector4.y;
	z *= aVector4.z;
	w *= aVector4.w;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator*=(const Vector3<TYPE>& aVector3)
{
	x *= aVector3.x;
	y *= aVector3.y;
	z *= aVector3.z;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator*=(const Vector2<TYPE>& aVector2)
{
	x *= aVector2.x;
	y *= aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator*=(const TYPE& aScalar)
{
	x *= aScalar;
	y *= aScalar;
	z *= aScalar;
	w *= aScalar;

	return (*this);
}


//Operator /

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator/(const Vector4<TYPE>& aVector4) const
{
	Vector4<TYPE> vector(x / aVector4.x, y / aVector4.y, z / aVector4.z, w / aVector4.w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator/(const Vector3<TYPE>& aVector3) const
{
	Vector4<TYPE> vector(x / aVector3.x, y / aVector3.y, z / aVector3.z, w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator/(const Vector2<TYPE>& aVector2) const
{
	Vector4<TYPE> vector(x / aVector2.x, y / aVector2.y, z, w);

	return vector;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::operator/(const TYPE& aScalar) const
{
	Vector4<TYPE> vector(x / aScalar, y / aScalar, z / aScalar, w / aScalar);

	return vector;
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator/=(const Vector4<TYPE>& aVector4)
{
	x /= aVector4.x;
	y /= aVector4.y;
	z /= aVector4.z;
	w /= aVector4.w;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator/=(const Vector3<TYPE>& aVector3)
{
	x /= aVector3.x;
	y /= aVector3.y;
	z /= aVector3.z;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator/=(const Vector2<TYPE>& aVector2)
{
	x /= aVector2.x;
	y /= aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector4<TYPE>& Vector4<TYPE>::operator/=(const TYPE& aScalar)
{
	x /= aScalar;
	y /= aScalar;
	z /= aScalar;
	w /= aScalar;

	return (*this);
}



/* Utility methods */

template<typename TYPE>
template<typename T>
Vector4<TYPE>::operator Vector4<T>() const
{
	return Vector4<T>(static_cast<T>(x), static_cast<T>(y), static_cast<T>(z), static_cast<T>(w));
}

template<typename TYPE>
template<typename T>
Vector4<TYPE>::operator Vector3<T>() const
{
	return Vector3<T>(static_cast<T>(x), static_cast<T>(y), static_cast<T>(z));
}

template<typename TYPE>
template<typename T>
Vector4<TYPE>::operator Vector2<T>() const
{
	return Vector2<T>(static_cast<T>(x), static_cast<T>(y));
}

template<typename TYPE>
const Vector3<TYPE> Vector4<TYPE>::AsVector3() const
{
	return Vector3<TYPE>(x, y, z);
}

template<typename TYPE>
const Vector2<TYPE> Vector4<TYPE>::AsVector2() const
{
	return Vector2<TYPE>(x, y);
}

template<typename TYPE>
void Vector4<TYPE>::Set(TYPE aX, TYPE aY, TYPE aZ, TYPE aW)
{
	x = aX;
	y = aY;
	z = aZ;
	w = aW;
}

template<typename TYPE>
void Vector4<TYPE>::Set(const Vector4<TYPE> aVector4)
{
	x = aVector4.x;
	y = aVector4.y;
	z = aVector4.z;
	w = aVector4.w;
}

template<typename TYPE>
void Vector4<TYPE>::Set(const Vector3<TYPE> aVector3)
{
	x = aVector3.x;
	y = aVector3.y;
	z = aVector3.z;
}

template<typename TYPE>
void Vector4<TYPE>::Set(const Vector2<TYPE> aVector2)
{
	x = aVector2.x;
	y = aVector2.y;
}

template<typename TYPE>
const TYPE Vector4<TYPE>::Dot(const Vector4<TYPE>& aVector4) const
{
	TYPE product = 0;

	product += (x * aVector4.x);
	product += (y * aVector4.y);
	product += (z * aVector4.z);
	product += (w * aVector4.w);

	return product;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::GetInversed() const
{
	return Vector4<TYPE>(1 / x, 1 / y, 1 / z, 1 / w);
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::GetNormalized() const
{
	Vector4<TYPE> aVector(*this);
	aVector.Normalize();

	return (aVector);
}

template<typename TYPE>
const TYPE Vector4<TYPE>::Length() const
{
	TYPE lenght = static_cast<TYPE>(sqrt(x * x + y * y + z * z + w * w));

	return lenght;
}

template<typename TYPE>
const TYPE Vector4<TYPE>::Length2() const
{
	TYPE lenght2 = x * x + y * y + z * z + w * w;

	return lenght2;
}

template<typename TYPE>
void Vector4<TYPE>::Normalize()
{
	TYPE lenght = Length();
	x /= lenght;
	y /= lenght;
	z /= lenght;
	w /= lenght;
}

template<typename TYPE>
void Vector4<TYPE>::Inverse()
{
	x = 1 / x;
	y = 1 / y;
	z = 1 / z;
	w = 1 / w;
}

template<typename TYPE>
const Vector4<TYPE> Vector4<TYPE>::Lerp(const Vector4<TYPE>& aVector4, const Vector4<TYPE>& aSecondVector4, TYPE aLerpVal)
{
	Vector4<TYPE> lerpedVector;

	lerpedVector.x = aVector4.x + (aSecondVector4.x - aVector4.x) * aLerpVal;
	lerpedVector.y = aVector4.y + (aSecondVector4.y - aVector4.y) * aLerpVal;
	lerpedVector.z = aVector4.z + (aSecondVector4.z - aVector4.z) * aLerpVal;
	lerpedVector.w = aVector4.w + (aSecondVector4.w - aVector4.w) * aLerpVal;
	return lerpedVector;
}