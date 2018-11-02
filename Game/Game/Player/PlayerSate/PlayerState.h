#pragma once
#include "stdafx.h"
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
	void SetPlayer(CPlayer* player)
	{
		m_pPlayer = player;
	}
protected:
	CPlayer*		m_pPlayer = nullptr;	//�v���C���[�̃C���X�^���X
};
