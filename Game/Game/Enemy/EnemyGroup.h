/*
*	�G�l�~�[�̃O���[�v�N���X
*/

#pragma once

class IEnemy;

struct SEnemyGroupData
{
	IEnemy* enemy;
	int groupNumber;
};

class CEnemyGroup : public IGameObject
{
public:
	//�R���X�g���N�^
	CEnemyGroup() {}

	//�f�X�g���N�^
	virtual ~CEnemyGroup() {}

	//������
	//position		���W
	void Init(const CVector3& position)
	{
		m_position = position;
	}

	//�X�V
	void Update() override;

	//�O���[�v�̃��X�g�ɒǉ�
	//enemy		�G�l�~�[�N���X�̃|�C���^
	void Add(IEnemy* enemy)
	{
		m_groupNum++;
		m_enemyGroupList.push_back({ enemy, m_groupNum });
	}

	//���W���擾
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//�O���[�v�̃��X�g���擾
	std::list<SEnemyGroupData> GetGroupList()
	{
		return m_enemyGroupList;
	}

	//�O���[�v���̃G�l�~�[�����擾
	int GetGroupNum()
	{
		return m_groupNum;
	}

private:
	std::list<SEnemyGroupData>	m_enemyGroupList ;	//�O���[�v�̃��X�g
	CVector3					m_position;			//���W
	int							m_groupNum = 0;		//�O���[�v���̃G�l�~�[��
};