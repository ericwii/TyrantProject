#pragma once
#include "Vector3.h"


namespace CommonUtilities
{
	template<typename T>
	class Plane
	{
	public:
		Plane(){};
		Plane(Vector3<T> aFirstPoint, Vector3<T> aSecondPoint, Vector3<T> aThirdPoint) : point(aFirstPoint)
		{
			Vector3<T> firstDifference = aSecondPoint - aFirstPoint;
			Vector3<T> secondDifference = aThirdPoint - aSecondPoint;
			normal = Cross(firstDifference, secondDifference);
			Normalize(myNormal);
		}
		Plane(Vector3<T> aPoint, Vector3<T> aNormal) : point(aPoint), normal(aNormal)
		{ }

		bool operator ==(const Plane<T>& aPlane)
		{
			if (myNormal == aPlane.myNormal)
			{
				if (myPoint == aPlane.myPoint)
				{
					return true;
				}
			}
			return false;
		}

		void InitWith3Points(Vector3<T> aFirstPoint, Vector3<T> aSecondPoint, Vector3<T> aThirdPoint)
		{
			point = aFirstPoint;
			Vector3<T> firstDifference = aSecondPoint - aFirstPoint;
			Vector3<T> secondDifference = aThirdPoint - aSecondPoint;
			normal = Cross(firstDifference, secondDifference);
			Normalize(myNormal);
		}

		void InitWithPointAndNormal(Vector3<T> aPoint, Vector3<T> aNormal)
		{
			point = aPoint;
			normal = aNormal;
		}

		bool Inside(const Vector3<T>& aPosition) const
		{
			Vector3<T> difference = (point - aPosition);
			if (difference.Dot(normal) <= 0)
			{
				return true;
			}
			return false;
		}

	private:
		Vector3<T> point;
		Vector3<T> normal;
	};
}