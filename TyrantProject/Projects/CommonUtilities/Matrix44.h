#pragma once
#include "Vector4.h"
#include "Matrix33.h"

namespace CommonUtilities
{
	template<typename T>
	class Matrix44
	{
	public:
		Matrix44<T>();
		Matrix44<T>(const Matrix44<T>& aMatrix44);
		Matrix44<T>(const Matrix33<T>& aMatrix33);

		bool operator==(const Matrix44<T>& aMatrix44);
		Matrix44<T>& operator=(const Matrix44<T>& aMatrix44);

		const Matrix44<T> operator+(const Matrix44<T>& aMatrix44) const;
		Matrix44<T>& operator+=(const Matrix44<T>& aMatrix44);

		const Matrix44<T> operator-(const Matrix44<T>& aMatrix44) const;
		Matrix44<T>& operator-=(const Matrix44<T>& aMatrix44);

		const Matrix44<T> operator*(const Matrix44<T>& aMatrix44) const;
		Matrix44<T>& operator*=(const Matrix44<T>& aMatrix44);

		static Matrix44<T> CreateRotateAroundX(T aAngleInRadians);
		static Matrix44<T> CreateRotateAroundY(T aAngleInRadians);
		static Matrix44<T> CreateRotateAroundZ(T aAngleInRadians);

		Vector3<T> GetUp() const;
		Vector3<T> GetRight() const;
		Vector3<T> GetForward() const;

		Vector4<T> GetTranslation() const;
		Vector3<T> GetPosition() const;

		void SetTranslation(Vector4<T> aVector4);
		void SetPosition(Vector3<T> aVector3);
		Matrix44<T>& Transpose();
		const Matrix44<T> GetInverse() const;

		T matrix[16];
	};




	/* Contructors/Destructor */

	template<typename T>
	Matrix44<T>::Matrix44()
	{
		matrix[0] = 1;
		matrix[1] = 0;
		matrix[2] = 0;
		matrix[3] = 0;

		matrix[4] = 0;
		matrix[5] = 1;
		matrix[6] = 0;
		matrix[7] = 0;

		matrix[8] = 0;
		matrix[9] = 0;
		matrix[10] = 1;
		matrix[11] = 0;

		matrix[12] = 0;
		matrix[13] = 0;
		matrix[14] = 0;
		matrix[15] = 1;
	}

	template<typename T>
	Matrix44<T>::Matrix44(const Matrix44<T>& aMatrix44)
	{
		matrix[0] = aMatrix44.matrix[0];
		matrix[1] = aMatrix44.matrix[1];
		matrix[2] = aMatrix44.matrix[2];
		matrix[3] = aMatrix44.matrix[3];
		matrix[4] = aMatrix44.matrix[4];
		matrix[5] = aMatrix44.matrix[5];
		matrix[6] = aMatrix44.matrix[6];
		matrix[7] = aMatrix44.matrix[7];
		matrix[8] = aMatrix44.matrix[8];
		matrix[9] = aMatrix44.matrix[9];
		matrix[10] = aMatrix44.matrix[10];
		matrix[11] = aMatrix44.matrix[11];
		matrix[12] = aMatrix44.matrix[12];
		matrix[13] = aMatrix44.matrix[13];
		matrix[14] = aMatrix44.matrix[14];
		matrix[15] = aMatrix44.matrix[15];
	}

	template<typename T>
	Matrix44<T>::Matrix44(const Matrix33<T>& aMatrix33)
	{
		matrix[0] = aMatrix33.matrix[0];
		matrix[1] = aMatrix33.matrix[1];
		matrix[2] = aMatrix33.matrix[2];
		matrix[3] = 0;

		matrix[4] = aMatrix33.matrix[3];
		matrix[5] = aMatrix33.matrix[4];
		matrix[6] = aMatrix33.matrix[5];
		matrix[7] = 0;

		matrix[8] = aMatrix33.matrix[6];
		matrix[9] = aMatrix33.matrix[7];
		matrix[10] = aMatrix33.matrix[8];
		matrix[11] = 0;

		matrix[12] = 0;
		matrix[13] = 0;
		matrix[14] = 0;
		matrix[15] = 1;
	}



	/* Operators */


	template<typename T>
	bool Matrix44<T>::operator==(const Matrix44<T>& aMatrix44)
	{
		for (int i = 0; i < 16; ++i)
		{
			if (matrix[i] != aMatrix44.matrix[i])
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator=(const Matrix44<T>& aMatrix44)
	{
		for (int i = 0; i < 16; ++i)
		{
			matrix[i] = aMatrix44.matrix[i];
		}

		return (*this);
	}


	//Operator +

	template<typename T>
	const Matrix44<T> Matrix44<T>::operator+(const Matrix44<T>& aMatrix44) const
	{
		Matrix44<T> tempMatrix;
		for (int i = 0; i < 16; ++i)
		{
			tempMatrix.matrix[i] = matrix[i] + aMatrix44.matrix[i];
		}

		return tempMatrix;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator+=(const Matrix44<T>& aMatrix44)
	{
		for (int i = 0; i < 16; ++i)
		{
			matrix[i] += aMatrix44.matrix[i];
		}

		return (*this);
	}


	//Operator -

	template<typename T>
	const Matrix44<T> Matrix44<T>::operator-(const Matrix44<T>& aMatrix44) const
	{
		Matrix44<T> tempMatrix;
		for (int i = 0; i < 16; ++i)
		{
			tempMatrix.matrix[i] = matrix[i] - aMatrix44.matrix[i];
		}

		return tempMatrix;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator-=(const Matrix44<T>& aMatrix44)
	{
		for (int i = 0; i < 16; ++i)
		{
			matrix[i] -= aMatrix44.matrix[i];
		}

		return (*this);
	}


	//Operator *

	template<typename T>
	const Matrix44<T> Matrix44<T>::operator*(const Matrix44<T>& aMatrix44) const
	{
		Matrix44<T> tempMatrix;

		tempMatrix.matrix[0] = (matrix[0] * aMatrix44.matrix[0]) + (matrix[1] * aMatrix44.matrix[4]) + (matrix[2] * aMatrix44.matrix[8]) + (matrix[3] * aMatrix44.matrix[12]);
		tempMatrix.matrix[1] = (matrix[0] * aMatrix44.matrix[1]) + (matrix[1] * aMatrix44.matrix[5]) + (matrix[2] * aMatrix44.matrix[9]) + (matrix[3] * aMatrix44.matrix[13]);
		tempMatrix.matrix[2] = (matrix[0] * aMatrix44.matrix[2]) + (matrix[1] * aMatrix44.matrix[6]) + (matrix[2] * aMatrix44.matrix[10]) + (matrix[3] * aMatrix44.matrix[14]);
		tempMatrix.matrix[3] = (matrix[0] * aMatrix44.matrix[3]) + (matrix[1] * aMatrix44.matrix[7]) + (matrix[2] * aMatrix44.matrix[11]) + (matrix[3] * aMatrix44.matrix[15]);

		tempMatrix.matrix[4] = (matrix[4] * aMatrix44.matrix[0]) + (matrix[5] * aMatrix44.matrix[4]) + (matrix[6] * aMatrix44.matrix[8]) + (matrix[7] * aMatrix44.matrix[12]);
		tempMatrix.matrix[5] = (matrix[4] * aMatrix44.matrix[1]) + (matrix[5] * aMatrix44.matrix[5]) + (matrix[6] * aMatrix44.matrix[9]) + (matrix[7] * aMatrix44.matrix[13]);
		tempMatrix.matrix[6] = (matrix[4] * aMatrix44.matrix[2]) + (matrix[5] * aMatrix44.matrix[6]) + (matrix[6] * aMatrix44.matrix[10]) + (matrix[7] * aMatrix44.matrix[14]);
		tempMatrix.matrix[7] = (matrix[4] * aMatrix44.matrix[3]) + (matrix[5] * aMatrix44.matrix[7]) + (matrix[6] * aMatrix44.matrix[11]) + (matrix[7] * aMatrix44.matrix[15]);

		tempMatrix.matrix[8] =  (matrix[8] * aMatrix44.matrix[0]) + (matrix[9] * aMatrix44.matrix[4]) + (matrix[10] * aMatrix44.matrix[8]) + (matrix[11] * aMatrix44.matrix[12]);
		tempMatrix.matrix[9] =  (matrix[8] * aMatrix44.matrix[1]) + (matrix[9] * aMatrix44.matrix[5]) + (matrix[10] * aMatrix44.matrix[9]) + (matrix[11] * aMatrix44.matrix[13]);
		tempMatrix.matrix[10] = (matrix[8] * aMatrix44.matrix[2]) + (matrix[9] * aMatrix44.matrix[6]) + (matrix[10] * aMatrix44.matrix[10]) + (matrix[11] * aMatrix44.matrix[14]);
		tempMatrix.matrix[11] = (matrix[8] * aMatrix44.matrix[3]) + (matrix[9] * aMatrix44.matrix[7]) + (matrix[10] * aMatrix44.matrix[11]) + (matrix[11] * aMatrix44.matrix[15]);

		tempMatrix.matrix[12] = (matrix[12] * aMatrix44.matrix[0]) + (matrix[13] * aMatrix44.matrix[4]) + (matrix[14] * aMatrix44.matrix[8]) + (matrix[15] * aMatrix44.matrix[12]);
		tempMatrix.matrix[13] = (matrix[12] * aMatrix44.matrix[1]) + (matrix[13] * aMatrix44.matrix[5]) + (matrix[14] * aMatrix44.matrix[9]) + (matrix[15] * aMatrix44.matrix[13]);
		tempMatrix.matrix[14] = (matrix[12] * aMatrix44.matrix[2]) + (matrix[13] * aMatrix44.matrix[6]) + (matrix[14] * aMatrix44.matrix[10]) + (matrix[15] * aMatrix44.matrix[14]);
		tempMatrix.matrix[15] = (matrix[12] * aMatrix44.matrix[3]) + (matrix[13] * aMatrix44.matrix[7]) + (matrix[14] * aMatrix44.matrix[11]) + (matrix[15] * aMatrix44.matrix[15]);

		return tempMatrix;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::operator*=(const Matrix44<T>& aMatrix44)
	{
		Matrix44<T> tempMatrix;

		tempMatrix.matrix[0] = (matrix[0] * aMatrix44.matrix[0]) + (matrix[1] * aMatrix44.matrix[4]) + (matrix[2] * aMatrix44.matrix[8]) + (matrix[3] * aMatrix44.matrix[12]);
		tempMatrix.matrix[1] = (matrix[0] * aMatrix44.matrix[1]) + (matrix[1] * aMatrix44.matrix[5]) + (matrix[2] * aMatrix44.matrix[9]) + (matrix[3] * aMatrix44.matrix[13]);
		tempMatrix.matrix[2] = (matrix[0] * aMatrix44.matrix[2]) + (matrix[1] * aMatrix44.matrix[6]) + (matrix[2] * aMatrix44.matrix[10]) + (matrix[3] * aMatrix44.matrix[14]);
		tempMatrix.matrix[3] = (matrix[0] * aMatrix44.matrix[3]) + (matrix[1] * aMatrix44.matrix[7]) + (matrix[2] * aMatrix44.matrix[11]) + (matrix[3] * aMatrix44.matrix[15]);

		tempMatrix.matrix[4] = (matrix[4] * aMatrix44.matrix[0]) + (matrix[5] * aMatrix44.matrix[4]) + (matrix[6] * aMatrix44.matrix[8]) + (matrix[7] * aMatrix44.matrix[12]);
		tempMatrix.matrix[5] = (matrix[4] * aMatrix44.matrix[1]) + (matrix[5] * aMatrix44.matrix[5]) + (matrix[6] * aMatrix44.matrix[9]) + (matrix[7] * aMatrix44.matrix[13]);
		tempMatrix.matrix[6] = (matrix[4] * aMatrix44.matrix[2]) + (matrix[5] * aMatrix44.matrix[6]) + (matrix[6] * aMatrix44.matrix[10]) + (matrix[7] * aMatrix44.matrix[14]);
		tempMatrix.matrix[7] = (matrix[4] * aMatrix44.matrix[3]) + (matrix[5] * aMatrix44.matrix[7]) + (matrix[6] * aMatrix44.matrix[11]) + (matrix[7] * aMatrix44.matrix[15]);

		tempMatrix.matrix[8] = (matrix[8] * aMatrix44.matrix[0]) + (matrix[9] * aMatrix44.matrix[4]) + (matrix[10] * aMatrix44.matrix[8]) + (matrix[11] * aMatrix44.matrix[12]);
		tempMatrix.matrix[9] = (matrix[8] * aMatrix44.matrix[1]) + (matrix[9] * aMatrix44.matrix[5]) + (matrix[10] * aMatrix44.matrix[9]) + (matrix[11] * aMatrix44.matrix[13]);
		tempMatrix.matrix[10] = (matrix[8] * aMatrix44.matrix[2]) + (matrix[9] * aMatrix44.matrix[6]) + (matrix[10] * aMatrix44.matrix[10]) + (matrix[11] * aMatrix44.matrix[14]);
		tempMatrix.matrix[11] = (matrix[8] * aMatrix44.matrix[3]) + (matrix[9] * aMatrix44.matrix[7]) + (matrix[10] * aMatrix44.matrix[11]) + (matrix[11] * aMatrix44.matrix[15]);

		tempMatrix.matrix[12] = (matrix[12] * aMatrix44.matrix[0]) + (matrix[13] * aMatrix44.matrix[4]) + (matrix[14] * aMatrix44.matrix[8]) + (matrix[15] * aMatrix44.matrix[12]);
		tempMatrix.matrix[13] = (matrix[12] * aMatrix44.matrix[1]) + (matrix[13] * aMatrix44.matrix[5]) + (matrix[14] * aMatrix44.matrix[9]) + (matrix[15] * aMatrix44.matrix[13]);
		tempMatrix.matrix[14] = (matrix[12] * aMatrix44.matrix[2]) + (matrix[13] * aMatrix44.matrix[6]) + (matrix[14] * aMatrix44.matrix[10]) + (matrix[15] * aMatrix44.matrix[14]);
		tempMatrix.matrix[15] = (matrix[12] * aMatrix44.matrix[3]) + (matrix[13] * aMatrix44.matrix[7]) + (matrix[14] * aMatrix44.matrix[11]) + (matrix[15] * aMatrix44.matrix[15]);

		(*this) = tempMatrix;

		return (*this);
	}

	template<typename T>
	Vector4<T> operator*(const Vector4<T>& aVector, const Matrix44<T>& aMatrix)
	{
		Vector4<T> tempVector;

		tempVector.x = aVector.Dot(Vector4<T>(aMatrix.matrix[0], aMatrix.matrix[4], aMatrix.matrix[8], aMatrix.matrix[12]));
		tempVector.y = aVector.Dot(Vector4<T>(aMatrix.matrix[1], aMatrix.matrix[5], aMatrix.matrix[9], aMatrix.matrix[13]));
		tempVector.z = aVector.Dot(Vector4<T>(aMatrix.matrix[2], aMatrix.matrix[6], aMatrix.matrix[10], aMatrix.matrix[14]));
		tempVector.w = aVector.Dot(Vector4<T>(aMatrix.matrix[3], aMatrix.matrix[7], aMatrix.matrix[11], aMatrix.matrix[15]));

		return tempVector;
	}		  

	template<typename T>
	Vector4<T>& operator*=(Vector4<T>& aVector, const Matrix44<T>& aMatrix)
	{
		Vector4<T> tempVector;

		tempVector.x = aVector.Dot(Vector4<T>(aMatrix.matrix[0], aMatrix.matrix[4], aMatrix.matrix[8], aMatrix.matrix[12]));
		tempVector.y = aVector.Dot(Vector4<T>(aMatrix.matrix[1], aMatrix.matrix[5], aMatrix.matrix[9], aMatrix.matrix[13]));
		tempVector.z = aVector.Dot(Vector4<T>(aMatrix.matrix[2], aMatrix.matrix[6], aMatrix.matrix[10], aMatrix.matrix[14]));
		tempVector.w = aVector.Dot(Vector4<T>(aMatrix.matrix[3], aMatrix.matrix[7], aMatrix.matrix[11], aMatrix.matrix[15]));

		aVector = tempVector;
		return aVector;
	}

	template<typename T>
	Vector3<T> operator*(const Vector3<T>& aVector, const Matrix44<T>& aMatrix)
	{
		Vector4<T> tempVector(aVector, 1);

		tempVector *= aMatrix;

		return Vector3<T>(tempVector.x, tempVector.y, tempVector.z);
	}

	template<typename T>
	Vector3<T>& operator*=(Vector3<T>& aVector, const Matrix44<T>& aMatrix)
	{
		Vector4<T> tempVector(aVector, 1);

		tempVector *= aMatrix;

		aVector.x = tempVector.x;
		aVector.y = tempVector.y;
		aVector.z = tempVector.z;
		return aVector;
	}

	template<typename T>
	Vector2<T> operator*(const Vector2<T>& aVector, const Matrix44<T>& aMatrix)
	{
		Vector4<T> tempVector(aVector,1, 1);

		tempVector *= aMatrix;

		return Vector2<T>(tempVector.x, tempVector.y);
	}

	template<typename T>
	Vector2<T>& operator*=(Vector2<T>& aVector, const Matrix44<T>& aMatrix)
	{
		Vector4<T> tempVector(aVector,1, 1);

		tempVector *= aMatrix;

		aVector.x = tempVector.x;
		aVector.y = tempVector.y;
		return aVector;
	}



	/* Utility methods*/

	template<typename T>
	Matrix44<T> Matrix44<T>::CreateRotateAroundX(T aAngleInRadians)
	{
		//X = X
		//Y = Y*cos(angle) + Z*sin(angle)
		//Z = -Y*sin(angle) + Z*cos(angle)
		Matrix44<T> tempMatrix;

		tempMatrix.matrix[0] = 1;
		tempMatrix.matrix[1] = 0;
		tempMatrix.matrix[2] = 0;
		tempMatrix.matrix[3] = 0;

		tempMatrix.matrix[4] = 0;
		tempMatrix.matrix[5] = cos(aAngleInRadians);
		tempMatrix.matrix[6] = sin(aAngleInRadians);
		tempMatrix.matrix[7] = 0;

		tempMatrix.matrix[8] = 0;
		tempMatrix.matrix[9] = -sin(aAngleInRadians);
		tempMatrix.matrix[10] = cos(aAngleInRadians);
		tempMatrix.matrix[11] = 0;

		tempMatrix.matrix[12] = 0;
		tempMatrix.matrix[13] = 0;
		tempMatrix.matrix[14] = 0;
		tempMatrix.matrix[15] = 1;

		return tempMatrix;
	}

	template<typename T>
	Matrix44<T> Matrix44<T>::CreateRotateAroundY(T aAngleInRadians)
	{
		//X = X*cos(angle)-Z*sin(angle) 
		//Y = Y
		//Z = -X*sin(angle) + Z*cos(angle)
		Matrix44<T> tempMatrix;

		tempMatrix.matrix[0] = cos(aAngleInRadians);
		tempMatrix.matrix[1] = 0;
		tempMatrix.matrix[2] = -sin(aAngleInRadians);
		tempMatrix.matrix[3] = 0;

		tempMatrix.matrix[4] = 0;
		tempMatrix.matrix[5] = 1;
		tempMatrix.matrix[6] = 0;
		tempMatrix.matrix[7] = 0;

		tempMatrix.matrix[8] = sin(aAngleInRadians);
		tempMatrix.matrix[9] = 0;
		tempMatrix.matrix[10] = cos(aAngleInRadians);
		tempMatrix.matrix[11] = 0;

		tempMatrix.matrix[12] = 0;
		tempMatrix.matrix[13] = 0;
		tempMatrix.matrix[14] = 0;
		tempMatrix.matrix[15] = 1;

		return tempMatrix;
	}

	template<typename T>
	Matrix44<T> Matrix44<T>::CreateRotateAroundZ(T aAngleInRadians)
	{
		//X = X*cos(angle) + Y*sin(angle);
		//Y = -X*sin(angle) + Y*cos(angle);
		//Z = Z;
		Matrix44<T> tempMatrix;

		tempMatrix.matrix[0] = cos(aAngleInRadians);
		tempMatrix.matrix[1] = sin(aAngleInRadians);
		tempMatrix.matrix[2] = 0;
		tempMatrix.matrix[3] = 0;

		tempMatrix.matrix[4] = -sin(aAngleInRadians);
		tempMatrix.matrix[5] = cos(aAngleInRadians);
		tempMatrix.matrix[6] = 0;
		tempMatrix.matrix[7] = 0;

		tempMatrix.matrix[8] = 0;
		tempMatrix.matrix[9] = 0;
		tempMatrix.matrix[10] = 1;
		tempMatrix.matrix[11] = 0;

		tempMatrix.matrix[12] = 0;
		tempMatrix.matrix[13] = 0;
		tempMatrix.matrix[14] = 0;
		tempMatrix.matrix[15] = 1;

		return tempMatrix;
	}

	template<typename T>
	Vector3<T> Matrix44<T>::GetRight() const
	{
		return Vector3<T>(matrix[0], matrix[1], matrix[2]);
	}

	template<typename T>
	Vector3<T> Matrix44<T>::GetUp() const
	{
		return Vector3<T>(matrix[4], matrix[5], matrix[6]);
	}

	template<typename T>
	Vector3<T> Matrix44<T>::GetForward() const
	{
		return Vector3<T>(matrix[8], matrix[9], matrix[10]);
	}

	template<typename T>
	Vector4<T> Matrix44<T>::GetTranslation() const
	{
		return Vector4<T>(matrix[12], matrix[13], matrix[14], matrix[15]);
	}

	template<typename T>
	Vector3<T> Matrix44<T>::GetPosition() const
	{
		return Vector3<T>(matrix[12], matrix[13], matrix[14]);
	}

	template<typename T>
	void Matrix44<T>::SetTranslation(Vector4<T> aVector4)
	{
		matrix[12] = aVector4.x;
		matrix[13] = aVector4.y;
		matrix[14] = aVector4.z;
		matrix[15] = aVector4.w;
	}

	template<typename T>
	void Matrix44<T>::SetPosition(Vector3<T> aVector3)
	{
		matrix[12] = aVector3.x;
		matrix[13] = aVector3.y;
		matrix[14] = aVector3.z;
	}

	template<typename T>
	Matrix44<T>& Matrix44<T>::Transpose()
	{
		T copy[12] =
		{
			matrix[4], matrix[8], matrix[12],
			matrix[1], matrix[9], matrix[13],
			matrix[2], matrix[6], matrix[14],
			matrix[3], matrix[7], matrix[11]
		};

		matrix[1] = copy[0];
		matrix[2] = copy[1];
		matrix[3] = copy[2];

		matrix[4] = copy[3];
		matrix[6] = copy[4];
		matrix[7] = copy[5];

		matrix[8] =  copy[6];
		matrix[9] =  copy[7];
		matrix[11] = copy[8];

		matrix[12] = copy[9];
		matrix[13] = copy[10];
		matrix[14] = copy[11];

		return (*this);
	}

	template<typename T>
	const Matrix44<T> Matrix44<T>::GetInverse() const
	{
		Matrix44<T> inversedMatrix(*this);

		Vector4<T> translation(inversedMatrix.GetTranslation());
		translation.x *= -1.f;
		translation.y *= -1.f;
		translation.z *= -1.f;
		translation.w = 1.f;

		inversedMatrix.matrix[12] = 0;
		inversedMatrix.matrix[13] = 0;
		inversedMatrix.matrix[14] = 0;
		inversedMatrix.matrix[15] = 1.f;

		inversedMatrix.Transpose();

		translation = translation * inversedMatrix;

		inversedMatrix.SetTranslation(translation);

		return inversedMatrix;
	}
}