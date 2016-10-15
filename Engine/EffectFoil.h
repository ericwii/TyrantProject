#pragma once
#include "Effect.h"

class EffectFoil : public Effect
{
public:
	EffectFoil();
	~EffectFoil();

	bool Init(const string& aEffectFile);
	void Update() override;

private:

};

