#pragma once
#include "stdafx.h"
#include "../PlayerGetter.h"


class CPlayer;
//�v���C���[�̃X�e�[�g�̊��N���X

class IPlayerState
{
public:

	virtual ~IPlayerState() {}

	//�������֐�(�X�e�[�g���ς�����Ƃ������ɌĂяo�����֐�
	virtual void Init() {}
	
	//�X�V
	virtual void Update() = 0;

	//�v���C���[�̃C���X�^���X��ݒ�
	void SetPlayer(CPlayer* player, CPlayerGetter* playerGetter)
	{
		m_pPlayer = player;
		m_pPlayerGetter = playerGetter;
	}
protected:
	CPlayer*		m_pPlayer = nullptr;	//�v���C���[�̃C���X�^���X
	CPlayerGetter*	m_pPlayerGetter = nullptr;
};
