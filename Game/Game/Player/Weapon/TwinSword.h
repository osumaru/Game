#pragma once
#include "IWeapon.h"

class CTwinSword : public IWeapon
{
public:
	void Init()override;

	void Update()override;

	void Draw() override;

	SWeaponEnemyAttackInfo EnemyAttackPositionDecide()override;

	SWeaponTraceDrawInfo WeaponTraceDraw()override;

	//スキンモデルを取得
	const CSkinModel& GetSkinModel() const
	{
		return m_skinModelTwin;
	}

	//頂点バッファの座標を格納しているリスト
	const std::vector<CVector3>& GetTwinVertexBufferList() const
	{
		return m_twinVertexBufferVector;
	}

	//頂点バッファの数
	int GetTwinVertexBufferCount()
	{
		return m_twinVertexBufferCount;
	}

private:
	
	const CMatrix*				m_normalTwinBoneMat = nullptr;	//プレイヤーのボーン行列
	const CMatrix*				m_attackTwinBoneMat = nullptr;	//プレイヤーのボーン行列
	CVector3					m_positionTwin;					//通常時の座標
	CVector3					m_attackTwinPosition;			//攻撃時の座標
	CQuaternion					m_rotationTwin;					//通常時の回転
	CQuaternion					m_attackTwinRotation;			//攻撃時の回転
	CSkinModel					m_skinModelTwin;				//双剣武器のスキンモデル
	std::vector<CVector3>		m_twinVertexBufferVector;		//頂点バッファの座標を格納しているリスト
	int							m_twinVertexBufferCount = 0;	//頂点バッファの数
};