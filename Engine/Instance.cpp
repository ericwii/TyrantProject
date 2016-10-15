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


void Instance::Init(Model* aModel, CU::Matrix44<float> anOrientation)
{
	myModel = aModel;
	myOrientation = anOrientation;
}

void Instance::Render()
{
	DEBUG_ASSERT(myModel != nullptr, "Cannot render an instance without a model");

	myModel->Render(myOrientation);
}