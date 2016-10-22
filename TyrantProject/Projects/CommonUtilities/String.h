#pragma once

#include <map>
#include "Macro.h"
#include "Assert.h"


#define StringTemplate template<unsigned int Size=64>

namespace CommonUtilities
{
	StringTemplate
	class String
	{
	public:
		String();
		String(const String& aCopy);
		String(const char* aCopy);
		~String();

		String operator+(const char* aLiteralString) const;
		String operator+(const String& aString) const;
		String operator+(const double aDouble) const;
		String operator+(const float aFloat) const;
		String operator+(const int aInt) const;

		String& operator+=(const char* aLiteralString);
		String& operator+=(const String& aString);
		String& operator+=(const double aDouble);
		String& operator+=(const float aFloat);
		String& operator+=(const int aInt);

		char& operator[](const int aIndex);
		char& operator[](const int aIndex) const;


		bool operator==(const String& aString) const;
		void operator=(const String& aString);
		void operator=(const char* aLiteralString);

		int Find(const char* aLiteralString) const;


		String SubStr(const int aIndex, const int aLenght = Size) const;
		String& SetAsSubStr(const int aIndex, const int aLenght = Size);
		inline const char* c_str() const;
		inline int Lenght() const;


	private:
		char myArray[Size];
		int myCurrentSize;

		char IntToChar(int aInt);
	};

	//Constructors/Destructor

	StringTemplate
	String<Size>::String() : myCurrentSize(1)
	{
		myArray[0] = '\0';
	}

	StringTemplate
	String<Size>::String(const String<Size>& aCopy)
	{
		for (int i = 0; i < aCopy.myCurrentSize+1; ++i)
		{
			myArray[i] = aCopy.myArray[i];
		}

		myCurrentSize = aCopy.myCurrentSize;
	}

	StringTemplate
	String<Size>::String(const char* aLiteralString)
	{	
		int i = 0;
		for (; i < Size; ++i)
		{
			myArray[i] = aLiteralString[i];
		
			if (aLiteralString[i] == '\0')
			{
				break;
			}
		}
		
		myCurrentSize = i;
		DEBUG_ASSERT(i < Size,"Size out of bounds");
	}

	StringTemplate
	String<Size>::~String()
	{}


	//Operators

	//Operator +

	StringTemplate
	String<Size> String<Size>::operator+(const char* aLiteralString) const
	{
		String<Size> stringToReturn(*this);

		stringToReturn += aLiteralString;

		return stringToReturn;
	}

	StringTemplate
	String<Size> String<Size>::operator+(const String<Size>& aString) const
	{
		String<Size> stringToReturn(*this);

		stringToReturn += aString;
		return stringToReturn;
	}

	StringTemplate
	String<Size> String<Size>::operator+(const double aDouble) const
	{
		String<Size> stringToReturn(*this);

		stringToReturn += aDouble;
		return stringToReturn;
	}

	StringTemplate
	String<Size> String<Size>::operator+(const float aFloat) const
	{
		String<Size> stringToReturn(*this);

		stringToReturn += aFloat;
		return stringToReturn;
	}

	StringTemplate
	String<Size> String<Size>::operator+(const int aInt) const
	{
		String<Size> stringToReturn(*this);
		stringToReturn += aInt;

		return stringToReturn;
	}



	//Operator +=

	StringTemplate
	String<Size>& String<Size>::operator+=(const char* aLiteralString) //Kan inte addera sig sj�lv!
	{
		int i = 0;
		while (aLiteralString[i] != '\0')
		{
			if (myCurrentSize >= Size)
			{
				DEBUG_ASSERT(myCurrentSize < Size, "Size out of bounds");
				--myCurrentSize;
				break;
			}
			else
			{
				myArray[myCurrentSize] = aLiteralString[i];
				++myCurrentSize;
			}
			++i;
		}
		myArray[myCurrentSize] = '\0';

		return (*this);
	}

	StringTemplate
	String<Size>& String<Size>::operator+=(const String<Size>& aString)
	{
		return operator+=(&aString.myArray[0]);
	}

	StringTemplate
	String<Size>& String<Size>::operator+=(const double aDouble)
	{
		char literalString[20];

		sprintf_s(literalString, "%f", aDouble);

		return operator+=(literalString);
		return (*this);
	}

	StringTemplate
	String<Size>& String<Size>::operator+=(const float aFloat)
	{
		char literalString[20];

		sprintf_s(literalString, "%f", aFloat);

		return operator+=(literalString);
	}

	StringTemplate
	String<Size>& String<Size>::operator+=(const int aInt)
	{
		int copy = aInt;
		int currentSize = 0;
		char litteralString[Size];
		
		do
		{
			assert(currentSize + myCurrentSize < Size && "Size out of bounds");
		
			litteralString[currentSize++] = IntToChar(copy % 10);
		
			copy /= 10;
		} while (copy != 0);
		
		--myCurrentSize;
		for (int i = currentSize - 1; i >= 0; --i)
		{
			myArray[myCurrentSize++] = litteralString[i];
		}
		
		myArray[myCurrentSize++] = '\0';
		return (*this);
	}



	//Operator ==

	StringTemplate
	bool String<Size>::operator==(const String& aString) const
	{
		if (aString.myCurrentSize == myCurrentSize)
		{
			for (int i = 0; i < myCurrentSize; ++i)
			{
				if (aString.myArray[i] != myArray[i])
				{
					return false;
				}
			}
			return true;
		}

		return false;
	}



	//Operator =

	StringTemplate
	void String<Size>::operator=(const String& aString)
	{
		for (int i = 0; i < aString.myCurrentSize + 1; ++i)
		{
			myArray[i] = aString.myArray[i];
		}

		myCurrentSize = aString.myCurrentSize;
	}

	StringTemplate
	void String<Size>::operator=(const char* aLiteralString)
	{
		int i = 0;
		for (; i < Size; ++i)
		{
			myArray[i] = aLiteralString[i];

			if (aLiteralString[i] == '\0')
			{
				break;
			}
		}

		myCurrentSize = i;
		DEBUG_ASSERT(i < Size, "Size out of bounds");
	}


	StringTemplate
	String<Size> String<Size>::SubStr(const int aIndex, const int aLenght) const
	{
		DEBUG_ASSERT(aIndex >= 0, aIndex < myCurrentSize && "Index out of bounds");
		DEBUG_ASSERT(aLenght > 0, "Lenght cannot be less than 1");

		aLenght = min(myCurrentSize - aIndex, aLenght);
		char charArray[Size];

		for (int i = 0; i < aLenght; ++i)
		{
			char x = myArray[aIndex + i];
			charArray[i] = myArray[aIndex + i];
		}
		charArray[aLenght] = '\0';

		return String<Size>(charArray);
	}

	StringTemplate
	String<Size>& String<Size>::SetAsSubStr(const int aIndex, const int aLenght)
	{
		DEBUG_ASSERT(aIndex >= 0, aIndex < myCurrentSize && "Index out of bounds");
		DEBUG_ASSERT(aLenght > 0, "Lenght cannot be less than 1");

		aLenght = min(myCurrentSize - aIndex, aLenght);
		for (int i = 0; i < aLenght; ++i)
		{
			myArray[i] = myArray[aIndex + i];
		}
		myArray[aLenght] = '\0';
		myCurrentSize = aLenght;

		return (*this);
	}

	StringTemplate
	const char* String<Size>::c_str() const
	{
		return &myArray[0];
	}

	StringTemplate
	int String<Size>::Lenght() const
	{
		return myCurrentSize;
	}


	//Operator []

	StringTemplate
	char& String<Size>::operator[](const int aIndex)
	{
		DEBUG_ASSERT(aIndex >= 0, aIndex < myCurrentSize && "Index out of bounds");

		return myArray[aIndex];
	}

	StringTemplate
	char& String<Size>::operator[](const int aIndex) const
	{
		DEBUG_ASSERT(aIndex >= 0, aIndex < myCurrentSize && "Index out of bounds");

		return myArray[aIndex];
	}


	StringTemplate
	int String<Size>::Find(const char* aLiteralString) const
	{
		DEBUG_ASSERT(myCurrentSize > 0, "Size is equal to zero!");

		unsigned int size = strlen(aLiteralString);

		if(size > myCurrentSize) 
		{
			return -1;
		}
		std::map<char, unsigned int>table;

		for (unsigned int c = 0; c < size - 1; ++c)
			table.insert(std::pair<char, unsigned int>(aLiteralString[c], size - c - 1));

		if (table.find(aLiteralString[size]) == table.end())
		{
			table.insert(std::pair<char, unsigned int>(aLiteralString[size - 1], size));
		}

		int i = 0;
		unsigned char success = 0;

		while (static_cast<unsigned int>(i) <= myCurrentSize - size) // vi har inte flyttat ordet utanf�r
		{
			success = 0;

			for (int j = size - 1; j >= 0; --j) // r�knar bakifr�n p� str�ngen
			{
				if (aLiteralString[j] != myArray[j + i]) //om en inte st�mmer
				{
					success = 0;
					auto it = table.find(aLiteralString[j]);				
					i += MAX(1, (int)(it._Mynode()->_Myval.second - j));
					break;
				}
				else
				{
					success = 1;
				}
			}

			if (success == 1)
			{
				return i;
			}
		}

		return -1;
	}

	//Private methods

	StringTemplate
	char String<Size>::IntToChar(int aInt)
	{
		char min = '0';
		char max = '9';

		char charNumber = min + aInt;

		if (charNumber > max)
		{
			return '\0';
		}
		return charNUmber;
	}
}

namespace CU = CommonUtilities;
using stringSmall = CommonUtilities::String<32>;
using string = CommonUtilities::String<128>;
using stringLong = CommonUtilities::String<256>;