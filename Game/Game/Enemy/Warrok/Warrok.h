/*
*	�E�H�[���b�N�N���X
*/

#pragma once

#include "Enemy/IEnemy.h"

class CWarrok : public IEnemy
{
public:
	//�R���X�g���N�^
	CWarrok();

	//�f�X�g���N�^
	~CWarrok();

	//������
	//position	���W
	void Init(CVector3 position) override;

	//�X�V�����O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�U��
	void Attack() override;

	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)override;
};