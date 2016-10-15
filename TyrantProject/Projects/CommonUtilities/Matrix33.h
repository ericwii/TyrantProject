#pragma once
#include "Vector3.h"

namespace CommonUtilities
{
	template<typename T>
	class Matrix33
	{
	public:
		Matrix33();
		Matrix33(const Matrix33<T>& aMatrix);
		~Matrix33();

		bool operator==(const Matrix33<T>& aMatrix33);
		Matrix33<T>& operator=(const Matrix33<T> aMatrix33);

		const Matrix33<T> operator+(const Matrix33<T>& aMatrix33) const;
		Matrix33<T>& operator+=(const Matrix33<T>& aMatrix33);

		const Matrix33<T> operator-(const Matrix33<T>& aMatrix33) const;
		Matrix33<T>& operator-=(const Matrix33<T>& aMatrix33);

		const Matrix33<T> operator*(const Matrix33<T>& aMatrix33) const;
		Matrix33<T>& operator*=(const Matrix33<T>& aMatrix33);


		static Matrix33<T> CreateRotateAroundX(T aAngleInRadians);
		static Matrix33<T> CreateRotateAroundY(T aAngleInRadians);
		static Matrix33<T> CreateRotateAroundZ(T aAngleInRadians);

		void Rotate2D(float aAngleInRadians);
		void SetRotation2d(float aAngleInRadians);
		void SetTranslation(const Vector3<T>& aVector3);
		Matrix33<T>& Transpose();

		Vector3<T> GetTranslation() const;

		T matrix[9];
	};



	/* Contructors/Destructor */

	template<typename T>
	Matrix33<T>::Matrix33()
	{
		matrix =
		{
			1,0,0,
			0,1,0,
			0,0,1
		};
	}

	template<typename T>
	Matrix33<T>::Matrix33(const Matrix33<T>& aMatrix33)
	{
		matrix[0] = aMatrix33.matrix[0];
		matrix[1] = aMatrix33.matrix[1];
		matrix[2] = aMatrix33.matrix[2];
		matrix[3] = aMatrix33.matrix[3];
		matrix[4] = aMatrix33.matrix[4];
		matrix[5] = aMatrix33.matrix[5];
		matrix[6] = aMatrix33.matrix[6];
		matrix[7] = aMatrix33.matrix[7];
		matrix[8] = aMatrix33.matrix[8];
	}

	template<typename T>
	Matrix33<T>::~Matrix33()
	{
	}



	/* Operators */


	template<typename T>
	bool Matrix33<T>::operator==(const Matrix33<T>& aMatrix33) 
	{
		for (int i = 0; i < 9; ++i)
		{
			if (matrix[i] != aMatrix33.matrix[i])
			{
				return false;
			}
		}
		return true;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator=(const Matrix33<T> aMatrix33) 
	{
		matrix[0] = aMatrix33.matrix[0];
		matrix[1] = aMatrix33.matrix[1];
		matrix[2] = aMatrix33.matrix[2];
		matrix[3] = aMatrix33.matrix[3];
		matrix[4] = aMatrix33.matrix[4];
		matrix[5] = aMatrix33.matrix[5];
		matrix[6] = aMatrix33.matrix[6];
		matrix[7] = aMatrix33.matrix[7];
		matrix[8] = aMatrix33.matrix[8];
		return (*this);
	}


	//Operator +

	template<typename T>
	const Matrix33<T> Matrix33<T>::operator+(const Matrix33<T>& aMatrix33) const
	{
		Matrix33<T> tempMatrix;
		for (int i = 0; i < 9; ++i)
		{
			tempMatrix.matrix[i] = matrix[i] + aMatrix33.matrix[i];
		}

		return tempMatrix;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator+=(const Matrix33<T>& aMatrix33)
	{
		for (int i = 0; i < 9; ++i)
		{
			matrix[i] += aMatrix33.matrix[i];
		}

		return (*this);
	}


	//Operator -

	template<typename T>
	const Matrix33<T> Matrix33<T>::operator-(const Matrix33<T>& aMatrix33) const
	{
		Matrix33<T> tempMatrix;
		for (int i = 0; i < 9; ++i)
		{
			tempMatrix.matrix[i] = matrix[i] - aMatrix33.matrix[i];
		}

		return tempMatrix;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator-=(const Matrix33<T>& aMatrix33)
	{
		for (int i = 0; i < 9; ++i)
		{
			matrix[i] -= aMatrix33.matrix[i];
		}

		return (*this);
	}


	//Operator *

	template<typename T>
	const Matrix33<T> Matrix33<T>::operator*(const Matrix33<T>& aMatrix33) const
	{
		Matrix33<T> tempMatrix;

		tempMatrix.matrix[0] = (matrix[0] * aMatrix33.matrix[0]) + (matrix[1] * aMatrix33.matrix[3]) + (matrix[2] * aMatrix33.matrix[6]);
		tempMatrix.matrix[1] = (matrix[0] * aMatrix33.matrix[1]) + (matrix[1] * aMatrix33.matrix[4]) + (matrix[2] * aMatrix33.matrix[7]);
		tempMatrix.matrix[2] = (matrix[0] * aMatrix33.matrix[2]) + (matrix[1] * aMatrix33.matrix[5]) + (matrix[2] * aMatrix33.matrix[8]);

		tempMatrix.matrix[3] = (matrix[3] * aMatrix33.matrix[0]) + (matrix[4] * aMatrix33.matrix[3]) + (matrix[5] * aMatrix33.matrix[6]);
		tempMatrix.matrix[4] = (matrix[3] * aMatrix33.matrix[1]) + (matrix[4] * aMatrix33.matrix[4]) + (matrix[5] * aMatrix33.matrix[7]);
		tempMatrix.matrix[5] = (matrix[3] * aMatrix33.matrix[2]) + (matrix[4] * aMatrix33.matrix[5]) + (matrix[5] * aMatrix33.matrix[8]);

		tempMatrix.matrix[6] =  (matrix[6] * aMatrix33.matrix[0]) + (matrix[7] * aMatrix33.matrix[3]) + (matrix[8] * aMatrix33.matrix[6]);
		tempMatrix.matrix[7] =  (matrix[6] * aMatrix33.matrix[1]) + (matrix[7] * aMatrix33.matrix[4]) + (matrix[8] * aMatrix33.matrix[7]);
		tempMatrix.matrix[8] = (matrix[6] * aMatrix33.matrix[2]) + (matrix[7] * aMatrix33.matrix[5]) + (matrix[8] * aMatrix33.matrix[8]);

		return tempMatrix;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::operator*=(const Matrix33<T>& aMatrix33)
	{
		Matrix33<T> tempMatrix;

		tempMatrix.matrix[0] = (matrix[0] * aMatrix33.matrix[0]) + (matrix[1] * aMatrix33.matrix[3]) + (matrix[2] * aMatrix33.matrix[6]);
		tempMatrix.matrix[1] = (matrix[0] * aMatrix33.matrix[1]) + (matrix[1] * aMatrix33.matrix[4]) + (matrix[2] * aMatrix33.matrix[7]);
		tempMatrix.matrix[2] = (matrix[0] * aMatrix33.matrix[2]) + (matrix[1] * aMatrix33.matrix[5]) + (matrix[2] * aMatrix33.matrix[8]);

		tempMatrix.matrix[3] = (matrix[3] * aMatrix33.matrix[0]) + (matrix[4] * aMatrix33.matrix[3]) + (matrix[5] * aMatrix33.matrix[6]);
		tempMatrix.matrix[4] = (matrix[3] * aMatrix33.matrix[1]) + (matrix[4] * aMatrix33.matrix[4]) + (matrix[5] * aMatrix33.matrix[7]);
		tempMatrix.matrix[5] = (matrix[3] * aMatrix33.matrix[2]) + (matrix[4] * aMatrix33.matrix[5]) + (matrix[5] * aMatrix33.matrix[8]);

		tempMatrix.matrix[6] = (matrix[6] * aMatrix33.matrix[0]) + (matrix[7] * aMatrix33.matrix[3]) + (matrix[8] * aMatrix33.matrix[6]);
		tempMatrix.matrix[7] = (matrix[6] * aMatrix33.matrix[1]) + (matrix[7] * aMatrix33.matrix[4]) + (matrix[8] * aMatrix33.matrix[7]);
		tempMatrix.matrix[8] = (matrix[6] * aMatrix33.matrix[2]) + (matrix[7] * aMatrix33.matrix[5]) + (matrix[8] * aMatrix33.matrix[8]);

		(*this) = tempMatrix;
		return (*this);
	}

	template<typename T>
	Vector2<T> operator*(const Vector2<T> aVector, const Matrix33<T> aMatrix33)
	{
		Vector3<T> vector3(aVector.X, aVector.Y, 1);

		vector3 *= aMatrix33;

		return Vector2<T>(vector3.X, vector3.Y);
	}

	template<typename T>
	Vector2<T> operator*=(Vector2<T>& aVector, const Matrix33<T> aMatrix33)
	{
		Vector3<T> vector3(aVector.X, aVector.Y, 1);

		vector3 *= aMatrix33;

		aVector.X = vector3.X;
		aVector.Y = vector3.Y;

		return aVector;
	}

	template<typename T>
	Vector3<T> operator*(const Vector3<T> aVector, const Matrix33<T> aMatrix33)
	{
		Vector3<T> tempVector;
		tempVector.X = aVector.Dot(Vector3<T>(aMatrix33.matrix[0], aMatrix33.matrix[3], aMatrix33.matrix[6]));
		tempVector.Y = aVector.Dot(Vector3<T>(aMatrix33.matrix[1], aMatrix33.matrix[4], aMatrix33.matrix[7]));
		tempVector.Z = aVector.Dot(Vector3<T>(aMatrix33.matrix[2], aMatrix33.matrix[5], aMatrix33.matrix[8]));

		return tempVector;
	}

	template<typename T>
	Vector3<T> operator*=(Vector3<T>& aVector, const Matrix33<T> aMatrix33)
	{
		Vector3<T> tempVector;
		tempVector.X = aVector.Dot(Vector3<T>(aMatrix33.matrix[0], aMatrix33.matrix[3], aMatrix33.matrix[6]));
		tempVector.Y = aVector.Dot(Vector3<T>(aMatrix33.matrix[1], aMatrix33.matrix[4], aMatrix33.matrix[7]));
		tempVector.Z = aVector.Dot(Vector3<T>(aMatrix33.matrix[2], aMatrix33.matrix[5], aMatrix33.matrix[8]));

		aVector = tempVector;

		return aVector;
	}



	/* Utility methods */

	template<typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundX(T aAngleInRadians)
	{
		//X = X
		//Y = Y*cos(angle) + Z*sin(angle)
		//Z = -Y*sin(angle) + Z*cos(angle)
		Matrix33<T> tempMatrix;

		tempMatrix.matrix[0] = 1;
		tempMatrix.matrix[1] = 0;
		tempMatrix.matrix[2] = 0;
		tempMatrix.matrix[3] = 0;
		tempMatrix.matrix[4] = cos(aAngleInRadians);
		tempMatrix.matrix[5] = sin(aAngleInRadians);
		tempMatrix.matrix[6] = 0;
		tempMatrix.matrix[7] = -sin(aAngleInRadians);
		tempMatrix.matrix[8] = cos(aAngleInRadians);

		return tempMatrix;
	}

	template<typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundY(T aAngleInRadians)
	{
		//X = X*cos(angle)-Z*sin(angle) 
		//Y = Y
		//Z = -X*sin(angle) + Z*cos(angle)
		Matrix33<T> tempMatrix;

		tempMatrix.matrix[0] = cos(aAngleInRadians);
		tempMatrix.matrix[1] = 0;
		tempMatrix.matrix[2] = -sin(aAngleInRadians);
		tempMatrix.matrix[3] = 0;
		tempMatrix.matrix[4] = 1;
		tempMatrix.matrix[5] = 0;
		tempMatrix.matrix[6] = sin(aAngleInRadians);
		tempMatrix.matrix[7] = 0;
		tempMatrix.matrix[8] = cos(aAngleInRadians);

		return tempMatrix;
	}

	template<typename T>
	Matrix33<T> Matrix33<T>::CreateRotateAroundZ(T aAngleInRadians)
	{
		//X = X*cos(angle) + Y*sin(angle);
		//Y = -X*sin(angle) + Y*cos(angle);
		//Z = Z;

		Matrix33<T> tempMatrix;

		tempMatrix.matrix[0] = cos(aAngleInRadians);
		tempMatrix.matrix[1] = sin(aAngleInRadians);
		tempMatrix.matrix[2] = 0;
		tempMatrix.matrix[3] = -sin(aAngleInRadians);
		tempMatrix.matrix[4] = cos(aAngleInRadians);
		tempMatrix.matrix[5] = 0;
		tempMatrix.matrix[6] = 0;
		tempMatrix.matrix[7] = 0;
		tempMatrix.matrix[8] = 0;

		return tempMatrix;
	}

	template<typename T>
	void Matrix33<T>::Rotate2D(float aAngleInRadians)
	{
		Matrix33<float> identityMatrix = CreateRotateAroundZ(aAngleInRadians);

		Matrix33<float> matrixCopy = (*this);

		matrixCopy *= identityMatrix;

		matrix[0] = matrixCopy.matrix[0];
		matrix[1] = matrixCopy.matrix[1];
		matrix[3] = matrixCopy.matrix[3];
		matrix[4] = matrixCopy.matrix[4];
	}

	template<typename T>
	void Matrix33<T>::SetRotation2d(float aAngleInRadians)
	{
		matrix[0] = cos(aAngleInRadians);
		matrix[1] = sin(aAngleInRadians);
		matrix[2] = 0;
		matrix[3] = -sin(aAngleInRadians);
		matrix[4] = cos(aAngleInRadians);
		matrix[5] = 0;
		matrix[6] = 0;
		matrix[7] = 0;
		matrix[8] = 1;
	}

	template<typename T>
	void Matrix33<T>::SetTranslation(const Vector3<T>& aVector3)
	{
		matrix[6] = aVector3.X;
		matrix[7] = aVector3.Y;
		matrix[8] = aVector3.Z;
	}

	template<typename T>
	Matrix33<T>& Matrix33<T>::Transpose()
	{
		Vector3<T> firstRow(matrix[0], matrix[3], matrix[6]);
		Vector3<T> secondRow(matrix[1], matrix[4], matrix[7]);
		Vector3<T> thirdRow(matrix[2], matrix[5], matrix[8]);

		matrix[0] = firstRow.X;
		matrix[1] = firstRow.Y;
		matrix[2] = firstRow.Z;

		matrix[3] = secondRow.X;
		matrix[4] = secondRow.Y;
		matrix[5] = secondRow.Z;

		matrix[6] = thirdRow.X;
		matrix[7] = thirdRow.Y;
		matrix[8] = thirdRow.Z;

		return (*this);
	}

	template<typename T>
	Vector3<T> Matrix33<T>::GetTranslation() const
	{
		return Vector3<T>(matrix[6], matrix[7], matrix[8]);
	}
}