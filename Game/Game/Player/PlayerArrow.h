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
	const float		GRAVITY  =  -3.0f;					//重力
	const float     MOVE_POWRE	= 40.0f;				//弓を放つ力
	const float		ARROW_LIFE	= 1000.0f;				//弓の生存時間
	const float		OFFSET_Y	=  1.0f;				//Y方向に対しての補正値
	const float		HIT_LENGTH	=  0.5f;				//矢の当たり判定までの距離
	const CVector3  ARROW_SCALE = { 2.5f,2.5f,2.5f };	//矢の大きさ
	CBow*			m_pBow;								//自分を消すときに使う弓のポインター
};

