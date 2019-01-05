#pragma once
#include "PlayerArrow.h"
#include "Weapon/WeaponManager.h"
#include "WireAction.h"
#include "WireDraw.h"

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

	//スタンダメージ状態を解除する関数
	void StanDamageStateReset();
	/*
	プレイヤーの座標の設定
	*/
	void SetPosition(const CVector3& pos);

	//プレイヤーのクォータニオンを取得
	const CQuaternion& GetRotation();

	//プレイヤーのクォータニオンを設定
	void SetRotation(const CQuaternion& rotation);

	/*
	プレイヤーの移動速度の設定
	*/
	void SetMoveSpeed(const CVector3& moveSpeed);

	/*
	死ぬかどうかのフラグを設定
	*/
	void SetIsDied(bool isDied);

	/*
	スキンモデルのアップデート
	*/
	void SkinModelUpdate();

	/*
	攻撃してるかのフラグを設定
	*/
	void SetIsAttack(bool isAttack);

	//プレイヤーのスピードを取得する
	const CVector3& GetMoveSpeed();

	//スティックの入力方向を設定
	void SetStickDir(const CVector3& stickDir);

	//スティックの入力方向を取得
	const CVector3& GetStickDir();

	void SetDamageEnemyPos(const CVector3& position);

	const CVector3& GetDamageEnemyPos();

	CWireDraw& GetWireDraw();

private:
	CPlayer*	m_pPlayer = nullptr;
	CVector3	m_stickDir;
	CVector3	m_damageEnemyPos;
};
