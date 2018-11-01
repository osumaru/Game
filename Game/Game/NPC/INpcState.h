#pragma once
class INpcState	:	public IGameObject
{
public:
	INpcState();
	~INpcState();
	virtual void Init(const CVector3 position, const CQuaternion rotation) = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	const CVector3 GetPosition()
	{
		return m_position;
	}

	void SetPosition(const CVector3 pos)
	{
		m_position = pos;
	}

protected:
	CSkinModel		m_skinModel;						//�X�L�����f��
	CVector3		m_position = CVector3::Zero;		//�|�W�V����
	CVector3		m_scale = CVector3::One;			//�X�P�[��
	CQuaternion		m_rotation = CQuaternion::Identity;	//��]
};

