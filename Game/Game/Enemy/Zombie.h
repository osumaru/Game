#pragma once

#include "Enemy/IEnemy.h"

class Zombie : public IEnemy
{
public:
	void Init(CVector3 position);

	void Update();

	void Draw();
};