#pragma once
#include "PlayerState.h"
//�v���C���[���_���[�W���󂯂��Ƃ��̃X�e�[�g

class CPlayerDamage : public IPlayerState
{
public:
	void Init()override;

	void Update()override;
private:
	void Rotation();
private:
	CVector3 m_airDamageVec;
};

