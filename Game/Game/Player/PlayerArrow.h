#pragma once
class CBow;

class CPlayerArrow : public IGameObject
{
public:
	CPlayerArrow();
	~CPlayerArrow();
	bool Start();
	void Update();
	void Draw();
	const CVector3 getArrowPosition()
	{
		return m_arrowPosition;
	}
private:
	CSkinModel		m_arrowskin;
	CVector3		m_arrowPosition;
	CQuaternion		m_arrowRot;
	CVector3		m_scale = CVector3::Zero;
	CVector3		m_moveSpeed = CVector3::Zero;
	float			m_lifeTime = 0.0f;
	bool			m_isMove = false;
	const float		GRAVITY  =  -3.0f;					//�d��
	const float     MOVE_POWRE	= 40.0f;				//�|�����
	const float		ARROW_LIFE	= 1000.0f;				//�|�̐�������
	const float		OFFSET_Y	=  1.0f;				//Y�����ɑ΂��Ă̕␳�l
	const float		HIT_LENGTH	=  0.5f;				//��̓����蔻��܂ł̋���
	const CVector3  ARROW_SCALE = { 2.5f,2.5f,2.5f };	//��̑傫��
	CBow*			m_pBow;								//�����������Ƃ��Ɏg���|�̃|�C���^�[
};

