#include "stdafx.h"
#include "CombatManager.h"
#include "Player.h"
#include "AnimationStack.h"

CombatManager* CombatManager::instance = new CombatManager();
AnimationData attackAnimation
{
	"Data/Textures/attackAnimation.png",
		10,
		2,
		30.f,
		false
};


CombatManager::CombatManager()
{
}

CombatManager::~CombatManager()
{
}


void CombatManager::DoCombat(Player* anAttacker, Player* aDefender)
{
	Vector3<float> position;
	Vector2<float> size(2.f, 2.f);
	for (int i = 0; i < anAttacker->myAssaultCards.Size(); ++i)
	{
		position = anAttacker->myAssaultCards[i]->GetOrientation().GetPosition();

		if (position.y < 0)
		{
			AnimationStack::AddAnimation(attackAnimation, position, size);
		}
		else
		{
			AnimationStack::AddAnimation(attackAnimation, position, size, PI);
		}
	}

	aDefender;
}