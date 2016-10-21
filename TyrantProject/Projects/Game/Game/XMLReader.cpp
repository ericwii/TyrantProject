#include "stdafx.h"


XMLReader::XMLReader()
{
	myHasOpenedDoc = false;
	myDoc = nullptr;
}


XMLReader::~XMLReader()
{
	if (myDoc != nullptr)
	{
		delete myDoc;
		myDoc = nullptr;
	}
}

void XMLReader::OpenDocument(const std::string& aFilePath)
{
	delete myDoc;

	if (myDoc == nullptr)
	{
		myDoc = new tinyxml2::XMLDocument();
	}

	tinyxml2::XMLError error = myDoc->LoadFile(aFilePath.c_str());
	if (error == 0)
	{
		myHasOpenedDoc = true;
		myFilePath = aFilePath;
	}
	else
	{
		stringLong errorMessage = "Failed to open XML file: ";
		errorMessage += aFilePath.c_str();


#pragma region Error-Codes
		switch (error)
		{
			case tinyxml2::XML_NO_ATTRIBUTE:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_NO_ATTRIBUTE";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_WRONG_ATTRIBUTE_TYPE:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_WRONG_ATTRIBUTE_TYPE";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_FILE_NOT_FOUND:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_FILE_NOT_FOUND";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_FILE_COULD_NOT_BE_OPENED";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_FILE_READ_ERROR:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_FILE_READ_ERROR";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_ELEMENT_MISMATCH:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_ELEMENT_MISMATCH";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_PARSING_ELEMENT:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_PARSING_ELEMENT";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_PARSING_ATTRIBUTE:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_PARSING_ATTRIBUTE";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_IDENTIFYING_TAG:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_IDENTIFYING_TAG";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_PARSING_TEXT:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_PARSING_TEXT";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_PARSING_CDATA:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_PARSING_CDATA";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_PARSING_COMMENT:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_PARSING_COMMENT";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_PARSING_DECLARATION:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_PARSING_DECLARATION";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_PARSING_UNKNOWN:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_PARSING_UNKNOWN";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_EMPTY_DOCUMENT:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_EMPTY_DOCUMENT";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_MISMATCHED_ELEMENT:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_MISMATCHED_ELEMENT";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_PARSING:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_PARSING";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_CAN_NOT_CONVERT_TEXT:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_CAN_NOT_CONVERT_TEXT";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_NO_TEXT_NODE:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_NO_TEXT_NODE";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			case tinyxml2::XML_ERROR_COUNT:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_ERROR_COUNT";
				ASSERT(false, errorMessage.c_str());
				break;
			}
			default:
			{
				errorMessage += "\nError: ";
				errorMessage += "XML_UNREGOGNIZED_ERROR";
				ASSERT(false, errorMessage.c_str());
				break;
			}
		}
#pragma endregion

	}
}

void XMLReader::CloseDocument()
{
	if (myHasOpenedDoc == true)
	{
		myHasOpenedDoc = false;
		myFilePath = "";
		delete myDoc;
		myDoc = nullptr;
	}
}

std::string XMLReader::GetElementName(tinyxml2::XMLElement* aElement)
{
	if (myHasOpenedDoc == false)
	{
		ASSERT(false, "Tried to[GetElementName] before Opening the document");
	}

	return aElement->Name();
}

/*
---------------------------
Normal Find Operations
---------------------------
*/

tinyxml2::XMLElement* XMLReader::FindFirstChild(const std::string& aChildName)
{
	if (myHasOpenedDoc == false)
	{
		ASSERT(false, "[XMLReader]: Tried to [FindFirstChild] before Opening the document");
	}

	return myDoc->FirstChildElement(aChildName.c_str());
}

tinyxml2::XMLElement* XMLReader::FindFirstChild(tinyxml2::XMLElement* aParent) const
{
	if (myHasOpenedDoc == false)
	{
		ASSERT(false, "[XMLReader]: Tried to [FindFirstChild] before Opening the document");
	}

	return aParent->FirstChildElement();
}

tinyxml2::XMLElement* XMLReader::FindFirstChild(tinyxml2::XMLElement* aParent, const std::string& aChildName) const
{
	if (myHasOpenedDoc == false)
	{
		ASSERT(false, "[XMLReader]: Tried to [FindFirstChild] before Opening the document");
	}

	return aParent->FirstChildElement(aChildName.c_str());
}

tinyxml2::XMLElement* XMLReader::FindNextElement(const std::string& aElementName)
{
	if (myHasOpenedDoc == false)
	{
		ASSERT(false, "[XMLReader]: Tried to [FindNextElement] before Opening the document");
	}

	return myDoc->NextSiblingElement(aElementName.c_str());
}

tinyxml2::XMLElement* XMLReader::FindNextElement(tinyxml2::XMLElement* aPrevElement) const
{
	if (myHasOpenedDoc == false)
	{
		ASSERT(false, "[XMLReader]: Tried to [FindNextElement] before Opening the document");
	}

	return aPrevElement->NextSiblingElement();
}

tinyxml2::XMLElement* XMLReader::FindNextElement(tinyxml2::XMLElement* aPrevElement, const std::string& aElementName) const
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [FindNextElement] before Opening the document");

	return aPrevElement->NextSiblingElement(aElementName.c_str());
}



/*
---------------------------
Force Find Operations
---------------------------
*/

tinyxml2::XMLElement* XMLReader::ForceFindFirstChild(const std::string& aChildName)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [FindFirstChild] before Opening the document");

	DebugFirstChild(aChildName);

	return myDoc->FirstChildElement(aChildName.c_str());
}

tinyxml2::XMLElement* XMLReader::ForceFindFirstChild(tinyxml2::XMLElement* aParent) const
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [FindFirstChild] before Opening the document");

	DebugFirstChild(aParent);

	return aParent->FirstChildElement();
}

tinyxml2::XMLElement* XMLReader::ForceFindFirstChild(tinyxml2::XMLElement* aParent, const std::string& aChildName) const
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [FindFirstChild] before Opening the document");


	DebugFirstChild(aParent, aChildName);

	return aParent->FirstChildElement(aChildName.c_str());
}

tinyxml2::XMLElement* XMLReader::ForceFindNextElement(const std::string& aElementName)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [FindNextElement] before Opening the document");

	DebugNextElement(aElementName);

	return myDoc->NextSiblingElement(aElementName.c_str());

}

tinyxml2::XMLElement* XMLReader::ForceFindNextElement(tinyxml2::XMLElement* aPrevElement) const
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [FindNextElement] before Opening the document");

	DebugNextElement(aPrevElement);

	return aPrevElement->NextSiblingElement();
}

tinyxml2::XMLElement* XMLReader::ForceFindNextElement(tinyxml2::XMLElement* aPrevElement, const std::string& aElementName) const
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [FindNextElement] before Opening the document");

	DebugNextElement(aPrevElement, aElementName);

	return aPrevElement->NextSiblingElement(aElementName.c_str());
}



/*
---------------------------
Normal Read Operations
---------------------------
*/

bool XMLReader::ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const std::string& aAttributeToRead, std::string& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [ReadAttribute(string)] before Opening the document");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->FindAttribute(aAttributeToRead.c_str()) != 0)
	{
		aTargetVariable = aElementToReadFrom->Attribute(aAttributeToRead.c_str());
		return true;
	}

	return false;
}

bool XMLReader::ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const std::string& aAttributeToRead, int& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [ReadAttribute(int)] before Opening the document");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->QueryIntAttribute(aAttributeToRead.c_str(), &aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	return false;
}

bool XMLReader::ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const std::string& aAttributeToRead, float& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [ReadAttribute(float)] before Opening the document");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->QueryFloatAttribute(aAttributeToRead.c_str(), &aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	return false;
}

bool XMLReader::ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const std::string& aAttributeToRead, double& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [ReadAttribute(double)] before Opening the document");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->QueryDoubleAttribute(aAttributeToRead.c_str(), &aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	return false;
}

bool XMLReader::ReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const std::string& aAttributeToRead, bool& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [ReadAttribute(bool)] before Opening the document");

	if (aElementToReadFrom == nullptr)
		return false;

	if (aElementToReadFrom->QueryBoolAttribute(aAttributeToRead.c_str(), &aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	return false;
}



/*
---------------------------
Force Read Operations
---------------------------
*/

bool XMLReader::ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const std::string& aAttributeToRead, std::string& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [ForceReadAttribute(string)] before Opening the document");

	if (aElementToReadFrom->FindAttribute(aAttributeToRead.c_str()) != 0)
	{
		aTargetVariable = aElementToReadFrom->Attribute(aAttributeToRead.c_str());
		return true;
	}

	ASSERT(false, "Failed to [ForceReadAttribute(string)]");
	return false;
}

bool XMLReader::ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const std::string& aAttributeToRead, int& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [ForceReadAttribute(int)] before Opening the document");

	if (aElementToReadFrom->QueryIntAttribute(aAttributeToRead.c_str(), &aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	ASSERT(false, "Failed to [ForceReadAttribute(int)]");
	return false;
}

bool XMLReader::ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const std::string& aAttributeToRead, float& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [ReadAttribute(float)] before Opening the document");

	const tinyxml2::XMLError error = aElementToReadFrom->QueryFloatAttribute(aAttributeToRead.c_str(), &aTargetVariable);
	if (error == tinyxml2::XML_NO_ERROR)
		return true;

	ASSERT(false, "Failed to [ForceReadAttribute(float)]");
	return false;
}

bool XMLReader::ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const std::string& aAttributeToRead, double& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [ReadAttribute(double)] before Opening the document");

	if (aElementToReadFrom->QueryDoubleAttribute(aAttributeToRead.c_str(), &aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	ASSERT(false, "Failed to [ForceReadAttribute(double)]");
	return false;
}

bool XMLReader::ForceReadAttribute(const tinyxml2::XMLElement* aElementToReadFrom, const std::string& aAttributeToRead, bool& aTargetVariable)
{
	if (myHasOpenedDoc == false)
		ASSERT(false, "[XMLReader]: Tried to [ReadAttribute(bool)] before Opening the document");

	if (aElementToReadFrom->QueryBoolAttribute(aAttributeToRead.c_str(), &aTargetVariable) == tinyxml2::XML_NO_ERROR)
		return true;

	ASSERT(false, "Failed to [ForceReadAttribute(bool)]");
	return false;
}



/*
---------------------------
Debug Operations
---------------------------
*/
void XMLReader::DebugFirstChild(const std::string& aChildName)
{
	if (myDoc->FirstChildElement(aChildName.c_str()) == nullptr)
	{
		ASSERT(false, "Failed to [ForceFindFirstChild]");
	}
}

void XMLReader::DebugFirstChild(tinyxml2::XMLElement* aParent) const
{
	if (aParent->FirstChildElement() == nullptr)
	{
		ASSERT(false, "Failed to [ForceFindFirstChild]");
	}
}

void XMLReader::DebugFirstChild(tinyxml2::XMLElement* aParent, const std::string& aChildName) const
{
	if (aParent->FirstChildElement(aChildName.c_str()) == nullptr)
	{
		ASSERT(false, "Failed to [ForceFindFirstChild]");
	}
}

void XMLReader::DebugNextElement(const std::string& aChildName)
{
	if (myDoc->NextSiblingElement(aChildName.c_str()) == nullptr)
	{
		ASSERT(false, "Failed to [ForceFindNextElement]");
	}
}

void XMLReader::DebugNextElement(tinyxml2::XMLElement* aParent) const
{
	if (aParent->NextSiblingElement() == nullptr)
	{
		ASSERT(false, "Failed to [ForceFindNextElement]");
	}
}

void XMLReader::DebugNextElement(tinyxml2::XMLElement* aParent, const std::string& aChildName) const
{
	if (aParent->NextSiblingElement(aChildName.c_str()) == nullptr)
	{
		ASSERT(false, "Failed to [ForceFindNextElement]");
	}
}