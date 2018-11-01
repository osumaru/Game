#pragma once
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
	const float		GRAVITY  =  -3.0f;					//d—Í
	const float     MOVE_POWRE	= 40.0f;				//‹|‚ğ•ú‚Â—Í
	const float		ARROW_LIFE	= 10.0f;				//‹|‚Ì¶‘¶ŠÔ
	const float		OFFSET_Y	=  1.0f;				//Y•ûŒü‚É‘Î‚µ‚Ä‚Ì•â³’l
	const float		HIT_LENGTH	=  0.5f;				//–î‚Ì“–‚½‚è”»’è‚Ü‚Å‚Ì‹——£
	const CVector3  ARROW_SCALE = { 2.5f,2.5f,2.5f };	//–î‚Ì‘å‚«‚³
};

