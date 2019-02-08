/*
*	�E�H�[���b�N�N���X
*/

#pragma once

#include "Enemy/IEnemy.h"

class CRock;

class CWarrok : public IEnemy
{
public:
	//�R���X�g���N�^
	CWarrok();

	//�f�X�g���N�^
	~CWarrok();

	//������
	//position	���W
	//level		���x��
	void Init(const CVector3& position, int level) override;

	//�X�V�����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�U��
	void Attack() override;

	//��ōU������Ƃ��ɉ�]������
	void RockAttackRotation();

	//�A�j���[�V�����C�x���g���Ă΂��Ƃ��ɌĂ΂��
	//animClipName		�A�j���[�V�����̃t�@�C����
	void OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)override;

private:
	CRock*	m_rock = nullptr;	//��
};