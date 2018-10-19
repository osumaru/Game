/*
*	�G�l�~�[�̈ړ��N���X
*/

#pragma once

class IEnemy;

class CEnemyMove : public IGameObject
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	CEnemyMove(IEnemy* enemy) :
		m_enemy(enemy)
	{
	}

	//�X�V���Ă΂��O�Ɉ�x�����Ă΂��
	bool Start();

	//�X�V
	void Update();

private:
	CCharacterController	m_characterController;			//�L�����N�^�[�R���g���[���[
	IEnemy*					m_enemy = nullptr;				//�G�l�~�[
	CVector3				m_moveSpeed = CVector3::Zero;	//�ړ����x
};