#pragma once
#include "VertexStructs.h"
#include "ShaderBufferStructs.h"

#define TEXT_MAX_CHARACTER_COUNT 64

class TextFont;

class Text3D
{
public:
	Text3D();
	~Text3D();

	void Destroy();
	void Init(TextFont* aFont);
	void Render();

	void SetColor(const Vector4<float>& aColor);
	void SetOrientation(const CU::Matrix44<float>& anOrientation);
	void SetPosition(const Vector3<float>& aPosition);
	void SetCharacterScale(const Vector2<float>& aScale);
	void SetCharacterScale(float aScale);
	void SetText(const string& someText);

	inline const CU::Matrix44<float>& GetOrientation() const;
	inline const Vector3<float> GetPosition() const;
	inline void SetCharacterSpace(float aSpace);

private:
	void InitVertexBuffer();
	void InitInputLayout();
	void UpdateShaderVariables();
	void UpdateVertexBuffer(int aVertexCount);
	void DrawPass(unsigned int aPassIndex, unsigned int aVertexCount);

	CU::StaticArray<VertexPositionUV, TEXT_MAX_CHARACTER_COUNT> myVertexes;
	string myText;
	VertexBufferWrapper myVertexBuffer;
	CU::Matrix44<float> myOrientation;
	Vector4<float> myColor;
	Vector2<float> myCharacterScale;
	ID3D11InputLayout* myVertexLayout;
	TextFont* myFont;
	float myCharacterSpace;
};

inline const CU::Matrix44<float>& Text3D::GetOrientation() const
{
	return myOrientation;
}

inline const Vector3<float> Text3D::GetPosition() const
{
	return myOrientation.GetPosition();
}

inline void Text3D::SetCharacterSpace(float aSpace)
{
	myCharacterSpace = aSpace;
}