/*
*	�]���r�N���X
*/

#pragma once

#include "Enemy/IEnemy.h"

class Zombie : public IEnemy
{
public:
	//�R���X�g���N�^
	Zombie();

	//�f�X�g���N�^
	~Zombie();

	//������
	//position	���W
	void Init(CVector3 position);

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�G�̍��W���擾
	CVector3 GetPosition()
	{
		return m_position;
	}

private:
	CSkinModel				m_skinModel;			//�X�L�����f��
	CCharacterController	m_characterController;	//�L�����N�^�[�R���g���[���[
	CAnimation				m_animation;			//�A�j���[�V����
	EnemyStateMachine		m_enemyStateMachine;	//�X�e�[�g�}�V��
	CVector3				m_position;				//���W
};