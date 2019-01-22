#pragma once
class CPlayer;
class IEnemy;

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

	//���C���[�ɓ��������G�l�~�[���擾
	IEnemy* GetHitEnemy()
	{
		return m_hitEnemy;
	}

	//���C���[���΂����Y�����̕␳�l���擾
	float GetOffsetY()
	{
		return WIRE_OFFSET_Y;
	}

private:
	struct SWireInfo
	{
		float value;
		CVector3 wirePos;
	};

private:
	const CPlayer*					m_pPlayer = nullptr;					//�v���C���[�̃C���X�^���X
	IEnemy*							m_hitEnemy = nullptr;					//���C���[�𓖂Ă��G�l�~�[
	bool							m_isWireMove = false;					//���C���[�ړ��ł��邩
	CRayTest						m_wireCollisionSolver;					//���C���[�ړ��̃R���W���������N���X
	CVector3						m_wirePosition;
	static const int				WIRE_POS_LIST_NUM = 10;
	SWireInfo						m_wirePositionList[WIRE_POS_LIST_NUM];							//���C���[�ړ���̍��W
	std::vector<const CVector3*>	m_posWireFly;							//��Ԑ�̒n�_���X�g
	EnWireState						m_state = enStateEnemy/*enStateMap*/;					//���C���[�̏��
	float							WIRE_OFFSET_Y = 0.0f;					//���C���[���΂����Y�����̕␳�l
};