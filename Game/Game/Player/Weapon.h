#pragma once

class CPlayer;
//武器を管理するクラス

class CWeapon
{
public:
	enum EnPlayerWeapon
	{
		enSword,			//片手剣
		enLongSword,		//両手剣
		enArrow,				//弓矢
		enTwinSword,		//二刀
		enWeaponNum,
		enInvalid			//何もない
	};

	void Init(CPlayer* player);

	void Update();

	void Draw();

	EnPlayerWeapon GetCurrentState() const
	{
		return m_weaponState;
	}

	const CVector3& GetPosition() const
	{
		return m_worldPos[m_weaponState];
	}

	struct SWeaponStatus
	{
		int attack = 0;
		int diffence = 0;
		EnPlayerWeapon weaponNum = enInvalid;
	};

private:
	const CMatrix*			m_boneMat = nullptr;
	CPlayer*				m_pPlayer = nullptr;
	CVector3				m_position[enWeaponNum];
	CVector3				m_attackPosition[enWeaponNum];
	CQuaternion				m_rotation[enWeaponNum];
	CQuaternion				m_attackRotation[enWeaponNum];
	CVector3				m_worldPos[enWeaponNum];
	CSkinModel				m_weaponskin[enWeaponNum];								//武器のスキンモデル
	CBoxCollider			m_weaponBoxCollider;									//武器用のボックスコライダー
	CRigidBody				m_weaponRigitBody;										//ボックス用のrigidBody
	EnPlayerWeapon			m_weaponState = EnPlayerWeapon::enSword;
};