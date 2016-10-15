#pragma once

class Texture
{
public:
	Texture();
	~Texture();

	bool LoadTexture(const string& aFileName);

	inline const string& GetFileName() const;
	inline ID3D11ShaderResourceView* GetShaderView();

private:
	string myFileName;
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