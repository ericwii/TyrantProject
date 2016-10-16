#pragma once
class AbilityBase
{
public:
	AbilityBase();
	~AbilityBase();

	virtual void OnPlay();
	virtual void OnDeath();
	virtual void OnAttacked();
	virtual void OnDamaged();
	virtual void OnAbilityTageted();
	virtual void OnKill();

protected:
	char myAbilityValue;
	bool myTargetAll;
};

