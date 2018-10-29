#pragma once

class CPlayer;

class CWeapon
{
public:
	enum EnPlayerWeapon
	{
		enWeaponSword,			//片手剣
		enWeaponLongSword,		//両手剣
		enWeaponArrow,				//弓矢
		enWeaponTwinSword,		//二刀
		enWeaponNum
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
	EnPlayerWeapon			m_weaponState = EnPlayerWeapon::enWeaponSword;
};