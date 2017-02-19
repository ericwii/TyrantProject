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
	
	Card* currentCard;
	for (int i = 0; i < anAttacker->myAssaultCards.Size(); ++i)
	{
		currentCard = anAttacker->myAssaultCards[i];
		if (currentCard->GetCooldown() < 1)
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

			if (aDefender->myAssaultCards.Size() > i)
			{
				aDefender->myAssaultCards[i]->TakeDamage(currentCard->GetAttack());
			}
			else
			{
				aDefender->myComander->TakeDamage(currentCard->GetAttack());
			}
		}
	}

	aDefender;
}