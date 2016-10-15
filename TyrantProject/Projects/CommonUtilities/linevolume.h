#pragma once
#include "Vector.h"
#include "line.h"
#include <vector>

namespace CommonUtilities
{
	template<typename T>
	class LineVolume
	{
	public:
		LineVolume(std::vector<Line<T>> aLineList)
		{
			myList = aLineList;
		}


		void AddLine(Line<T> aLine)
		{
			myList.push_back(aLine);
		}

		void RemoveLine(Line<T> aLine)
		{
			int index = -1;
			for (unsigned int i = 0; i < myList.size(); i++)
			{
				if (myList[i] == aLine)
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

		bool Inside(Vector2<T> aPosition)
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
		std::vector<Line<T>> myList;
	};
}