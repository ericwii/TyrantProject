#include "stdafx.h"
#include "EffectContainer.h"
#include "EffectText.h"
#include "EffectFoil.h"


EffectContainer::EffectContainer()
{
}

EffectContainer::~EffectContainer()
{
}


Effect* EffectContainer::GetEffect(const eEffectType3D anEffectType)
{
	if (my3DEffects.find(anEffectType) == my3DEffects.end())
	{
		Effect* newEffect = GetEffectFromType(anEffectType);
		my3DEffects.insert(std::make_pair(anEffectType, newEffect));
	}
	return my3DEffects.at(anEffectType);
}

Effect2D* EffectContainer::GetEffect(const eEffectType2D anEffectType)
{
	if (my2DEffects.find(anEffectType) == my2DEffects.end())
	{
		Effect2D* newEffect = GetEffectFromType(anEffectType);
		my2DEffects.insert(std::make_pair(anEffectType, newEffect));
	}
	return my2DEffects.at(anEffectType);
}



//Private methods

Effect* EffectContainer::GetEffectFromType(const eEffectType3D anEffectType)
{
	Effect* newEffect(nullptr);

	switch (anEffectType)
	{
		case(eEffectType3D::VertexColored) :
		{	
			newEffect = new Effect();
			newEffect->Init("Data/Shaders/VertexColorShader.fx");
			break;
		}
		case(eEffectType3D::UnTextured) :
		{
			newEffect = new Effect();
			newEffect->Init("Data/Shaders/NoTextureShader.fx");
			break;
		}
		case(eEffectType3D::Textured) :
		{
			newEffect = new Effect();
			newEffect->Init("Data/Shaders/DefaultShader.fx");
			break;
		}
		case(eEffectType3D::Textured_Foiled) :
		{
			EffectFoil* foilEffect = new EffectFoil();
			foilEffect->Init("Data/Shaders/FoilShader.fx");
			newEffect = foilEffect;
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

Effect2D* EffectContainer::GetEffectFromType(const eEffectType2D anEffectType)
{
	Effect2D* newEffect(nullptr);

	switch (anEffectType)
	{
		case(eEffectType2D::Text) :
		{
			EffectText* textEffect = new EffectText();
			textEffect->Init("Data/Shaders/DefaultTextShader.fx");

			newEffect = textEffect;
			break;
		}
		case(eEffectType2D::Sprite) :
		{
			ASSERT(false, "Add a shader for sprites please :)");
		}
		default:
		{
			delete newEffect;
			newEffect = nullptr;
		}
	}

	return newEffect;
}