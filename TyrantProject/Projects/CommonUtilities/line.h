#pragma once
#include "Vector.h"

namespace CommonUtilities
{
	template<typename T>
	class Line
	{
	public:
		Line(){}
		Line(Vector2<T> afirstPoint, Vector2<T> aSecondPoint)
		{
			myPoint = afirstPoint;

			Vector2<T> vector;
			vector.x = (aSecondPoint.x - afirstPoint.x);
			vector.y = (aSecondPoint.y - afirstPoint.y);

			T anX = vector.x;
			vector.x = -vector.y;
			vector.y = anX;

			Normalize(vector);

			myNormal = vector;
		}

		bool operator==(Line aLine)
		{
			if (myNormal == aLine.myNormal)
			{
				if (myPoint == aLine.myPoint)
				{
					return true;
				}
			}
			return false;
		}

		void InitWith2Points(Vector2<T> afirstPoint, Vector2<T> aSecondPoint)
		{
			myPoint = afirstPoint;

			Vector2<T> vector;
			vector.x = (aSecondPoint.x - afirstPoint.x);
			vector.y = (aSecondPoint.y - afirstPoint.y);

			T anX = vector.x;
			vector.x = -vector.y;
			vector.y = anX;

			Normalize(vector);

			myNormal = vector;
		}

		void InitWithPointAndDirection(Vector2<T> aPoint, Vector2<T> aDirection)
		{
			myPoint = aPoint;
			myNormal.x = -aDirection.y;
			myNormal.y = aDirection.x;
			Normalize(myNormal);
		}

		bool Inside(Vector2<T> aPosition)
		{
			if (Dot(myNormal, aPosition) <= 0)
			{
				return true;
			}
			return false;
		}

	private:
		Vector2<T> myNormal;
		Vector2<T> myPoint;
	};
}