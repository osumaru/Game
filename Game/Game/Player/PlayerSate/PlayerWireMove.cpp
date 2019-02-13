#include "stdafx.h"
#include "PlayerWireMove.h"
#include "../Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"
CPlayerWireMove::CPlayerWireMove()
{
	m_hitEffect.Init(L"Assets/Effect/DamageEffect.efk");
}

void CPlayerWireMove::Init()
{
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationWireThrow, 0.25f);
	m_movePosition = m_pPlayer->GetWireAction().GetWirePosition();	
	CVector3 playerPos = GetPlayer().GetPosition();
	playerPos.y += m_pPlayer->GetWireAction().GetOffsetY();
	m_moveDirection = m_movePosition - playerPos;
	m_moveDirection.Normalize();
	m_accel = 0.0f;
	m_moveSpeed = 0.0f;
	m_wireSpeed = 1.0f;
	m_isWireThrow = true;
	//プレイヤーの手のワールド行列を取得
	m_playerHandMatrix = &m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"LeftHand");
	//ワイヤー描画を更新
	UpdateWireDraw();

	const float WireAttackVolume = 0.3f;
	CSoundSource* WireAttackSound = New<CSoundSource>(0);
	WireAttackSound->Init("Assets/sound/Battle/WireThrow.wav");
	WireAttackSound->Play(false);
	WireAttackSound->SetVolume(WireAttackVolume);
	const float WindVolume = 0.1f;
	m_windSound = New<CSoundSource>(0);
	m_windSound->Init("Assets/sound/Battle/magic-wind.wav");
	//m_windSound->Play(true);
	m_windSound->SetVolume(WindVolume);
}

void CPlayerWireMove::Update()
{
	//ダメージを受けた場合の処理
	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		//再生停止
		m_windSound->Stop();
		const float DamageVolume = 0.3f;
		CSoundSource* DamageSound = New<CSoundSource>(0);
		DamageSound->Init("Assets/sound/Battle/Damage.wav");
		DamageSound->Play(false);
		DamageSound->SetVolume(DamageVolume);
		//移動が終わった
		GetPlayer().GetWireAction().SetIsWireMove(false);
		//ワイヤーをエネミーに当てている
		if (GetPlayer().GetWireAction().GetHitEnemy() != nullptr)
		{
			//ワイヤーに当たったフラグを戻す
			GetPlayer().GetWireAction().GetHitEnemy()->SetIsWireHit(false);
		}
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
		return;
	}

	//ワイヤー描画を更新
	UpdateWireDraw();

	//ワイヤーを投げるアニメーションが終了したか判定
	if (m_pPlayerGetter->GetAnimation().GetCurrentAnimationNum() == enPlayerAnimationWireThrow
		&& !m_pPlayerGetter->GetAnimation().IsPlay())
	{
		m_windSound->Play(true);
		//ワイヤー移動するアニメーションに切り替え
		m_isWireThrow = false;
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationWireMove, 0.25f);
	}
	if (m_isWireThrow)
	{
		//ワイヤーを投げるアニメーションをしている
		return;
	}

	bool isMoveEnd = false;
	CVector3 playerPos = GetPlayer().GetPosition();
	playerPos.y += m_pPlayer->GetWireAction().GetOffsetY();
	CVector3 toMovePos = m_movePosition - playerPos;
	float angle = m_moveDirection.Dot(toMovePos);
	float length = toMovePos.Length();
	toMovePos = m_moveDirection;
	toMovePos.Normalize();
	m_accel += 0.1f;
	m_moveSpeed += m_accel;
	m_moveSpeed = min(m_moveSpeed, m_speed);
	toMovePos *= m_moveSpeed;
	float range = 2.0f;
	switch (m_pPlayer->GetWireAction().GetState())
	{
	case CWireAction::enStateEnemy:
		range = 2.0f;
		break;
	case CWireAction::enStateMap:
		range = 1.0f;
		break;
	}

	if (length < range || angle < 0.0f) {
		isMoveEnd = true;
		m_pPlayerGetter->SetPosition(m_movePosition);

	}
	else {
		//目標との距離が離れていれば移動先に進む
		float gravityBackup = m_pPlayerGetter->GetCharacterController().GetGravity();
		m_pPlayerGetter->GetCharacterController().SetGravity(0.0f);
		m_pPlayerGetter->SetMoveSpeed(toMovePos);
		m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());
		m_pPlayerGetter->SetPosition(m_pPlayerGetter->GetCharacterController().GetPosition());
		m_pPlayerGetter->GetCharacterController().SetGravity(gravityBackup);
	}

	if (isMoveEnd) {
		//再生停止
		m_windSound->Stop();

		//移動が終わった
		GetPlayer().GetWireAction().SetIsWireMove(false);
		IEnemy* enemy = GetPlayer().GetWireAction().GetHitEnemy();
		const float SCALE = 0.1f;
		switch(m_pPlayer->GetWireAction().GetState())
		{
		case CWireAction::enStateEnemy:
			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateWireAttack);
			//エネミーにダメージフラグを立てる
			enemy->SetIsDamage(true);
			m_hitEffect.Play();
			m_hitEffect.SetPosition(enemy->GetPosition());
			m_hitEffect.SetScale({ SCALE, SCALE, SCALE });
			m_hitEffect.Update();
			//エネミーのワイヤーに当たったフラグを戻す
			enemy->SetIsWireHit(false);
			break;
		case CWireAction::enStateMap:
			if (0.0f < m_moveDirection.y)
			{
				//toMovePos.y = 10.0f;
				m_pPlayerGetter->SetMoveSpeed(toMovePos);
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateJump);
			}
			else
			{
				if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
				{
					m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateRun);
				}
				else
				{
					m_pPlayerGetter->SetPosition(m_movePosition);
					m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateSky);
					m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
				}
			}
			break;
		}
	}
	if (m_pPlayer->GetWireAction().GetState() == CWireAction::enStateMap && !Pad().IsPressButton(enButtonRightTrigger))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateSky);
		GetPlayer().GetWireAction().SetIsWireMove(false);
	}
}

void CPlayerWireMove::UpdateWireDraw()
{
	//ワイヤーの始点を決める
	m_playerHandPos.x = m_playerHandMatrix->m[3][0];
	m_playerHandPos.y = m_playerHandMatrix->m[3][1];
	m_playerHandPos.z = m_playerHandMatrix->m[3][2];
	m_pPlayerGetter->GetWireDraw().SetStartPosition(m_playerHandPos);
	//ワイヤーの終点を決める
	CVector3 currentWireDir = m_movePosition - m_playerHandPos;
	float length = currentWireDir.Length();
	CVector3 wireDir = currentWireDir;
	wireDir.Normalize();
	wireDir *= m_wireSpeed;
	m_wireSpeed += m_wireSpeed;
	//ワイヤーの長さがターゲットまでの距離を超えているか
	if (length < wireDir.Length())
	{
		wireDir = currentWireDir;
	}
	CVector3 wireEndPos = m_playerHandPos + wireDir;
	m_pPlayerGetter->GetWireDraw().SetEndPosition(wireEndPos);
	//ワイヤー描画を更新
	m_pPlayerGetter->GetWireDraw().Update();
}
