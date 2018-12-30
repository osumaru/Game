/*
*	敵が投げる岩クラス
*/

#pragma once

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
	void Init(const CMatrix* handMatrix, CVector3 enemyPos);

	//更新される前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

	//描画
	void Draw();

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
	CVector3				m_enemyPos;				//敵の座標
	const CMatrix*			m_enemyHandMatrix;		//敵の手の行列
	bool					m_isThrow = false;		//岩を投げるか
};