#pragma once
class CPlayer;
//武器の基底クラス

class IWeapon
{
public:
	//デストラクタ
	virtual ~IWeapon(){}

	//初期化関数
	void Init(CPlayer* player);

	//継承用用の初期化関数
	virtual void Init(){}

	//更新処理
	void Updater();
	
	//継承用の更新処理
	virtual void Update(){}

	void Drawer();

	virtual void Draw(){}

	virtual void AfterDraw(){}

	void AfterDrawer();

	virtual void EnemyAttack(){ }

	void EnemyAttacker();

	const CVector3 GetPosition() const
	{
		return m_worldPos;
	}
protected:
	CPlayer*					m_pPlayer = nullptr;		//プレイヤーのインスタンス
	const CMatrix*				m_normalBoneMat = nullptr;	//プレイヤーのボーン行列
	const CMatrix*				m_attackBoneMat = nullptr;	//プレイヤーのボーン行列
	CVector3					m_position;					//通常時の座標
	CVector3					m_attackPosition;			//攻撃時の座標
	CQuaternion					m_rotation;					//通常時の回転
	CQuaternion					m_attackRotation;			//攻撃時の回転
	CVector3					m_worldPos;					//当たり判定用の座標
	CSkinModel					m_skinModel;				//武器のスキンモデル
	
};