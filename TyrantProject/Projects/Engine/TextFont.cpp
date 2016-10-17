#include "stdafx.h"
#include "TextFont.h"


TextFont::TextFont() : myTextEffect(nullptr)
{
}

TextFont::~TextFont()
{
}


bool TextFont::Init(Effect* aTextEffect, const string& aTextureFilepath, float aTextureWidth, float aTextureHeight)
{
	mySurface.SetEffect(aTextEffect);
	if (mySurface.AddTexture("AlbedoTexture", aTextureFilepath) == false)
	{
		return false;
	}

	myTextEffect = aTextEffect;
	myTextureSize.x = aTextureWidth;
	myTextureSize.y = aTextureHeight;
	myCharacterSize.x = aTextureWidth / 16;
	myCharacterSize.y = aTextureHeight / 16;
	myNormalizedCharacterSize = myCharacterSize / myTextureSize;


	mySurface.SetPrimologyType(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	myCharacters['@'] = GetCharacterUVFromGrid(0, 4);
	myCharacters['A'] = GetCharacterUVFromGrid(1, 4);
	myCharacters['B'] = GetCharacterUVFromGrid(2, 4);
	myCharacters['C'] = GetCharacterUVFromGrid(3, 4);
	myCharacters['D'] = GetCharacterUVFromGrid(4, 4);
	myCharacters['E'] = GetCharacterUVFromGrid(5, 4);
	myCharacters['F'] = GetCharacterUVFromGrid(6, 4);
	myCharacters['G'] = GetCharacterUVFromGrid(7, 4);
	myCharacters['H'] = GetCharacterUVFromGrid(8, 4);
	myCharacters['I'] = GetCharacterUVFromGrid(9, 4);
	myCharacters['J'] = GetCharacterUVFromGrid(10, 4);
	myCharacters['K'] = GetCharacterUVFromGrid(11, 4);
	myCharacters['L'] = GetCharacterUVFromGrid(12, 4);
	myCharacters['M'] = GetCharacterUVFromGrid(13, 4);
	myCharacters['N'] = GetCharacterUVFromGrid(14, 4);
	myCharacters['O'] = GetCharacterUVFromGrid(15, 4);
	myCharacters['P'] = GetCharacterUVFromGrid(0, 5);
	myCharacters['Q'] = GetCharacterUVFromGrid(1, 5);
	myCharacters['R'] = GetCharacterUVFromGrid(2, 5);
	myCharacters['S'] = GetCharacterUVFromGrid(3, 5);
	myCharacters['T'] = GetCharacterUVFromGrid(4, 5);
	myCharacters['U'] = GetCharacterUVFromGrid(5, 5);
	myCharacters['V'] = GetCharacterUVFromGrid(6, 5);
	myCharacters['W'] = GetCharacterUVFromGrid(7, 5);
	myCharacters['X'] = GetCharacterUVFromGrid(8, 5);
	myCharacters['Y'] = GetCharacterUVFromGrid(9, 5);
	myCharacters['Z'] = GetCharacterUVFromGrid(10, 5);
	myCharacters['Å'] = GetCharacterUVFromGrid(5, 12);
	myCharacters['Ä'] = GetCharacterUVFromGrid(4, 12);
	myCharacters['Ö'] = GetCharacterUVFromGrid(6, 13);

	myCharacters['a'] = GetCharacterUVFromGrid(1, 6);
	myCharacters['b'] = GetCharacterUVFromGrid(2, 6);
	myCharacters['c'] = GetCharacterUVFromGrid(3, 6);
	myCharacters['d'] = GetCharacterUVFromGrid(4, 6);
	myCharacters['e'] = GetCharacterUVFromGrid(5, 6);
	myCharacters['f'] = GetCharacterUVFromGrid(6, 6);
	myCharacters['g'] = GetCharacterUVFromGrid(7, 6);
	myCharacters['h'] = GetCharacterUVFromGrid(8, 6);
	myCharacters['i'] = GetCharacterUVFromGrid(9, 6);
	myCharacters['j'] = GetCharacterUVFromGrid(10, 6);
	myCharacters['k'] = GetCharacterUVFromGrid(11, 6);
	myCharacters['l'] = GetCharacterUVFromGrid(12, 6);
	myCharacters['m'] = GetCharacterUVFromGrid(13, 6);
	myCharacters['n'] = GetCharacterUVFromGrid(14, 6);
	myCharacters['o'] = GetCharacterUVFromGrid(15, 6);
	myCharacters['p'] = GetCharacterUVFromGrid(0, 7);
	myCharacters['q'] = GetCharacterUVFromGrid(1, 7);
	myCharacters['r'] = GetCharacterUVFromGrid(2, 7);
	myCharacters['s'] = GetCharacterUVFromGrid(3, 7);
	myCharacters['t'] = GetCharacterUVFromGrid(4, 7);
	myCharacters['u'] = GetCharacterUVFromGrid(5, 7);
	myCharacters['v'] = GetCharacterUVFromGrid(6, 7);
	myCharacters['w'] = GetCharacterUVFromGrid(7, 7);
	myCharacters['x'] = GetCharacterUVFromGrid(8, 7);
	myCharacters['y'] = GetCharacterUVFromGrid(9, 7);
	myCharacters['z'] = GetCharacterUVFromGrid(10, 7);
	myCharacters['å'] = GetCharacterUVFromGrid(5, 14);
	myCharacters['ä'] = GetCharacterUVFromGrid(4, 14);
	myCharacters['ö'] = GetCharacterUVFromGrid(6, 15);


	myCharacters['0'] = GetCharacterUVFromGrid(0, 3);
	myCharacters['1'] = GetCharacterUVFromGrid(1, 3);
	myCharacters['2'] = GetCharacterUVFromGrid(2, 3);
	myCharacters['3'] = GetCharacterUVFromGrid(3, 3);
	myCharacters['4'] = GetCharacterUVFromGrid(4, 3);
	myCharacters['5'] = GetCharacterUVFromGrid(5, 3);
	myCharacters['6'] = GetCharacterUVFromGrid(6, 3);
	myCharacters['7'] = GetCharacterUVFromGrid(7, 3);
	myCharacters['8'] = GetCharacterUVFromGrid(8, 3);
	myCharacters['9'] = GetCharacterUVFromGrid(9, 3);
	myCharacters[':'] = GetCharacterUVFromGrid(10, 3);
	myCharacters[';'] = GetCharacterUVFromGrid(11, 3);
	myCharacters['<'] = GetCharacterUVFromGrid(12, 3);
	myCharacters['='] = GetCharacterUVFromGrid(13, 3);
	myCharacters['>'] = GetCharacterUVFromGrid(14, 3);
	myCharacters['?'] = GetCharacterUVFromGrid(15, 3);

	myCharacters[' '] = GetCharacterUVFromGrid(0, 2);
	myCharacters['!'] = GetCharacterUVFromGrid(1, 2);
	myCharacters['"'] = GetCharacterUVFromGrid(2, 2);
	myCharacters['#'] = GetCharacterUVFromGrid(3, 2);
	myCharacters['$'] = GetCharacterUVFromGrid(4, 2);
	myCharacters['%'] = GetCharacterUVFromGrid(5, 2);
	myCharacters['&'] = GetCharacterUVFromGrid(6, 2);
	myCharacters['\''] = GetCharacterUVFromGrid(7, 2);
	myCharacters['('] = GetCharacterUVFromGrid(8, 2);
	myCharacters[')'] = GetCharacterUVFromGrid(9, 2);
	myCharacters['*'] = GetCharacterUVFromGrid(10, 2);
	myCharacters['+'] = GetCharacterUVFromGrid(11, 2);
	myCharacters[','] = GetCharacterUVFromGrid(12, 2);
	myCharacters['-'] = GetCharacterUVFromGrid(13, 2);
	myCharacters['.'] = GetCharacterUVFromGrid(14, 2);
	myCharacters['/'] = GetCharacterUVFromGrid(15, 2);
	myCharacters['\\'] = GetCharacterUVFromGrid(12, 5);
	myCharacters['_'] = GetCharacterUVFromGrid(15, 5);
	myCharacters['|'] = GetCharacterUVFromGrid(12, 7);

	return true;
}




//Private methods

Vector2<float> TextFont::GetCharacterUVFromGrid(int x, int y)
{
	return Vector2<float>(
		(x * myCharacterSize.x) / myTextureSize.x, 
		(y * myCharacterSize.y) / myTextureSize.y);
}