#include "stdafx.h"
#include "Texture.h"

#include <D3DX11tex.h>

Texture::Texture() : myShaderResourceView(nullptr)
{
}

Texture::~Texture()
{
}


bool Texture::LoadTexture(const string& aFileName)
{
	myFileName = aFileName;

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(GET_DIRECTX().GetDevice(), aFileName.c_str(), 0, 0, &myShaderResourceView, 0);
	if (FAILED(hr))
	{
		string errorMessage = "Failed to load texture: '";
		errorMessage += aFileName + "'";
		DEBUG_ASSERT(false, errorMessage.c_str());
		return false;
	}
	return true;
}