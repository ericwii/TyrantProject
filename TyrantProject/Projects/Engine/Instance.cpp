#include "stdafx.h"
#include "Instance.h"
#include "Model.h"


Instance::Instance() : myModel(nullptr)
{
	myInstances.Allocate(4);
	myTexts.Allocate(4);
}

Instance::Instance(Model* aModel, CU::Matrix44<float> anOrientation) : myModel(aModel), myOrientation(anOrientation)
{
}

Instance::~Instance()
{
}

void Instance::Init(Model * aModel, CU::Matrix44<float> anOrientation)
{
	myModel = aModel;
	myOrientation = anOrientation;
}

void Instance::Init(Model * aModel, CU::GrowingArray<Instance*> someInstaceChildren, CU::Matrix44<float> anOrientation)
{
	myModel = aModel;
	myOrientation = anOrientation;
	myInstances = someInstaceChildren;
}

void Instance::Render(bool aRenderChildren, unsigned int aPassIndex)
{
	DEBUG_ASSERT(myModel != nullptr, "Cannot render an instance without a model");
	
	myModel->Render(myOrientation, aPassIndex);

	if (aRenderChildren == true)
	{
		for (unsigned short i = 0; i < myInstances.Size(); ++i)
		{
			myInstances[i]->Render(aRenderChildren);
		}

		for (unsigned short i = 0; i < myTexts.Size(); ++i)
		{
			myTexts[i]->Render();
		}
	}
}


void Instance::SetPosition(Vector3<float> aPosition)
{
	myOrientation.SetPosition(aPosition);

	Vector3<float> currentPosition;
	for (unsigned short i = 0; i < myInstances.Size(); ++i)
	{
		currentPosition = myInstances[i]->GetPosition();
		myInstances[i]->SetPosition(currentPosition + aPosition);
	}

	for (unsigned short i = 0; i < myTexts.Size(); ++i)
	{
		currentPosition = myTexts[i]->GetPosition();
		currentPosition += aPosition;
		myTexts[i]->SetPosition(currentPosition.AsVector2());
	}
}

void Instance::SetOrientation(CU::Matrix44<float> anOrientation)
{
	myOrientation = anOrientation;

	CU::Matrix44<float> currentOrientation;
	for (unsigned short i = 0; i < myInstances.Size(); i++)
	{
		currentOrientation = myInstances[i]->GetOrientation();
		myInstances[i]->SetOrientation(currentOrientation * anOrientation);
	}

	Vector2<float> currentPosition;
	for (unsigned short i = 0; i < myTexts.Size(); ++i)
	{
		currentPosition = myTexts[i]->GetPosition();
		currentPosition += anOrientation.GetPosition().AsVector2();
		myTexts[i]->SetPosition(currentPosition);
	}
}


void Instance::AddChild(Instance* anInstance)
{
	CU::Matrix44<float> orientation = myOrientation;
	orientation *= anInstance->GetOrientation();
	anInstance->SetOrientation(orientation);
	myInstances.Add(anInstance);
}

void Instance::AddChild(Text* aText)
{
	Vector2<float> position(0.5f, 0.5f);
	position += aText->GetPosition();
	position += myOrientation.GetPosition().AsVector2();
	aText->SetPosition(position);
	myTexts.Add(aText);
}

void Instance::RemoveChild(Instance* anInstance)
{
	myInstances.RemoveNonCyclic(anInstance);
}

void Instance::RemoveChild(Text* aText)
{
	myTexts.RemoveNonCyclic(aText);
}