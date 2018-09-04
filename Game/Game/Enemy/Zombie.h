#pragma once

#include "Enemy/Enemy.h"

class Zombie : public IEnemy
{
public:
	void Init(CVector3 position) override;

	void Update() override;

	void Draw() override;
};