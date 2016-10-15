#include "stdafx.h"
#include "Surface.h"
#include "Texture.h"
#include "Effect.h"

Surface::Surface() : myEffect(nullptr)
{
	myTextures.Allocate(2);
	myShaderVariables.Allocate(2);
}

Surface::~Surface()
{
}


void Surface::UpdateShaderVariables()
{
	GET_DIRECTX().GetDeviceContext()->IASetPrimitiveTopology(myPrimologyType);

	for (int i = 0; i < myShaderVariables.Size(); ++i)
	{
		if (myShaderVariables[i]->IsValid() == TRUE)
		{
			myShaderVariables[i]->SetResource(myTextures[i]->GetShaderView());
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

	myTextures.Add(temp);
	myShaderVariables.Add(tempShaderResourceVar);

	return true;
}