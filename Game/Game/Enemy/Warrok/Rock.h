/*
*	敵が投げる岩クラス
*/

#pragma once

class CWarrok;

class CRock : public IGameObject
{
public:
	//コンストラクタ
	CRock() {};

	//デストラクタ
	~CRock() {};

	//初期化
	//warrok		エネミーのポインタ
	//enemyPos		エネミーの座標
	void Init(CWarrok* warrok, const CVector3& enemyPos);

	//更新
	void Update();

	//描画
	void Draw();

	//移動速度を設定
	void SetMoveSpeed();

	//投げられているかを設定
	void SetIsThrow(bool isThrow)
	{
		m_isThrow = isThrow;
	}

	//投げられているかを取得
	bool GetIsThrow()
	{
		return m_isThrow;
	}

private:
	CSkinModel				m_skinModel;			//スキンモデル
	CCharacterController	m_characterController;	//キャラクターコントローラー
	CVector3				m_position;				//座標
	CQuaternion				m_rotation;				//回転
	CVector3				m_targetPos;			//ターゲットの座標
	CWarrok*				m_warrok;				//エネミー
	CVector3				m_enemyPos;				//敵の座標
	const CMatrix*			m_enemyHandMatrix;		//敵の手の行列
	bool					m_isThrow = false;		//投げられているか
	bool					m_isHit = false;		//何かに当たった
	SParticleEmittInfo		m_particleInfo;			//パーティクルの情報
};