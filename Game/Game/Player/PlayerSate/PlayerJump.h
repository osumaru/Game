#pragma once
#include "PlayerState.h"
//�v���C���[���W�����v����Ƃ��̃X�e�[�g
class CPlayerJump: public IPlayerState
{
public:
	void Init()override;

	void Update()override;
private:
	const float LIMIT_MOVE_SPEED = 20.0f;
};

