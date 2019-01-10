#pragma once
#include "PlayerState.h"

class CPlayerAvoidance: public IPlayerState
{
public:
	//������
	void Init()override;

	//�X�V����
	void Update()override;

	//�ړ�����
	void Move();

	//��]
	void Rotation();
private:
	const CMatrix* m_pBoneMat;	//�{�[���̍s��̃|�C���^
	float	m_fallSpeed = 0.0f;
};

