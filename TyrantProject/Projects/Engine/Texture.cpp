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
	else
	{
		ID3D11Resource* resourcePtr;
		ID3D11Texture2D* texturePtr;
		myShaderResourceView->GetResource(&resourcePtr);
		hr = resourcePtr->QueryInterface<ID3D11Texture2D>(&texturePtr);

		if (SUCCEEDED(hr))
		{
			D3D11_TEXTURE2D_DESC desc;
			texturePtr->GetDesc(&desc);

			myDimensions.Set(static_cast<float>(desc.Width), static_cast<float>(desc.Height));

			resourcePtr->Release();
			texturePtr->Release();
		}
		else
		{
			DEBUG_ASSERT(false, "Failed to get texture from resource view");
		}
	}
	return true;
}