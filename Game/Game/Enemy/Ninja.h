/*
*	�E�҃N���X
*/

#pragma once

#include "Enemy/IEnemy.h"

class CNinja : public IEnemy
{
public:
	//�R���X�g���N�^
	CNinja();

	//�f�X�g���N�^
	~CNinja();

	//������
	//position	���W
	void Init(const CVector3& position) override;

	//�X�V�����O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�U��
	void Attack();

	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)override;

};