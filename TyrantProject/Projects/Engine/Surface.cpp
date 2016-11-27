#include "stdafx.h"
#include "Surface.h"
#include "Texture.h"

Surface::Surface() : myEffect(nullptr)
{
	myData.Allocate(2);
}

Surface::~Surface()
{
}


void Surface::UpdateShaderVariables()
{
	GET_DIRECTX().GetDeviceContext()->IASetPrimitiveTopology(myPrimologyType);


	SurfaceData* currentData(nullptr);
	for (int i = 0; i < myData.Size(); ++i)
	{
		currentData = &myData[i];
		if (currentData->shaderVariable->IsValid() == TRUE)
		{
			currentData->shaderVariable->SetResource(currentData->texture->GetShaderView());
		}
	}
}


bool Surface::AddTexture(const string& aShaderVariableName, const string& aTextureFileName)
{
	Texture* temp = Engine::GetInstance()->GetTextureContainer().GetTexture(aTextureFileName);
	ID3DX11EffectShaderResourceVariable* tempShaderResourceVar = myEffect->GetEffect()->GetVariableByName(aShaderVariableName.c_str())->AsShaderResource();

	if (temp == nullptr)
	{
		DEBUG_ASSERT(false, "Failed to create texture for surface");
		return false;
	}

	if (tempShaderResourceVar->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Shader resource variable for surface is not valid.");
		return false;
	}

	myData.Add(SurfaceData(tempShaderResourceVar, temp, aShaderVariableName));

	return true;
}