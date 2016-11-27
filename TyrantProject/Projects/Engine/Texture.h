#pragma once

class Texture
{
public:
	Texture();
	~Texture();

	bool LoadTexture(const string& aFileName);

	inline const string& GetFileName() const;
	inline ID3D11ShaderResourceView* GetShaderView();

	inline float GetWidth();
	inline float GetHeight();

private:
	string myFileName;
	Vector2<float> myDimensions;
	ID3D11ShaderResourceView* myShaderResourceView;
};

inline const string& Texture::GetFileName() const
{
	return myFileName;
}

inline ID3D11ShaderResourceView* Texture::GetShaderView()
{
	return myShaderResourceView;
}

inline float Texture::GetWidth()
{
	return myDimensions.x;
}

inline float Texture::GetHeight()
{
	return myDimensions.y;
}