#include "stdafx.h"
#include "EffectContainer.h"
#include "EffectText2D.h"
#include "EffectText3D.h"


EffectContainer::EffectContainer()
{
}

EffectContainer::~EffectContainer()
{
}


Effect* EffectContainer::GetEffect(const eEffectType anEffectType)
{
	if (myEffects.find(anEffectType) == myEffects.end())
	{
		Effect* newEffect = GetEffectFromType(anEffectType);
		myEffects.insert(std::make_pair(anEffectType, newEffect));
	}
	return myEffects.at(anEffectType);
}



//Private methods

Effect* EffectContainer::GetEffectFromType(const eEffectType anEffectType)
{
	Effect* newEffect(nullptr);

	switch (anEffectType)
	{
		case(eEffectType::VertexColored) :
		{	
			newEffect = new Effect();
			newEffect->Init("Data/Shaders/VertexColorShader.fx");
			break;
		}
		case(eEffectType::UnTextured) :
		{
			newEffect = new Effect();
			newEffect->Init("Data/Shaders/NoTextureShader.fx");
			break;
		}
		case(eEffectType::Textured) :
		{
			newEffect = new Effect();
			newEffect->Init("Data/Shaders/DefaultShader.fx");
			break;
		}
		case(eEffectType::Card) :
		{
			newEffect = new Effect();
			newEffect->Init("Data/Shaders/CardShader.fx");
			break;
		}
		case(eEffectType::Sprite) :
		{
			Effect2D* spriteEffect = new Effect2D();
			spriteEffect->Init("Data/Shaders/SpriteShader.fx");

			newEffect = spriteEffect;
			break;
		}
		case(eEffectType::Text2D) :
		{
			EffectText2D* textEffect = new EffectText2D();
			textEffect->Init("Data/Shaders/TextShader2D.fx");

			newEffect = textEffect;
			break;
		}
		case(eEffectType::Text3D) :
		{
			EffectText3D* textEffect = new EffectText3D();
			textEffect->Init("Data/Shaders/TextShader3D.fx");

			newEffect = textEffect;
			break;
		}
		default:
		{
			delete newEffect;
			newEffect = nullptr;
		}
	}

	return newEffect;
}