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
	//position	座標
	void Init(CVector3 position);
	//更新される前に一度だけ呼ばれる
	bool Start();
	//更新
	void Update();
	//描画
	void Draw();

private:
	CSkinModel				m_skinModel;			//スキンモデル
	CCharacterController	m_characterController;	//キャラクターコントローラー
	CVector3				m_position;				//座標
	CQuaternion				m_rotation;				//回転
	CVector3				m_targetPos;			//ターゲットの座標
	CVector3				m_enemyPos;				//敵の座標
};