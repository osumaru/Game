#pragma once

#include "Number.h"

class DamegeNumber : public GameObject
{
public:
	void Init();

	void Update();

	void Draw();

private:
	Number* m_number[3];
	Vector2 m_numPos;
	Vector2 m_numSize;
};