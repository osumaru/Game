/*
*	�G�l�~�[�T���N���X
*/

#pragma once

class IEnemy;

class CEnemySearch : public IGameObject
{
public:
	//�R���X�g���N�^
	//enemy		�G�l�~�[�̃C���^�[�t�F�[�X�N���X�̃|�C���^
	CEnemySearch(IEnemy* enemy) :
		m_enemy(enemy)
	{
	}

	//�X�V
	void Update();

private:
	IEnemy* m_enemy = nullptr;	//�G�l�~�[
};