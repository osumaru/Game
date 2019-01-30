#include "stdafx.h"
#include "PlayerRun.h"
#include "../Player.h"
#include "../../Camera/GameCamera.h"

void CPlayerRun::Init()
{
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationRun, 0.3f);
	if (m_pPlayer->GetWeaponManager().GetDrawingWeapon())
	{
		const IWeapon* weapon = m_pPlayer->GetWeaponManager().GetWeapon();
		m_pPlayerGetter->GetAnimation().AddBlendAnimation(weapon->GetWeaponHorldBoneName(), weapon->GetWeaponHoldAnimationNum());
	}

	//タイマー初期化
	m_timer = 0.0f;
	m_isDash = false;
	m_moveSpeed = 0.0f;
	m_accel = 0.0f;
}

void CPlayerRun::Update()
{
	float speed = 8.0f;
	m_timer += GameTime().GetDeltaFrameTime();
	m_accel += 0.1f;
	m_moveSpeed += m_accel;
	m_moveSpeed = min(speed, m_moveSpeed);
	if (!m_isDash && m_timer >= 2.0f)
	{
		m_isDash = true;
		//一定時間走るとダッシュする
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationDash, 0.2f);
		if (m_pPlayer->GetWeaponManager().GetDrawingWeapon())
		{
			const IWeapon* weapon = m_pPlayer->GetWeaponManager().GetWeapon();
			m_pPlayerGetter->GetAnimation().AddBlendAnimation(weapon->GetWeaponHorldBoneName(), weapon->GetWeaponHoldAnimationNum());
		}
	}
	if (m_isDash)
	{
		m_moveSpeed = 12.0f;
	}
	if (!m_pPlayer->GetWeaponManager().GetDrawingWeapon())
	{
		m_pPlayerGetter->GetAnimation().BlendAnimationClear();
	}
	const CCamera& gameCamera = GetGameCamera().GetCamera();
	CVector3 frontVec = gameCamera.GetTarget() - gameCamera.GetPosition();
	frontVec.y = 0.0f;
	frontVec.Normalize();
	CVector3 rightVec;
	rightVec.Cross(CVector3::AxisY, frontVec);
	rightVec.Normalize();
	CVector3 moveSpeed = CVector3::Zero;
	moveSpeed += frontVec * Pad().GetLeftStickY();
	moveSpeed += rightVec * Pad().GetLeftStickX();
	moveSpeed.Normalize();
	moveSpeed.Scale(speed);

	m_pPlayerGetter->SetMoveSpeed(moveSpeed);
	m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());

	m_pPlayerGetter->SetPosition(m_pPlayerGetter->GetCharacterController().GetPosition());
	//走り中にダメージを受けた場合
	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
	}
	//走っているときに攻撃した時の処理
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateArrowAttack))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateArrowAttack);
	}
	//走っているときに攻撃した時の処理
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAttack))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateAttack);
	}
	//走り中に回避した時の処理
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateAvoidance))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateAvoidance);
	}
	//走っている時にジャンプが押されたとき処理
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRunJump))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateRunJump);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateStand))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateWireMove))
	{
		//ワイヤー移動できるなら遷移
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
	}
	else if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateSky))
	{
		GetPlayer().GetStateMachine().SetState(CPlayerState::enPlayerStateSky);
	}
}