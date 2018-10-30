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

	//�ړ����Ă��邩
	bool GetIsMove()
	{
		return m_isMove;
	}

	//�ړ����x���擾
	const CVector3& GetMoveSpeed() const
	{
		return m_characterController.GetMoveSpeed();
	}

	//�ړ����x��ݒ�
	//moveSpeed		�ړ����x
	void SetMoveSpeed(const CVector3& moveSpeed)
	{
		m_characterController.SetMoveSpeed(moveSpeed);
	}

private:
	CCharacterController	m_characterController;			//�L�����N�^�[�R���g���[���[
	IEnemy*					m_enemy = nullptr;				//�G�l�~�[
	CVector3				m_destination;					//�ړ���̍��W
	int						m_interval = 0;
	bool					m_isMove = false;				//�ړ����Ă��邩
};