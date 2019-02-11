/*
*	アイテムクラスのインターフェース
*/

#pragma once

class IItem : public IGameObject
{
public:
	//コンストラクタ
	IItem();

	//デストラクタ
	virtual ~IItem();

	//更新する前に一度だけ呼ばれる
	virtual bool Start() { return true; }

	//更新
	virtual void Update() = 0;

	//描画
	virtual void Draw() {};

	//ランダム地点にポップさせる
	//distance	ランダム地点までの距離
	//upSpeed	ポップさせる上方向の速度
	//戻り値　移動速度
	CVector3 RamdomPop(float distance, float upSpeed);

	//アイテムを拾うことができるか
	//isPopEnd	ポップし終わっているか
	//length	アイテムを拾える距離
	bool PickUp(bool isPopEnd, float length);

	//移動
	//戻り値　移動速度
	CVector3 Move();

	//加速度をリセットする
	void AcceleReset()
	{
		m_accele = 0.0f;
	}
protected:
	CSkinModel				m_skinModel;				//スキンモデル
	CVector3				m_position;					//座標
	CQuaternion				m_rotation;					//回転
	CCharacterController	m_characterController;		//キャラクターコントローラー
	const float				m_deadTime = 30.0f;			//アイテムが消滅するまでの時間
	float					m_timer = 0.0f;				//タイマー
	float					m_accele = 0.0f;			//加速度
	bool					m_isPopEnd = false;			//ポップし終わったか
	bool					m_isMove = false;			//移動しているか
};