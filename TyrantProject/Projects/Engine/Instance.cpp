#include "stdafx.h"
#include "Instance.h"
#include "Model.h"
#include "Text3D.h"


Instance::Instance() : myModel(nullptr)
{
	myInstances.Allocate(4);
	myTexts.Allocate(4);
}

Instance::Instance(Model* aModel, CU::Matrix44<float> anOrientation) : 
	myModel(aModel), myOrientation(anOrientation), myOriginalOrientation(anOrientation)
{
}

Instance::~Instance()
{
}

void Instance::Init(Model * aModel, CU::Matrix44<float> anOrientation)
{
	myModel = aModel;
	myOrientation = anOrientation;
	myOriginalOrientation = anOrientation;
}

void Instance::Init(Model * aModel, CU::GrowingArray<Instance*> someInstaceChildren, CU::Matrix44<float> anOrientation)
{
	myModel = aModel;
	myOrientation = anOrientation;
	myOriginalOrientation = anOrientation;
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
	Vector3<float> deltaPosition = aPosition - myOrientation.GetPosition();
	myOrientation.SetPosition(aPosition);

	Vector3<float> currentPosition;
	for (unsigned short i = 0; i < myInstances.Size(); i++)
	{
		currentPosition = myInstances[i]->GetPosition();
		myInstances[i]->SetPosition(currentPosition + deltaPosition);
	}

	for (unsigned short i = 0; i < myTexts.Size(); ++i)
	{
		currentPosition = myTexts[i]->GetPosition();

		myTexts[i]->SetPosition(currentPosition + deltaPosition);
	}
}

void Instance::SetOrientation(CU::Matrix44<float> anOrientation)
{
	CU::Matrix44<float> inverse(anOrientation.GetInverse());

	CU::Matrix44<float> currentOrientation;
	for (unsigned short i = 0; i < myInstances.Size(); i++)
	{
		currentOrientation = myInstances[i]->GetOriginalOrientation();
		myInstances[i]->SetOrientation(currentOrientation * inverse);
	}

	for (unsigned short i = 0; i < myTexts.Size(); ++i)
	{
		currentOrientation = myTexts[i]->GetOriginalOrientation();
		myTexts[i]->SetOrientation(currentOrientation * inverse);
	}

	myOrientation = anOrientation;
}


void Instance::AddChild(Instance* anInstance)
{
	anInstance->SetCurrentOrientationAsOriginal();
	CU::Matrix44<float> orientation = myOrientation;
	orientation *= anInstance->GetOrientation();
	anInstance->SetOrientation(orientation);
	myInstances.Add(anInstance);
}

void Instance::AddChild(Text3D* aText)
{
	aText->SetOrientation(aText->GetOrientation() * myOrientation.GetInverse());
	myTexts.Add(aText);
}

void Instance::RemoveChild(Instance* anInstance)
{
	myInstances.RemoveNonCyclic(anInstance);
}

void Instance::RemoveChild(Text3D* aText)
{
	myTexts.RemoveNonCyclic(aText);
}