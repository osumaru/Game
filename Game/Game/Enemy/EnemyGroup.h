/*
*	�G�l�~�[�̃O���[�v�N���X
*/

#pragma once

class IEnemy;

class CEnemyGroup : public IGameObject
{
public:
	//�R���X�g���N�^
	CEnemyGroup() {}

	//�f�X�g���N�^
	virtual ~CEnemyGroup() {}

	//������
	//position		���W
	void Init(CVector3 position)
	{
		m_position = position;
	}

	//�X�V
	void Update() override;

	//�O���[�v�̃��X�g�ɒǉ�
	//enemy		�G�l�~�[�N���X�̃|�C���^
	void Add(IEnemy* enemy)
	{
		m_enemyGroupList.push_back(enemy);
	}

	//���W���擾
	const CVector3& GetPosition()
	{
		return m_position;
	}

	//�O���[�v�̃��X�g���擾
	std::list<IEnemy*> GetGroupList()
	{
		return m_enemyGroupList;
	}

private:
	std::list<IEnemy*> m_enemyGroupList ;	//�O���[�v�̃��X�g
	CVector3 m_position;					//���W
};