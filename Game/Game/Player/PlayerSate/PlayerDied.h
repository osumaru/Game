#pragma once
#include "PlayerState.h"
//�v���C���[�����񂾂Ƃ��m�X�e�[�g

class CPlayerDied : public IPlayerState
{
public:
	void Init()override;

	void Update()override;
};

