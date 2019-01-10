/*
*	ボスがいる建物のクラス
*/

#pragma once

class CMessage;
class CChoices;

class CBossBuilding : public IGameObject
{
public:
	//初期化
	//position	座標
	void Init(CVector3 position);

	//更新
	void Update() override;

	//描画
	void Draw() override;
private:
	CMessage*	m_message = nullptr;	//メッセージ
	CChoices*	m_choices = nullptr;	//選択肢
	CSkinModel	m_skinModel;			//モデル
	CVector3	m_position;				//座標
	CQuaternion m_rotation;				//回転
	float		m_timer = 0.0f;			//タイマー
	bool		m_isChoice = false;		//選択しているか
};