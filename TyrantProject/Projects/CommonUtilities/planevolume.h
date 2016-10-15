#pragma once
#include "Vector.h"
#include "plane.h"
#include <vector>

namespace CommonUtilities
{
	template<typename T>
	class PlaneVolume
	{
	public:
		PlaneVolume(std::vector<Plane<T>> aPlaneList)
		{
			myList = aPlaneList;
		}


		void AddPlane(Plane<T> aPlane)
		{
			myList.push_back(aPlane);
		}

		void RemovePlane(Plane<T> aPlane)
		{
			int index = -1;
			for (unsigned int i = 0; i < myList.size(); i++)
			{
				if (myList[i] == aPlane)
				{
					index = i;
					break;
				}
			}

			if (index >= 0)
			{
				myList.erase(myList.begin() + index);
			}
		}

		bool Inside(Vector3<T> aPosition)
		{
			for (unsigned int i = 0; i < myList.size(); i++)
			{
				if (myList[i].Inside(aPosition) == false)
				{
					return false;
				}
			}
			return true;
		}

	private:
		std::vector<Plane<T>> myList;
	};
}