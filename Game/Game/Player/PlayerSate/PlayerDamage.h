#pragma once
#include "PlayerState.h"
//�v���C���[���_���[�W���󂯂��Ƃ��̃X�e�[�g

class CPlayerDamage : public IPlayerState
{
public:
	void Init()override;

	void Update()override;

	//�󒆂̃_���[�W�t���O�擾
	bool GetIsSky()
	{
		return m_isSky;
	}
private:
	void Rotation();
private:
	CVector3	m_airDamageVec;
	bool		m_isSky = false;	//�󒆂Ń_���[�W���󂯂���
};

