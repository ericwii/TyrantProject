#pragma once
#include "VertexStructs.h"
#include "ShaderBufferStructs.h"
#include "../CommonUtilities/StaticArray.h"

#define TEXT_MAX_CHARACTER_COUNT 64

class TextFont;

class Text2D
{
public:
	Text2D();
	~Text2D();

	void Destroy();
	void Init(TextFont* aFont);
	void Render();

	void SetColor(const Vector4<float>& aColor);
	void SetPosition(const Vector2<float>& aPosition);
	void SetCharacterScale(const Vector2<float>& aScale);
	void SetCharacterScale(float aScale);
	void SetText(const string& someText);

	inline const Vector2<float>& GetPosition() const;
	inline void SetCharacterSpace(float aSpace);

private:
	void InitVertexBuffer();
	void InitInputLayout();
	void UpdateShaderVariables();
	void UpdateVertexBuffer(int aVertexCount);
	void DrawPass(unsigned int aPassIndex, unsigned int aVertexCount);

	CU::StaticArray<VertexPositionUV, TEXT_MAX_CHARACTER_COUNT> myVertexes;
	VertexBufferWrapper myVertexBuffer;
	string myText;
	Vector4<float> myColor;
	Vector2<float> myCharacterScale;
	Vector2<float> myPosition;
	ID3D11InputLayout* myVertexLayout;
	TextFont* myFont;
	float myCharacterSpace;
};

inline const Vector2<float>& Text2D::GetPosition() const
{
	return myPosition;
}

inline void Text2D::SetCharacterSpace(float aSpace)
{
	myCharacterSpace = aSpace;
}