#include "stdafx.h"
#include "Ninja.h"
#include "../Player/Player.h"
#include "../Camera/GameCamera.h"

CNinja::CNinja()
{
	this->SetIsActive(false);
}

CNinja::~CNinja()
{
}

void CNinja::OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)
{
	if (wcscmp(animClipName, L"Assets/modelData/NinjaAttack.tka") == 0)
	{
		if (!m_isAttack)
		{
			//攻撃音
			const float AttackVolume = 0.3f;
			CSoundSource* AttackSound = New<CSoundSource>(0);
			AttackSound->Init("Assets/sound/Battle/WarrokEnemyAttackSE.wav");
			AttackSound->Play(false);
			AttackSound->SetVolume(AttackVolume);
		}
		m_isAttack = !m_isAttack;
	}
}

void CNinja::Init(int level)
{
	//モデルを読み込むinfo
	m_skinModel.LoadNormalmap(L"Assets/modelData/Ninja_normal.png");
	//キャラクターコントローラーを初期化
	m_characterController.Init(0.5f, 0.9f, m_position);
	m_characterController.SetGravity(-9.8f);
	//アニメーションの初期化
	wchar_t* animClip[CEnemyState::enAnimation_Num] = {
		L"Assets/modelData/NinjaStand.tka",
		L"Assets/modelData/NinjaWalk.tka",
		L"Assets/modelData/NinjaDash.tka",
		L"Assets/modelData/NinjaAttack.tka",
		L"Assets/modelData/NinjaDamageSmall.tka",
		L"Assets/modelData/NinjaDown.tka",
		L"Assets/modelData/NinjaUp.tka",
		L"Assets/modelData/NinjaDeath.tka"
	};
	m_animation.Init(animClip, CEnemyState::enAnimation_Num);
	m_animation.SetLoopFlg(CEnemyState::enAnimation_Idle, true);
	m_animation.SetLoopFlg(CEnemyState::enAnimation_Walk, true);
	m_animation.SetLoopFlg(CEnemyState::enAnimation_Chase, true);
	m_animation.Play(CEnemyState::enAnimation_Idle, 0.3f);

	//ライトの設定
	CVector4 ambientLight = { 0.2f,0.2f,0.2f,0.6f };
	m_light.SetAmbientLight(ambientLight);
	m_skinModel.SetLight(m_light);

	//ステータスを設定
	m_status.level = level;
	m_status.strength = 15 + level * 2;
	m_status.defense = 10 + level * 2;
	m_status.hp = 85 + level * 5;
	m_status.maxHp = m_status.hp;
	m_status.gold = 80 + level * 20;
	m_status.exp = 7 + level * 3;

	this->SetIsActive(true);

	//エフェクトを初期化
	m_auraEffect.Init(L"Assets/Effect/auraEffect.efk");
	m_auraEffect.SetPosition(m_position);
	m_auraEffect.SetScale({ 1.0f, 1.0f, 1.0f });
	//腰のワールド行列を取得
	m_spineMatrix = &GetBoneWorldMatrix(L"Spine");
	//攻撃できる距離を設定
	m_attackLength = 1.2f;
	//エネミーの種類を設定
	m_type = enEnemy_Ninja;

	m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
	{
		OnInvokeAnimationEvent(animClipname, eventName);
	});
}

bool CNinja::Start()
{
	IEnemy::Start();
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CNinja::Update()
{
	if (m_isDead)
	{
		//剛体を削除する
		m_characterController.RemovedRigidBody();
	}

	//プレイヤーとのレベル差を求める
	int levelDifference = m_status.level - GetPlayer().GetStatus().Level;
	//倒しやすい敵のレベル差を設定
	const int LEVEL_DIFFERENCE_LIMIT = 5;
	//レベル差が大きいか
	if (levelDifference > LEVEL_DIFFERENCE_LIMIT)
	{
		m_effectInterval++;
		const int EFFECT_INTERVAL = 40;
		if (m_effectInterval % EFFECT_INTERVAL == 0)
		{
			m_effectInterval = 0;
			//エフェクトを再生
			m_auraEffect.Play();
		}
		//エフェクトの座標を設定
		m_auraEffect.SetPosition(m_position);
		//エフェクトの更新
		m_auraEffect.Update();
	}

	if (m_isAttack)
	{
		//攻撃中はプレイヤーとの当たり判定をとる
		//ボーンのワールド行列を取得
		CMatrix boneMatrix = GetBoneWorldMatrix(L"RightFoot");
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
			GetPlayer().SetDamage(m_status.strength);
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

void CNinja::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CNinja::Attack()
{
	m_animation.Play(CEnemyState::enAnimation_Attack, 0.3f);
}
