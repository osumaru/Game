#include "stdafx.h"
#include "Money.h"
#include "../Player/Player.h"
#include"../../Game/Camera/GameCamera.h"

void CMoney::Init(const int gold)
{
	m_gold = gold;
}

bool CMoney::Start()
{
	return true;
}

void CMoney::Update()
{
	if (GetPlayer().GetIsDied() || m_timer > m_deadTime)
	{
		//プレイヤーが死亡した又は一定時間で削除
		Delete(this);
		return;
	}
	m_timer += GameTime().GetDeltaFrameTime();

	//移動速度を取得
	m_moveSpeed = m_characterController.GetMoveSpeed();
	//地面に接地しているか判定
	bool isPopEnd = m_characterController.IsOnGround();
	if (isPopEnd) {
		//ポップし終わっている
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}

	//拾うことができるか判定
	bool isPickUp = PickUp(isPopEnd, 0.8f);
	if (isPickUp) {
		//拾うことができる
		GetPlayer().GainGold(m_gold);
		Delete(this);
	}

	//キャラクターコントローラーに移動速度を設定
	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);

}

void CMoney::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CMoney::Pop(CVector3 position)
{
	//モデルの初期化
	m_skinModel.Load(L"Assets/modelData/money.cmo");
	m_position = position;
	m_characterController.Init(0.2f, 0.2f, m_position);
	m_characterController.SetUserIndex(EnCollisionAttr::enCollisionAttr_Item);
	float distance = 3.0f;
	float popUpSpeed = 6.0f;
	//ランダム地点にポップさせる
	RamdomPop(distance, popUpSpeed);
}