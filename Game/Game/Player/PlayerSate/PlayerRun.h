#pragma once
#include"PlayerState.h"

class CPlayerRun	: public	IPlayerState
{
public:
	void Init()override;

	void Update()override;
private:
	float	m_timer = 0.0f;		//�^�C�}�[
	bool	m_isDash = false;	//�_�b�V�����Ă��邩
};

