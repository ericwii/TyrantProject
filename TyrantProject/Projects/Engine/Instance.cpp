#include "stdafx.h"
#include "Instance.h"
#include "Model.h"


Instance::Instance() : myModel(nullptr)
{
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
	myInstances.Allocate(40);
}

void Instance::Init(Model * aModel, CU::GrowingArray<Instance*> someInstaceChildren, CU::Matrix44<float> anOrientation)
{
	myModel = aModel;
	myOrientation = anOrientation;
	myInstances.Allocate(40);
	myInstances = someInstaceChildren;
}

void Instance::Render(bool aRenderChildren, unsigned int aPassIndex)
{
	DEBUG_ASSERT(myModel != nullptr, "Cannot render an instance without a model");
	
	myModel->Render(myOrientation, aPassIndex);

	if (aRenderChildren)
	{
		for (unsigned short i = 0; i < myInstances.Size(); ++i)
		{
			myInstances[i]->Render(aRenderChildren, aPassIndex);
		}
	}
}


void Instance::SetPosition(Vector3<float> aPosition)
{
	myOrientation.SetPosition(aPosition);
	for (unsigned short i = 0; i < myInstances.Size(); i++)
	{
		myInstances[i]->SetPosition(aPosition);
	}
}

void Instance::SetOrientation(CU::Matrix44<float> anOrientation)
{
	myOrientation = anOrientation;
	for (unsigned short i = 0; i < myInstances.Size(); i++)
	{
		myInstances[i]->SetOrientation(anOrientation);
	}
}
