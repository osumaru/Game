/*
*	�G�̃C���^�[�t�F�[�X�N���X
*/

#pragma once

#include "../Enemy/EnemyState/EnemyStateMachine.h"

class IEnemy : public IGameObject
{
public:
	//�R���X�g���N�^
	IEnemy();

	//�f�X�g���N�^
	virtual ~IEnemy();

	//������
	virtual void Init(CVector3 position) = 0;

	//�X�V
	virtual void Update() = 0;

	//�`��
	virtual void Draw() = 0;

	//�G�̍��W���擾
	const CVector3& GetPosition()
	{
		return m_position;
	}

	//�Đ��������A�j���[�V�����̔ԍ���ݒ�
	void SetAnimNum(int animNum)
	{
		m_animNum = animNum;
	}

protected:
	CSkinModel				m_skinModel;			//�X�L�����f��
	CCharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	CAnimation				m_animation;			//�A�j���[�V����
	EnemyStateMachine		m_enemyStateMachine;	//�X�e�[�g�}�V��
	CVector3				m_position;				//���W
	int						m_animNum = 0;			//�Đ�����A�j���[�V�����ԍ�
	int						m_animNumOld = 0;		//1�O�̃A�j���[�V�����ԍ�
};