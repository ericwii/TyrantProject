#pragma once
#include "VertexStructs.h"
#include "ShaderBufferStructs.h"

#define TEXT_MAX_CHARACTER_COUNT 64

class TextFont;

enum class eTextPositioning
{
	eLeft,
	eRight,
	eMiddle
};

class Text3D
{
public:
	Text3D();
	Text3D(const Text3D& aText);
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
	void SetAlpha(float anAlpha);

	inline const string& GetText() const;
	inline const CU::Matrix44<float>& GetOrientation() const;
	inline const CU::Matrix44<float>& GetOriginalOrientation() const;
	inline const Vector3<float> GetPosition() const;
	inline void SetCharacterSpace(float aSpace);
	inline void SetTextPositioning(eTextPositioning aTextPositionEnum);

	inline void SetCurrentOrientationAsOriginal();

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
	CU::Matrix44<float> myOriginalOrientation;
	Vector4<float> myColor;
	Vector2<float> myCharacterScale;
	ID3D11InputLayout* myVertexLayout;
	TextFont* myFont;
	float myCharacterSpace;
	eTextPositioning myTextPositioning;
};

inline const CU::Matrix44<float>& Text3D::GetOriginalOrientation() const
{
	return myOriginalOrientation;
}

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

inline const string& Text3D::GetText() const
{
	return myText;
}

inline void Text3D::SetTextPositioning(eTextPositioning aTextPositionEnum)
{
	myTextPositioning = aTextPositionEnum;
}

inline void Text3D::SetCurrentOrientationAsOriginal()
{
	myOriginalOrientation = myOrientation;
}