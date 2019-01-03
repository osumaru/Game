#include "stdafx.h"
#include "Player.h"
#include"../../Game/Camera/GameCamera.h"
#include "../Map/Map.h"
#include "../Scene/SceneManager.h"
#include "../Enemy/IEnemy.h"
#include "../Item/IItem.h"
#include "../UI/Menu/ItemInventory.h"
#include "../UI/Menu/EquipInventory.h"
#include "../Enemy/Maw.h"
#include "Weapon/Bow.h"
#include "../Enemy/PathFinding/PathFinding.h"

CPlayer *CPlayer::m_player = NULL;
SplayerStatus CPlayer::m_status = {
	m_status.Strength = 10,							//攻撃力
	m_status.Defense = 3,							//防御力
	m_status.Health = 100,							//体力
	m_status.MaxHealth = m_status.Health,			//レベルごとの最大HP
	m_status.Level = 1,								//レベル
	m_status.OldExp = 15,							//ひとつ前のレベルに必要な経験値
	m_status.NextExp = ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12)) / 2 + 0.5,	//次のレベルアップに必要な経験値
	m_status.ExperiencePoint = 0,					//経験値
	m_status.AccumulationExp += m_status.OldExp,	//累積経験値
	m_status.Gold = 4000,							//所持金
};

void CPlayer::OnInvokeAnimationEvent(//アニメーションイベントが呼ばれるごとに呼び出される？
	const wchar_t* animClipName,
	const wchar_t* eventName
)
{

	if (wcscmp(animClipName, L"Assets/modelData/PlayerDash60fpsEvent.tka") == 0)
	{//イベント名で処理を変える？
		const float footVolume = 0.1f;
		CSoundSource* footSound = New<CSoundSource>(0);
		footSound->Init("Assets/sound/SystemSound/Run.wav");
		footSound->Play(false);
		footSound->SetVolume(footVolume);
	}

	if (wcscmp(animClipName, L"Assets/modelData/PlayerThrustAttack.tka") == 0)
	{//たぶん呼ばれた
		/*
		auto soundSource = New<CSoundSource>(0);
		soundSource->Init("sound/Footstep_00.wav");
		soundSource->Play(false);
		*/
	}

	if (!wcscmp(animClipName, L"Assets/modelData/PlayerLeageAttackFirst.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerLeageAttackSecand.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerLeageAttackThird.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerTwinAttackFirst.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerTwinAttackSecand.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerTwinAttackThird.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerCombo4.tka") ||
		!wcscmp(animClipName, L"Assets/modelData/PlayerCombo5.tka") || 
		!wcscmp(animClipName, L"Assets/modelData/PlayerCombo6.tka"))
	{
		m_weaponManager.SetIsAttackCheck(!m_weaponManager.GetIsAttackCheck());
	}
}

void CPlayer::BeforeDead()
{
	((CBow*)m_weaponManager.GetWeapon(enWeaponArrow))->Release();
}

void CPlayer::Init(CVector3 position)
{
	//Sleep(10000);
	//プレイヤーのスキンンモデルのロード
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_skinmodel.LoadNormalmap(L"Assets/modelData/Player_normal.png");

	m_position = position;
	m_skinmodel.Update(m_position, CQuaternion::Identity, CVector3::One);

	m_characterController.Init(0.4f, 1.1f, m_position);
	m_characterController.SetGravity(-30.0f);
	m_characterController.SetUserIndex(enCollisionAttr_Player);

	//アニメーションの初期化
	{
		wchar_t* animClip[enPlayerAnimationNum] = {
									{ L"Assets/modelData/PlayerStand.tka"},					//待機アニメーション	
									{ L"Assets/modelData/PlayerWalkStay.tka" },				//歩行アニメーション
									{ L"Assets/modelData/PlayerDash60fpsEvent.tka" },		//走りアニメーション
									{ L"Assets/modelData/PlayerDashDash.tka" },				//ダッシュアニメーション
									{ L"Assets/modelData/PlayerRunJump.tka" },				//走りジャンプアニメーション
									{ L"Assets/modelData/PlayerJump2.tka" },				//ジャンプアニメーション
									{ L"Assets/modelData/PlayerCombo4.tka" },				//攻撃アニメーション
									{ L"Assets/modelData/PlayerCombo5.tka" },				//連撃アニメーション
									{ L"Assets/modelData/PlayerCombo6.tka" },				//連撃アニメーション
									{ L"Assets/modelData/PlayerCombo4Combine.tka" },		//連撃アニメーション
									{ L"Assets/modelData/PlayerCombo5Combine.tka" },		//連撃アニメーション
									{ L"Assets/modelData/PlayerCombo6Combine.tka" },		//連撃アニメーション
									{ L"Assets/modelData/PlayerLeageAttackFirst.tka" },		//攻撃アニメーション
									{ L"Assets/modelData/PlayerLeageAttackSecand.tka" },	//連撃アニメーション
									{ L"Assets/modelData/PlayerLeageAttackThird.tka" },		//連撃アニメーション
									{ L"Assets/modelData/PlayerLeageAttackFirstEnd.tka" },	//連撃アニメーション
									{ L"Assets/modelData/PlayerLeageAttackSecandEnd.tka" },	//連撃アニメーション
									{ L"Assets/modelData/PlayerLeageAttackThirdEnd.tka" },	//連撃アニメーション
									{ L"Assets/modelData/PlayerTwinAttackFirst.tka" },		//攻撃アニメーション
									{ L"Assets/modelData/PlayerTwinAttackSecand.tka" },		//連撃アニメーション
									{ L"Assets/modelData/PlayerTwinAttackThird.tka" },		//連撃アニメーション
									{ L"Assets/modelData/PlayerTwinAttackFirstEnd.tka" },	//連撃アニメーション
									{ L"Assets/modelData/PlayerTwinAttackSecandEnd.tka" },	//連撃アニメーション
									{ L"Assets/modelData/PlayerTwinAttackThirdEnd.tka" },	//連撃アニメーション
									{ L"Assets/modelData/PlayerJumpAttack.tka"},			//ジャンプ攻撃アニメーション
									{ L"Assets/modelData/PlayerStun.tka" },					//スタンアニメーション
									{ L"Assets/modelData/PlayerDamage.tka" },				//ダメージアニメーション
									{ L"Assets/modelData/PlayerJumpDamage.tka"},			//ダメージ(空中)アニメーション
									{ L"Assets/modelData/PlayerRoll.tka" }	,				//回避アクション
									{ L"Assets/modelData/PlayerRollCombine.tka" }	,		//回避アクション
									{ L"Assets/modelData/PlayerDeath.tka" },				//死亡アニメーション
									{ L"Assets/modelData/PlayerWireThrow2.tka"},			//ワイヤーを投げるアニメーション
									{ L"Assets/modelData/PlayerWireMove.tka" },				//ワイヤー移動アニメーション
									{ L"Assets/modelData/PlayerJumpTackle.tka"},			//ワイヤー攻撃アニメーション
									{ L"Assets/modelData/PlayerArrowAttack.tka" },			//弓の攻撃アニメーション
									{ L"Assets/modelData/PlayerArrowAttackEvent.tka" },
									{ L"Assets/modelData/PlayerLeageSwordAttack.tka" },		//大剣の攻撃アニメーション
									{ L"Assets/modelData/PlayerTwinSwordAttack.tka" },		//二刀流の攻撃アニメーション
									{ L"Assets/modelData/PlayerLanding.tka" },				//着地アニメーション
									{ L"Assets/modelData/PlayerDown.tka" },					//ダウンアニメーション
									{ L"Assets/modelData/PlayerUp.tka" }					//起き上がりアニメーション
		};

		m_animation.Init(animClip, enPlayerAnimationNum);
		m_animation.SetLoopFlg(enPlayerAnimationStand, true);
		m_animation.SetLoopFlg(enPlayerAnimationWalk, true);
		m_animation.SetLoopFlg(enPlayerAnimationRun, true);
		m_animation.SetLoopFlg(enPlayerAnimationDash, true);
		m_animation.SetLoopFlg(enPlayerAnimationWireMove, true);

		//アニメーションイベントリスナーの登録　呼び出される関数の登録？
		m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
		{
			OnInvokeAnimationEvent(animClipname, eventName);
		});
	}

	//プレイヤーのステータスの初期化
	{
	m_status.Health = m_status.MaxHealth;
	m_status.MaxHealth = m_status.MaxHealth;
	//	m_status.Strength = 10;							//攻撃力
	//	m_status.Defense = 3;							//防御力
	//	m_status.Health = 100;							//体力
	//	m_status.MaxHealth = m_status.Health;			//レベルごとの最大HP
	//	m_status.Level = 1;								//レベル
	//	m_status.OldExp = 15;							//ひとつ前のレベルに必要な経験値
	//	m_status.NextExp = ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12)) / 2 + 0.5;	//次のレベルアップに必要な経験値
	//	m_status.ExperiencePoint = 0;					//経験値
	//	m_status.AccumulationExp += m_status.OldExp;	//累積経験値
	//	m_status.Gold = 4000;							//所持金
	}
	m_playerGetter.SetPlayer(this);

	CVector3 boxSize = { 0.4f,0.6f,0.4f };
	m_boxCollider.Create({ boxSize.x,boxSize.y,boxSize.z });
	m_groundCollision.Init(&m_boxCollider,m_position, CQuaternion::Identity);
	CVector3 manipVector = { 0.0f,0.0f,100.0f };
	CVector3 oldRigidPos = m_characterController.GetPosition();
	m_characterController.SetPosition(manipVector);
	m_groundCollision.Execute();
	m_characterController.SetPosition(oldRigidPos);
	m_PlayerStateMachine.SetPlayer(this, &m_playerGetter);
	m_PlayerStateMachine.Init();
	m_skinmodel.SetIsShadowCaster(true);
	m_weaponManager.Init(this);
	m_wireAction.Init(this);
	SetIsActive(true);
	GetGameCamera().CameraSetPlayer();
	m_wireDraw.Init(CVector3::Zero, CVector3::Zero, CVector3::Zero);

}

void CPlayer::Update()
{
	m_position = m_characterController.GetPosition();
	if (m_isDied)
	{
		return;
	}

	StatusCalculation();	//ステータスの処理

	float stickX = Pad().GetLeftStickX();
	float stickZ = Pad().GetLeftStickY();
	CVector3 stickDir = { stickX, 0.0f, stickZ };
	m_playerGetter.SetStickDir(stickDir);

	/*if (Pad().IsPressButton(enButtonX))
	{
		m_status.Health = 0;
	}*/

	if (Pad().IsTriggerButton(enButtonB))
	{
		m_isDamege = true;
	}

	CMatrix viewMat;
	CVector3 cameraPos = m_position;
	cameraPos.y += 50.0f;
	CVector3 shadowCameraUp = GetGameCamera().GetSpringCamera().GetTarget() - GetGameCamera().GetSpringCamera().GetPosition();
	shadowCameraUp.y = 0.0f;
	shadowCameraUp.Normalize();
	viewMat.MakeLookAt(cameraPos, m_position, CVector3::AxisX);
	CMatrix projMat;
	projMat.MakeOrthoProjectionMatrix(5, 5, 1.0f, 1000.0f);
	Engine().GetShadowMap().SetViewMatrix(viewMat);
	Engine().GetShadowMap().SetProjectionMatrix(projMat);
	m_wireAction.Update();
	Rotation(m_characterController.GetMoveSpeed());
	m_animation.Update(GameTime().GetDeltaFrameTime());
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
	m_PlayerStateMachine.Update();
	m_isAction = true;
	m_animation.Update(0.0f);
	m_position = m_characterController.GetPosition();

	//アニメーションの更新
	//スキンモデルの更新
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
	m_weaponManager.Update();
	//補正値をを入れて剛体をずらす
	CVector3 manipVector = { 0.0f,0.0f,100.0f };
	CVector3 oldRigidPos = m_characterController.GetPosition();
	m_characterController.SetPosition(manipVector);
	m_groundCollision.SetPosition(m_position);
	m_groundCollision.Execute();
	m_characterController.SetPosition(oldRigidPos);
}

//描画処理
void CPlayer::Draw()
{
	//g_pathFinding.GetNavigationMesh().Draw();
	m_characterController.Draw();
	m_weaponManager.Draw();
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CPlayer::AfterDraw()
{
	m_weaponManager.AfterDraw();
	if (m_wireAction.IsWireMove()) 
	{
		m_wireDraw.Draw();
	}
}

void CPlayer::StatusCalculation()
{
	//レベルアップの処理
	if (m_status.NextExp <= m_status.ExperiencePoint)
	{
		m_status.ExperiencePoint -= m_status.NextExp;

		m_status.Level += 1;

		m_status.OldExp = m_status.NextExp;

		m_status.NextExp = ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12)) / 2 + 0.5;		//次のレベルアップに必要な経験値


		//10レベルごとのステータスの上昇量
		if (m_status.Level % 10 == 0)
		{

			m_status.Strength += 9;
			m_status.Defense += 6;
			m_status.MaxHealth += 25;
		}
		else if (m_status.Level % 2 == 0)
		{

			m_status.Strength += 5;
			m_status.Defense += 3;
			m_status.MaxHealth += 14;
		}
		else
		{
			m_status.Strength += 2;
			m_status.Defense += 2;
			m_status.MaxHealth += 11;
		}

		m_status.Health = m_status.MaxHealth;
	}
}



void CPlayer::Rotation(const CVector3& stickDir)
{
	if (m_isDamege) {
		return;
	}

	CVector3 moveSpeed = stickDir;
	CVector3 playerFront = CVector3::Front;
	if (moveSpeed.x == 0.0f && moveSpeed.z == 0.0f)
	{
		moveSpeed.x = m_skinmodel.GetWorldMatrix().m[2][0];
		moveSpeed.z = m_skinmodel.GetWorldMatrix().m[2][2];
	}
	moveSpeed.y = 0.0f;
	moveSpeed.Normalize();
	float rad = moveSpeed.Dot(playerFront);
	if (1.0f <= rad)
	{
		rad = 1.0f;
	}
	if (rad <= -1.0f)
	{
		rad = -1.0f;
	}
	rad = acosf(rad);
	CVector3 judgeAxis;
	judgeAxis.Cross(moveSpeed, playerFront);
	if (0.0f < judgeAxis.y)
	{
		rad = -rad;
	}
	CQuaternion addRot;
	addRot.SetRotation(CVector3::AxisY, rad);
	m_rotation.Slerp(0.3f , m_rotation, addRot);

	if (m_weaponManager.GetCurrentState() == enWeaponArrow && m_weaponManager.GetIsAttack())
	{
		CQuaternion rotXZ, rotY;
		CVector3 cameraFlont = GetGameCamera().GetCamera().GetFlont();
		cameraFlont.Normalize();
		rotXZ.SetRotation(CVector3::AxisY, atan2f(cameraFlont.x, cameraFlont.z));
		rotY.SetRotation(CVector3::AxisX, atanf(-cameraFlont.y));
		rotXZ.Multiply(rotY);
		m_rotation = rotXZ;
	}
	else if (m_wireAction.IsWireMove())
	{
		CVector3 moveSpeed = m_wireAction.GetWirePosition() - m_position;
		CVector3 moveSpeedXZ = moveSpeed;
		moveSpeedXZ.y = 0.0f;
		moveSpeed.Normalize();
		moveSpeedXZ.Normalize();
		rad = moveSpeedXZ.Dot(CVector3::Front);
		if (1.0f <= rad)
		{
			rad = 1.0f;
		}
		if (rad <= -1.0f)
		{
			rad = -1.0f;
		}
		rad = acosf(rad);
		CVector3 judgeAxis;
		judgeAxis.Cross(moveSpeedXZ, CVector3::Front);
		if (0.0f < judgeAxis.y)
		{
			rad = -rad;
		}
		CQuaternion multiY;
		multiY.SetRotation(CVector3::AxisY, rad);
		rad = moveSpeed.Dot(moveSpeedXZ);
		if (1.0f <= rad)
		{
			rad = 1.0f;
		}
		if (rad <= -1.0f)
		{
			rad = -1.0f;
		}
		rad = acosf(rad);
		if (moveSpeed.y > 0.0f)
		{
			rad = -rad;
		}
		CQuaternion multiX;
		multiX.SetRotation(CVector3::AxisX, rad);
		m_rotation = CQuaternion::Identity;
		m_rotation.Multiply(multiY);
		m_rotation.Multiply(multiX);
	}
}

bool CPlayer::GetIsStateCondition(CPlayerState::EnPlayerState state)
{
	switch (state)
	{
	case CPlayerState::enPlayerStateRun://左スティックの入力があったか
		return Pad().GetLeftStickX() != 0 || Pad().GetLeftStickY() != 0;

	case CPlayerState::enPlayerStateArrowAttack://xボタンを押して装備している武器が弓だったか
		return Pad().IsTriggerButton(enButtonX) && m_weaponManager.GetCurrentState() == enWeaponArrow;

	case CPlayerState::enPlayerStateArrowShoot:
		return !dynamic_cast<CPlayerArrowAttack*>(m_PlayerStateMachine.GetState(CPlayerState::enPlayerStateArrowAttack))->IsCharge();

	case CPlayerState::enPlayerStateAttack://xボタンを押して装備している武器が弓じゃなかったか
		return Pad().IsTriggerButton(enButtonX) && m_weaponManager.GetCurrentState() != enWeaponArrow;

	case CPlayerState::enPlayerStateAvoidance://bボタンを押しているか
		return m_isAction && Pad().IsTriggerButton(enButtonB);

	case CPlayerState::enPlayerStateDamage://ダメージフラグが立っているか
		return m_isDamege;

	case CPlayerState::enPlayerStateDied://HPが0以下か
		return m_status.Health <= 0;

	case CPlayerState::enPlayerStateJump://Aボタンを押しているか
		return m_isAction && Pad().IsTriggerButton(enButtonA);

	case CPlayerState::enPlayerStateRunJump://Aボタンを押しているか
		return m_isAction && Pad().IsTriggerButton(enButtonA);

	case CPlayerState::enPlayerStateWireMove://ワイヤーで移動するフラグが立っているか
		return m_wireAction.IsWireMove();

	case CPlayerState::enPlayerStateStand://移動量が0か
		return m_characterController.GetMoveSpeed().Length() == 0.0f;
	case CPlayerState::enPlayerStateSky:
		//地面に着地しているかどうか
		return !m_groundCollision.IsHit();
	}
}