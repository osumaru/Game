#pragma once
#include "PlayerArrow.h"
#include "Weapon/WeaponManager.h"
#include "WireAction.h"

class CPlayer;
/*
プレイヤーとステートマシンの間をもつプレイヤーのフレンドクラス
*/

class CPlayerGetter
{
public:
	void SetPlayer(CPlayer* player)
	{
		m_pPlayer = player;
	}

	//ワイヤーアクションを管理するクラスを取得
	CWireAction& GetWireAction();

	//無敵かどうかのフラグを設定
	void SetIsInvincible(bool isInvincible);

	CAnimation& GetAnimation();

	CCharacterController& GetCharacterController();

	//ダメージ状態を解除する関数
	void DamageStateReset();

	/*
	プレイヤーの座標の設定
	*/
	void SetPosition(const CVector3& pos);

	/*
	プレイヤーの移動速度の設定
	*/
	void SetMoveSpeed(const CVector3& moveSpeed);

	/*
	死ぬかどうかのフラグを設定
	*/
	void SetIsDied(bool isDied);

	/*
	攻撃してるかのフラグを設定
	*/
	void SetIsAttack(bool isAttack);

	//プレイヤーのスピードを取得する
	const CVector3& GetMoveSpeed();

private:
	CPlayer*	m_pPlayer = nullptr;
};
