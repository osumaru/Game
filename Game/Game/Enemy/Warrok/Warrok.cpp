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
		if (!m_isAttack)
		{
			//攻撃音
			const float AttackVolume = 0.3f;
			CSoundSource* AttackSound = New<CSoundSource>(0);
			AttackSound->Init("Assets/sound/Battle/WarrokEnemyAttackSE.wav");
			AttackSound->Play(false);
			AttackSound->SetVolume(AttackVolume);
		}
		//攻撃フラグを切り替える
		m_isAttack = !m_isAttack;
	}

	if (wcscmp(animClipName, L"Assets/modelData/WarrokRock.tka") == 0)
	{
		//移動速度を設定
		m_rock->SetMoveSpeed();
		//投げるフラグを立てる
		m_rock->SetIsThrow(true);
		//岩を投げるときの音を鳴らす
		CSoundSource* rockThrowSound = New<CSoundSource>(0);
		rockThrowSound->Init("Assets/sound/SystemSound/StoneThrow.wav", true);
		rockThrowSound->Play(false);
		rockThrowSound->SetPosition(m_position);
	}
}

void CWarrok::Init(int level)
{
	//モデルを読み込む
	m_skinModel.LoadNormalmap(L"Assets/modelData/Warrok_normal.png");
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
	m_animation.Play(CEnemyState::enAnimation_Idle, 0.3f);

	//ライトの設定
	CVector4 ambientLight = { 0.2f,0.2f,0.2f,0.4f };
	m_light.SetAmbientLight(ambientLight);
	m_skinModel.SetLight(m_light);

	//ステータスを設定
	m_status.level = level;
	m_status.strength = 30 + level * 2;
	m_status.defense = 15 + level * 2;
	m_status.hp = 100 + level * 5;
	m_status.maxHp = m_status.hp;
	m_status.gold = 100 + level * 20;
	m_status.exp = 10 + level * 3;

	this->SetIsActive(true);

	//エフェクトを初期化
	m_auraEffect.Init(L"Assets/Effect/auraEffect.efk");
	m_auraEffect.SetPosition(m_position);
	m_auraEffect.SetScale({ 1.0f, 1.0f, 1.0f });
	//腰のワールド行列を取得
	m_spineMatrix = &GetBoneWorldMatrix(L"Spine");
	//攻撃できる距離を設定
	m_attackLength = 10.0f;
	//攻撃タイプを設定
	m_attackType = enAttackType_Far;
	//エネミーの種類を設定
	m_type = enEnemy_Warrok;

	m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
	{
		OnInvokeAnimationEvent(animClipname, eventName);
	});
}

bool CWarrok::Start()
{
	IEnemy::Start();
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CWarrok::Update()
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

void CWarrok::RockAttackRotation()
{
	//攻撃する方向を求める
	CVector3 attackDir = GetPlayer().GetPosition() - m_position;
	attackDir.y = 0.0f;
	attackDir.Normalize();
	//エネミーの前方向を取得
	CMatrix worldMatrix = GetWorldMatrix();
	CVector3 enemyFront;
	enemyFront.x = worldMatrix.m[2][0];
	enemyFront.y = worldMatrix.m[2][1];
	enemyFront.z = worldMatrix.m[2][2];
	enemyFront.Normalize();
	//角度を計算
	float angle = attackDir.Dot(enemyFront);
	if (angle > 1.0f)
	{
		angle = 1.0f;
	}
	else if (angle < -1.0f)
	{
		angle = -1.0f;
	}
	angle = acosf(angle);
	//回転する方向を求める
	CVector3 cross = attackDir;
	cross.Cross(enemyFront);
	if (cross.y > 0.0f)
	{
		angle *= -1.0f;
	}
	//回転させる
	CQuaternion addRotation;
	addRotation.SetRotation(CVector3::AxisY, angle);
	m_rotation.Multiply(addRotation);
}
