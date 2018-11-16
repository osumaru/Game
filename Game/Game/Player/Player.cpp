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

CPlayer *CPlayer::m_player = NULL;

void CPlayer::OnInvokeAnimationEvent(//アニメーションイベントが呼ばれるごとに呼び出される？
	const wchar_t* animClipName,
	const wchar_t* eventName
)
{

	if (wcscmp(animClipName, L"Assets/modelData/PlayerDash60fpsEvent.tka") == 0)
	{//イベント名で処理を変える？
		const float footVolume = 1.0f;
		CSoundSource* footSound = New<CSoundSource>(0);
		footSound->Init("Assets/sound/Jump.wav");
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
}


void CPlayer::Init(CVector3 position)
{
	//プレイヤーのスキンンモデルのロード
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_skinmodel.LoadNormalmap(L"Assets/modelData/Player_normal.png");

	m_position = position;
	m_characterController.Init(0.3f, 1.0f, m_position);
	m_characterController.SetGravity(-30.0f);
	//ライトの設定
	Light().SetAmbientLight({ 0.5f,0.5f,0.5f,1.0f });
	Light().SetDiffuseLight(0, { 1.0f,1.0f,1.0f,1.0f });
	Light().SetDiffuseLightDir(0, { 0.0f, -1.0f, 1.0f, 1.0f });


	//サークルの読み込み
	{
		m_arrowtexture.Load(L"Assets/sprite/arrowTag.png");
		m_arrowtag.Init(&m_arrowtexture);
		m_arrowtag.SetPosition({ 0.0f,0.0f });
		m_arrowtag.SetSize({ 50.0f,50.0f });
		m_arrowtag.SetAlpha(0.7f);
	}

	//アニメーションの初期化
	{
		wchar_t* animClip[enPlayerAnimationNum] = {
									{ L"Assets/modelData/PlayerStand.tka"},				//待機アニメーション	
									{ L"Assets/modelData/PlayerWalkStay.tka" },			//歩行アニメーション
									{ L"Assets/modelData/PlayerDash60fpsEvent.tka" },		//走りアニメーション
									{ L"Assets/modelData/PlayerRunJump.tka" },			//走りジャンプアニメーション
									{ L"Assets/modelData/PlayerJump2.tka" },				//ジャンプアニメーション
									{ L"Assets/modelData/PlayerCombo4.tka" },			//攻撃アニメーション
									{ L"Assets/modelData/PlayerCombo5.tka" },		//連撃アニメーション
									{ L"Assets/modelData/PlayerCombo6.tka" },		//連撃アニメーション
									{ L"Assets/modelData/PlayerCombo4Combine.tka" },		//連撃アニメーション
									{ L"Assets/modelData/PlayerCombo5Combine.tka" },		//連撃アニメーション
									{ L"Assets/modelData/PlayerAttackCombine.tka" },		//連撃アニメーション
									{ L"Assets/modelData/PlayerDamage.tka" },			//ダメージアニメーション
									{ L"Assets/modelData/PlayerRoll.tka" }	,		//回避アクション
									{ L"Assets/modelData/PlayerRollCombine.tka" }	,		//回避アクション
									{ L"Assets/modelData/PlayerDeath.tka" },			//死亡アニメーション
									{ L"Assets/modelData/PlayerWireMove.tka" },				//ワイヤー移動アニメーション
									{ L"Assets/modelData/PlayerArrowAttack.tka" },		//弓の攻撃アニメーション
									{ L"Assets/modelData/PlayerArrowAttackEvent.tka" },
									{ L"Assets/modelData/PlayerLeageSwordAttack.tka" },	//大剣の攻撃アニメーション
									{ L"Assets/modelData/PlayerTwinSwordAttack.tka" },	//二刀流の攻撃アニメーション
									{ L"Assets/modelData/PlayerLanding.tka" }
		};

		m_animation.Init(animClip, enPlayerAnimationNum);
		m_animation.SetLoopFlg(enPlayerAnimationStand, true);
		m_animation.SetLoopFlg(enPlayerAnimationWalk, true);
		m_animation.SetLoopFlg(enPlayerAnimationRun, true);
		m_animation.SetLoopFlg(enPlayerAnimationWireMove, true);

		//アニメーションイベントリスナーの登録　呼び出される関数の登録？
		m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
		{
			OnInvokeAnimationEvent(animClipname, eventName);
		});

	}


	//プレイヤーのステータスの初期化
	{
		m_status.Strength = 10;						//攻撃力
		m_status.Defense = 3;						//防御力
		m_status.Health = 100;						//体力
		m_status.MaxHealth = m_status.Health;			//レベルごとの最大HP
		m_status.Level = 1;						//レベル
		m_status.OldExp = 15;						//ひとつ前のレベルに必要な経験値
		m_status.NextExp = ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12)) / 2 + 0.5;		//次のレベルアップに必要な経験値
		m_status.ExperiencePoint = 0;					//経験値
		m_status.AccumulationExp += m_status.OldExp;	//累積経験値
		m_status.Gold = 4000;							//所持金
	}
	m_playerGetter.SetPlayer(this);
	m_PlayerStateMachine.SetPlayer(this, &m_playerGetter);
	m_PlayerStateMachine.Init();
	//Add(this, 1);
	m_skinmodel.SetIsShadowCaster(true);
	m_weapon.Init(this);
	m_wireAction.Init(this);
}

void CPlayer::Update()
{
	m_position = m_characterController.GetPosition();
	if (m_isDied)
	{
		return;
	}

	StatusCalculation();	//ステータスの処理

	std::list<CPlayerArrow*>::iterator it;
	it = m_arrowList.begin();
	it = m_arrowList.begin();
	while (it != m_arrowList.end())
	{
		if ((*it)->IsDelete())
		{
			//死亡していたらリストから削除
			CPlayerArrow* enemy = *it;
			it = m_arrowList.erase(it);
		}
		else
		{
			it++;
		}
	}

	if (Pad().IsPressButton(enButtonX))
	{
		m_status.Health = 5;
	}

	if (Pad().GetLeftTrigger())
	{
		GetGameCamera().SetCmareaState(GetGameCamera().enArrow);
		m_isZoom = true;
	}

	else
	{
		GetGameCamera().SetCmareaState(GetGameCamera().enNormal);
		m_isZoom = false;
	}

	CMatrix viewMat;
	CVector3 cameraPos = m_position;
	cameraPos.y += 50.0f;
	CVector3 shadowCameraUp = GetGameCamera().GetSpringCamera().GetTarget() - GetGameCamera().GetSpringCamera().GetPosition();
	shadowCameraUp.y = 0.0f;
	shadowCameraUp.Normalize();
	viewMat.MakeLookAt(cameraPos, m_position, CVector3::AxisX);
	CMatrix projMat;
	projMat.MakeOrthoProjectionMatrix(5, 5, 1.0f, 100.0f);
	Engine().GetShadowMap().SetViewMatrix(viewMat);
	Engine().GetShadowMap().SetProjectionMatrix(projMat);
	m_wireAction.Update();
	m_PlayerStateMachine.Update();
	Rotation();
	m_position = m_characterController.GetPosition();
	//アニメーションの更新
	m_animation.Update(GameTime().GetDeltaFrameTime());
	//スキンモデルの更新
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
	m_weapon.Update();
}

//描画処理
void CPlayer::Draw()
{
	m_weapon.Draw();
	//m_characterController.Draw();
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CPlayer::AfterDraw()
{
	if (m_isZoom)
	{
		m_arrowtag.Draw();
	}
}

void CPlayer::InitArrow()
{
	CPlayerArrow*	Arrow = New<CPlayerArrow>(0);
	m_arrowList.push_back(Arrow);
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

void CPlayer::Rotation()
{

	CVector3 moveSpeed = m_characterController.GetMoveSpeed();
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
	m_rotation.SetRotation(CVector3::AxisY, rad);

	if (m_weapon.GetCurrentState() == CWeapon::enArrow && m_isAttack)
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
		CVector3 moveSpeed = m_characterController.GetMoveSpeed();
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

void CPlayer::UseItem(int number)
{
	if (m_itemList.empty())
	{
		//アイテムがない
		return;
	}
	//選んだアイテムを使う
	std::list<IItem*>::iterator it;
	it = m_itemList.begin();
	for (int i = 0; i < number; i++)
	{
		it++;
	}
	bool isUse = (*it)->Use();
	if (isUse) {
		//使ったアイテムをリストから削除する
		m_itemList.erase(it);
	}
}

void CPlayer::ChangeEquip(int number)
{
	if (m_equipList.empty())
	{
		//装備アイテムがない
		return;
	}
	//選んだ装備と現在の装備を交換する
	std::list<CWeapon::SWeaponStatus>::iterator it;
	it = m_equipList.begin();
	for (int i = 0; i < number; i++)
	{
		it++;
	}
	int weaponNumber = (*it).weaponNum;
	if (m_equipWeapon[weaponNumber].weaponNum == CWeapon::enInvalid)
	{
		//何も装備していない
		m_equipWeapon[weaponNumber] = (*it);
		m_equipList.erase(it);
	}
	else
	{
		//装備を交換する
		CWeapon::SWeaponStatus equipWeapon = m_equipWeapon[weaponNumber];
		m_equipWeapon[weaponNumber] = (*it);
		(*it) = equipWeapon;
	}
}

void CPlayer::AddItemList(IItem * item)
{
	if (m_itemList.size() < CItemInventory::GetItemLimit())
	{
		//所持上限を超えていなければアイテムリストに追加
		m_itemList.push_back(item);
	}
}

void CPlayer::AddEquipList(CWeapon::SWeaponStatus item)
{
	if (m_equipList.size() < CEquipInventory::GetEquipLimit())
	{
		//所持上限を超えていなければ装備リストに追加
		m_equipList.push_back(item);
	}
}