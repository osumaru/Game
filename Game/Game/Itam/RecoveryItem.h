/*
*	回復アイテムクラス
*/

#pragma once

class CRecoveryItem : public IGameObject
{
public:
	//初期化
	//position	座標
	void Init(CVector3 position);

	//更新する前に一度だけ呼ばれる
	bool Start();

	//更新
	void Update();

	//描画
	void Draw();

	//移動
	void Move();

private:
	CSkinModel				m_skinModel;			//スキンモデル
	CVector3				m_position;				//座標
	CQuaternion				m_rotation;				//回転
	CCharacterController	m_characterController;	//キャラクターコントローラー
	CVector3				m_popPosition;			//アイテムがポップする座標
	float					m_speed = 4.0f;			//移動速度
};
