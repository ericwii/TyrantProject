#pragma once
#pragma warning (disable : 4201)

template<typename TYPE>
class Vector2
{
public:
	Vector2(TYPE aX = 0, TYPE aY = 0);
	Vector2(const Vector2<TYPE>& aVector2);
	~Vector2();

	bool operator==(const Vector2<TYPE>& aVector2) const;

	const Vector2<TYPE> operator+(const Vector2<TYPE>& aVector2) const;
	const Vector2<TYPE> operator+(const TYPE& aScalar) const;
	Vector2<TYPE>& operator+=(const Vector2<TYPE>& aVector2);
	Vector2<TYPE>& operator+=(const TYPE& aScalar);

	const Vector2<TYPE> operator-(const Vector2<TYPE>& aVector2) const;
	const Vector2<TYPE> operator-(const TYPE& aScalar) const;
	Vector2<TYPE>& operator-=(const Vector2<TYPE>& aVector2);
	Vector2<TYPE>& operator-=(const TYPE& aScalar);

	const Vector2<TYPE> operator*(const Vector2<TYPE>& aVector2) const;
	const Vector2<TYPE> operator*(const TYPE& aScalar) const;
	Vector2<TYPE>& operator*=(const Vector2<TYPE>& aVector2);
	Vector2<TYPE>& operator*=(const TYPE& aScalar);

	const Vector2<TYPE> operator/(const Vector2<TYPE>& aVector2) const;
	const Vector2<TYPE> operator/(const TYPE& aScalar) const;
	Vector2<TYPE>& operator/=(const Vector2<TYPE>& aVector2);
	Vector2<TYPE>& operator/=(const TYPE& aScalar);


	template<typename T>
	operator Vector2<T>() const;

	inline void Set(TYPE aX, TYPE aY);
	inline void Set(Vector2<TYPE> aVector2);
	const TYPE Dot(const Vector2<TYPE>& aVector2) const;
	const Vector2<TYPE> GetNormalized() const;
	const Vector2<TYPE> GetInversed() const;
	const TYPE Length() const;
	const TYPE Length2() const;
	void Normalize();
	void Inverse();

	static const Vector2<TYPE> Lerp(const Vector2<TYPE>& aVector2, const Vector2<TYPE>& aSecondVector2, TYPE aLerpVal);

	union
	{
		struct { TYPE x, y; };
		TYPE array[2];
	};
};

/* Constructors\Destructor */

template<typename TYPE>
Vector2<TYPE>::Vector2(TYPE aX = 0, TYPE aY = 0)
{
	x = aX;
	y = aY;
}

template<typename TYPE>
Vector2<TYPE>::Vector2(const Vector2<TYPE>& aVector2)
{
	x = aVector2.x;
	y = aVector2.y;
}

template<typename TYPE>
Vector2<TYPE>::~Vector2()
{
}



/* Operators */

//Operator ==

template<typename TYPE>
bool Vector2<TYPE>::operator==(const Vector2<TYPE>& aVector2) const
{
	if (aVector2.x == x && aVector2.y == y)
	{
		return true;	
	}
	return false;
}


//Operator +

template<typename TYPE>
const Vector2<TYPE> Vector2<TYPE>::operator+(const Vector2<TYPE>& aVector2) const
{
	Vector2<TYPE> aVector(x + aVector2.x, y + aVector2.y);

	return aVector;
}

template<typename TYPE>
const Vector2<TYPE> Vector2<TYPE>::operator+(const TYPE& aScalar) const
{
	Vector2<TYPE> aVector(x + aScalar, y + aScalar);

	return aVector;
}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator+=(const Vector2<TYPE>& aVector2)
{
	x += aVector2.x;
	y += aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator+=(const TYPE& aScalar)
{
	x += aScalar;
	y += aScalar;

	return (*this);
}


//Operator -

template<typename TYPE>
const Vector2<TYPE> Vector2<TYPE>::operator-(const Vector2<TYPE>& aVector2) const
{
	Vector2<TYPE> aVector(x - aVector2.x, y - aVector2.y);

	return aVector;
}

template<typename TYPE>
const Vector2<TYPE> Vector2<TYPE>::operator-(const TYPE& aScalar) const
{
	Vector2<TYPE> aVector(x - aScalar, y - aScalar);

	return aVector;
}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator-=(const Vector2<TYPE>& aVector2)
{
	x -= aVector2.x;
	y -= aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator-=(const TYPE& aScalar)
{
	x -= aScalar;
	y -= aScalar;

	return (*this);
}


//Operator *

template<typename TYPE>
const Vector2<TYPE> Vector2<TYPE>::operator*(const Vector2<TYPE>& aVector2) const
{
	Vector2<TYPE> aVector(x * aVector2.x, y * aVector2.y);

	return aVector;
}

template<typename TYPE>
const Vector2<TYPE> Vector2<TYPE>::operator*(const TYPE& aScalar) const
{
	Vector2<TYPE> aVector(x * aScalar, y * aScalar);

	return aVector;
}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator*=(const Vector2<TYPE>& aVector2)
{
	x *= aVector2.x;
	y *= aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator*=(const TYPE& aScalar)
{
	x *= aScalar;
	y *= aScalar;

	return (*this);
}


//Operator /

template<typename TYPE>
const Vector2<TYPE> Vector2<TYPE>::operator/(const Vector2<TYPE>& aVector2) const
{
	Vector2<TYPE> aVector(x / aVector2.x, y / aVector2.y);

	return aVector;
}

template<typename TYPE>
const Vector2<TYPE> Vector2<TYPE>::operator/(const TYPE& aScalar) const
{
	Vector2<TYPE> aVector(x / aScalar, y / aScalar);

	return aVector;
}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator/=(const Vector2<TYPE>& aVector2)
{
	x /= aVector2.x;
	y /= aVector2.y;

	return (*this);
}

template<typename TYPE>
Vector2<TYPE>& Vector2<TYPE>::operator/=(const TYPE& aScalar)
{
	x /= aScalar;
	y /= aScalar;

	return (*this);
}



/* Utility methods */

template<typename TYPE>
template<typename T>
Vector2<TYPE>::operator Vector2<T>() const
{
	return Vector2<T>(static_cast<T>(x), static_cast<T>(y));
}

template<typename TYPE>
void Vector2<TYPE>::Set(TYPE aX, TYPE aY)
{
	x = aX;
	y = aY;
}

template<typename TYPE>
void Vector2<TYPE>::Set(Vector2<TYPE> aVector2)
{
	x = aVector2.x;
	y = aVector2.y;
}

template<typename TYPE>
const TYPE Vector2<TYPE>::Length() const
{
	TYPE lenght = static_cast<TYPE>(sqrt(x * x + y * y));

	return lenght;
}

template<typename TYPE>
const TYPE Vector2<TYPE>::Length2() const
{
	TYPE lenght2 = x * x + y * y;

	return lenght2;
}

template<typename TYPE>
const TYPE Vector2<TYPE>::Dot(const Vector2<TYPE>& aVector2) const
{
	TYPE product = 0;

	product += (aVector2.x * aSecondVector2.x);
	product += (aVector2.y * aSecondVector2.y);

	return product;
}

template<typename TYPE>
void Vector2<TYPE>::Normalize()
{
	TYPE lenght = Length();
	x /= lenght;
	y /= lenght;
}

template<typename TYPE>
void Vector2<TYPE>::Inverse()
{
	x = 1 / x;
	y = 1 / y;
}

template<typename TYPE>
const Vector2<TYPE> Vector2<TYPE>::GetNormalized() const
{
	Vector2<TYPE> aVector(x,y);
	aVector.Normalize();

	return (aVector);
}

template<typename TYPE>
const Vector2<TYPE> Vector2<TYPE>::GetInversed() const
{
	return Vector2<TYPE>(1 / x, 1 / y);
}

template<typename TYPE>
const Vector2<TYPE> Lerp(const Vector2<TYPE>& aVector2, const Vector2<TYPE>& aSecondVector2, TYPE aLerpVal)
{
	Vector2<TYPE> lerpedVector;

	lerpedVector.x = aVector2.x + (aSecondVector2.x - aVector2.x) * aLerpVal;
	lerpedVector.y = aVector2.y + (aSecondVector2.y - aVector2.y) * aLerpVal;
	return lerpedVector;
}