#pragma once
class CPlayer;

class CWireAction
{
public:
	/*
	������
	player	�v���C���[�̃C���X�^���X
	*/
	void Init(const CPlayer* player);

	/*
	���C���[��΂���̒n�_�o�^
	model	�}�b�v�ɔz�u���Ă�I�u�W�F�N�g�̃��f��
	*/
	void Add(const CSkinModel& model);

	void Update();

	//���C���[�ړ����Ă��邩
	bool IsWireMove() const
	{
		return m_isWireMove;
	}

	//���C���[�ړ����Ă��邩��ݒ�
	void SetIsWireMove(bool isWireMove)
	{
		m_isWireMove = isWireMove;
	}

	//��Ԑ�̍��W���擾�B
	const CVector3& GetWirePosition() const
	{
		return m_wirePosition;
	}

	//���C���[���g���Ăǂ��ɔ�Ԃ��̏��
	enum EnWireState
	{
		enStateEnemy,		//��Ԑ悪�G�l�~�\�ł��鎞
		enStateMap,			//��Ԑ悪�}�b�v�̃I�u�W�F�N�g�ł���Ƃ�
		enWireStateNum		//
	};

	//���C���[�̏�Ԃ�ݒ�
	void SetState(EnWireState state)
	{
		m_state = state;
	}

	//���C���[�̏�Ԃ��擾
	EnWireState GetState()
	{
		return m_state;
	}

private:
	const CPlayer*					m_pPlayer = nullptr;					//�v���C���[�̃C���X�^���X
	bool							m_isWireMove = false;					//���C���[�ړ��ł��邩
	CRayTest						m_wireCollisionSolver;					//���C���[�ړ��̃R���W���������N���X
	CVector3						m_wirePosition;							//���C���[�ړ���̍��W
	std::vector<const CVector3*>	m_posWireFly;							//��Ԑ�̒n�_���X�g
	EnWireState						m_state = enStateMap;					//���C���[�̏��
};