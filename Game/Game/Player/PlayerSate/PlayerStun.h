#pragma once
#include "PlayerState.h"

class CPlayerStun : public IPlayerState
{
public:
	void Init()override;

	void Update()override;
private:
	float m_timer = 0.0f;//���Ԃ�}��ϐ�(�P�ʂ͕b
};