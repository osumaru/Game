/*
*	�G�l�~�[�̉�]�N���X
*/

#pragma once

class IEnemy;

class CEnemyTurn : public IGameObject
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�N���X�̃|�C���^
	CEnemyTurn(IEnemy* enemy) :
		m_enemy(enemy)
	{
	}

	//�X�V
	void Update();

private:
	IEnemy* m_enemy;	//�G�l�~�[
};