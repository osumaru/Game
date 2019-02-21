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
	//level		���x��
	void Init(int level) override;

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