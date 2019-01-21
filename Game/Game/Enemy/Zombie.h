/*
*	�]���r�N���X
*/

#pragma once

#include "Enemy/IEnemy.h"

class CZombie : public IEnemy
{
public:
	//�R���X�g���N�^
	CZombie();

	//�f�X�g���N�^
	~CZombie();

	//������
	//position	���W
	void Init(const CVector3& position) override;

	//�X�V�����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�U��
	void Attack() override;

	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)override;
};