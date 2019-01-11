/*
*	敵が投げる岩クラス
*/

#pragma once

class IEnemy;

class CRock : public IGameObject
{
public:
	//コンストラクタ
	CRock() {};

	//デストラクタ
	~CRock() {};

	//初期化
	//handMatrix	手のワールド行列
	//enemyPos		エネミーの座標
	void Init(IEnemy* enemy ,CVector3 enemyPos);

	//更新
	void Update();

	//描画
	void Draw();

	//座標を取得
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//移動速度を設定
	void SetMoveSpeed(const CVector3& moveSpeed)
	{
		m_characterController.SetMoveSpeed(moveSpeed);
	}

	//岩を投げるかを設定
	void SetIsThrow(bool isThrow)
	{
		m_isThrow = isThrow;
	}

private:
	CSkinModel				m_skinModel;			//スキンモデル
	CCharacterController	m_characterController;	//キャラクターコントローラー
	CVector3				m_position;				//座標
	CQuaternion				m_rotation;				//回転
	CVector3				m_targetPos;			//ターゲットの座標
	const IEnemy*			m_enemy;				//エネミー
	CVector3				m_enemyPos;				//敵の座標
	const CMatrix*			m_enemyHandMatrix;		//敵の手の行列
	bool					m_isThrow = false;		//岩を投げるか
};