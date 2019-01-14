#include "stdafx.h"
#include "Warrok.h"
#include "../../Player/Player.h"
#include "../../Camera/GameCamera.h"
#include "Rock.h"

CWarrok::CWarrok()
{
	this->SetIsActive(false);
}

CWarrok::~CWarrok()
{
}

void CWarrok::OnInvokeAnimationEvent(//アニメーションイベントが呼ばれるごとに呼び出される？
	const wchar_t* animClipName,
	const wchar_t* eventName)
{
	if (wcscmp(animClipName, L"Assets/modelData/WarrokAttack.tka") == 0) 
	{
		m_isAttack = !m_isAttack;
	}

	if (wcscmp(animClipName, L"Assets/modelData/WarrokRock.tka") == 0)
	{
		//岩からプレイヤーへのベクトルを求める
		CVector3 distance = GetPlayer().GetPosition() - m_rock->GetPosition();
		//XZ平面での距離を求める
		CVector3 distanceXZ = distance;
		distanceXZ.y = 0.0f;
		float lengthXZ = distanceXZ.Length();
		//投げる角度を設定
		float angle = CMath::PI / 6;
		//投げる高さを求める
		float height = tan(angle) * lengthXZ;
		//投げる方向を求める
		CVector3 moveDir = distance;
		moveDir.y += height;
		float length = moveDir.Length();
		moveDir.Normalize();
		//移動速度を設定
		CVector3 moveSpeed;
		moveSpeed.x = moveDir.x * length * cos(angle);
		moveSpeed.y = moveDir.y * length * sin(angle);
		moveSpeed.z = moveDir.z * length * cos(angle);
		m_rock->SetMoveSpeed(moveSpeed);
		//投げるフラグを立てる
		m_rock->SetIsThrow(true);
	}
}

void CWarrok::Init(const CVector3& position)
{
	//モデルを読み込む
	m_skinModel.Load(L"Assets/modelData/Warrok.cmo", &m_animation);
	m_skinModel.LoadNormalmap(L"Assets/modelData/Warrok_normal.png");
	m_position = position;
	//キャラクターコントローラーを初期化
	m_characterController.Init(0.5f, 0.9f, m_position);
	m_characterController.SetGravity(-9.8f);
	//アニメーションの初期化
	wchar_t* animClip[CEnemyState::enAnimationWarrok_Num] = {
		L"Assets/modelData/WarrokStand.tka",
		L"Assets/modelData/WarrokWalk.tka",
		L"Assets/modelData/WarrokDash.tka",
		L"Assets/modelData/WarrokAttack.tka",
		L"Assets/modelData/WarrokDamageSmall.tka",
		L"Assets/modelData/WarrokDown.tka",
		L"Assets/modelData/WarrokUp.tka",
		L"Assets/modelData/WarrokDeath.tka",
		L"Assets/modelData/WarrokRock.tka"
	};
	m_animation.Init(animClip, CEnemyState::enAnimationWarrok_Num);
	m_animation.SetLoopFlg(CEnemyState::enAnimationWarrok_Idle, true);
	m_animation.SetLoopFlg(CEnemyState::enAnimationWarrok_Walk, true);
	m_animation.SetLoopFlg(CEnemyState::enAnimationWarrok_Chase, true);
	//Add(&m_enemyStateMachine, 0);
	//Add(&m_enemyTurn, 0);
	//Add(&m_enemySearch, 0);

	//ステータスを設定
	m_status.strength = 10;
	m_status.defense = 0;
	m_status.hp = 50;
	m_status.maxHp = m_status.hp;
	m_status.gold = 100;
	m_status.exp = 10;
	this->SetIsActive(true);
	//腰のワールド行列を取得
	m_spineMatrix = &GetBoneWorldMatrix(L"Spine");
	//攻撃できる距離を設定
	m_attackLength = 10.0f;
	//攻撃タイプを設定
	m_attackType = enAttackType_Far;

	m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
	{
		OnInvokeAnimationEvent(animClipname, eventName);
	});
}

bool CWarrok::Start()
{
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CWarrok::Update()
{
	if (m_status.hp <= 0)
	{
		m_isDead = true;
		//剛体を削除する
		m_characterController.RemovedRigidBody();
	}

	if (m_isAttack) 
	{
		//攻撃中はプレイヤーとの当たり判定をとる
		//ボーンのワールド行列を取得
		CMatrix boneMatrix = GetBoneWorldMatrix(L"LeftHand");
		CVector3 bonePosition;
		bonePosition.x = boneMatrix.m[3][0];
		bonePosition.y = boneMatrix.m[3][1];
		bonePosition.z = boneMatrix.m[3][2];
		//敵の攻撃との距離を計算
		CVector3 playerPosition = GetPlayer().GetPosition();
		playerPosition.y += 0.5f;
		CVector3 distance = bonePosition - playerPosition;
		float length = distance.Length();
		if (length < 1.0f)
		{
			//プレイヤーがダメージを受けた
			GetPlayer().SetStanDamage(m_status.strength);
			GetPlayer().SetDamageEnemyPos(m_position);
		}
	}

	if (!m_isWireHit) 
	{
		//アニメーションの更新
		m_animation.Update(GameTime().GetDeltaFrameTime());
	}

	if (!m_isDead && !m_isWireHit)
	{
		//座標の更新
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GameTime().GetDeltaFrameTime());
		m_position = m_characterController.GetPosition();
	}

	//モデルの更新
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
}

void CWarrok::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CWarrok::Attack()
{
	//XZ平面でのプレイヤーとの距離を求める
	CVector3 toPlayer = GetPlayer().GetPosition() - m_position;
	toPlayer.y = 0.0f;
	float length = toPlayer.Length();
	if (length > 4.0f)
	{
		//岩を投げる
		m_animation.Play(CEnemyState::enAnimationWarrok_throw, 0.3f);
		m_rock = New<CRock>(PRIORITY_ENEMY);
		m_rock->Init(this, m_position);
	}
	else 
	{
		//通常攻撃
		m_animation.Play(CEnemyState::enAnimationWarrok_Attack, 0.3f);
	}
}
