#include "stdafx.h"
#include "Player.h"
#include"../../Game/Camera/GameCamera.h"
#include "../Map/Map.h"
#include "../Scene/SceneManager.h"
#include "../Enemy/IEnemy.h"

void CPlayer::OnInvokeAnimationEvent(//アニメーションイベントが呼ばれるごとに呼び出される？
	const wchar_t* animClipName,
	const wchar_t* eventName
)
{

	if (wcscmp(animClipName, L"Assets/modelData/PlayerDash60fpsEvent.tka") == 0) {//イベント名で処理を変える？
		const float footVolume = 1.0f;
		CSoundSource* footSound = New<CSoundSource>(0);
		footSound->Init("Assets/sound/Jump.wav");
		footSound->Play(false);
		footSound->SetVolume(footVolume);

	}

	if (wcscmp(animClipName, L"Assets/modelData/PlayerThrustAttack.tka") == 0) {//たぶん呼ばれた
		/*auto soundSource = New<CSoundSource>(0);
		soundSource->Init("sound/Footstep_00.wav");
		soundSource->Play(false);*/
	}
}

void CPlayer::Init(CVector3 position)
{
	//プレイヤーのスキンンモデルのロード
	m_skinmodel.Load(L"Assets/modelData/Player.cmo", &m_animation);
	m_skinmodel.LoadNormalmap(L"Assets/modelData/Player_normal.png");
	//武器のモデルのロード
	m_weaponskin[0].Load(L"Assets/modelData/Sword.cmo", NULL);
	m_weaponskin[1].Load(L"Assets/modelData/LargeSword.cmo", NULL);
	m_weaponskin[2].Load(L"Assets/modelData/LongBow.cmo", NULL);
	m_weaponskin[3].Load(L"Assets/modelData/TwinSword.cmo", NULL);

	m_position = position;
	m_characterController.Init(0.3f, 1.0f,m_position);
	m_characterController.SetGravity(-9.8f);
	//ライトの設定
	m_light.SetAmbientLight({ 0.5f,0.5f,0.5f,1.0f});
	m_light.SetDiffuseLight(0, { 1.0f,1.0f,1.0f,1.0f });
	m_skinmodel.SetLight(m_light);

	m_wireCollisionSolver.Init(0.3f, 1.0f);

	m_weaponBoxCollider.Create({ 0.05f,0.4f,0.05f });
	SRigidBodyInfo rInfo;
	rInfo.collider = &m_weaponBoxCollider;
	rInfo.mass = 0.0f;
	rInfo.pos = m_weaponPosition;
	rInfo.rot = m_weaponRotation;

	m_weaponRigitBody.Create(rInfo);
	m_weaponRigitBody.SetPosition(m_weaponPosition);
	m_weaponRigitBody.SetRotation(m_weaponRotation);
	m_weaponRigitBody.PhysicsWorldRemoveRigidBody();

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
		wchar_t* animClip[enPlayerNum] = {
											{ L"Assets/modelData/PlayerStand.tka"},				//待機アニメーション	
											{ L"Assets/modelData/PlayerWalkStay.tka" },			//歩行アニメーション
											{ L"Assets/modelData/PlayerDash60fpsEvent.tka" },		//走りアニメーション
											{ L"Assets/modelData/PlayerJump3.tka" },			//走りジャンプアニメーション
											{ L"Assets/modelData/PlayerJump.tka" },				//ジャンプアニメーション
											{ L"Assets/modelData/PlayerCombo3.tka" },			//攻撃アニメーション
											{ L"Assets/modelData/PlayerThrustAttack.tka" },		//連撃アニメーション
											{ L"Assets/modelData/PlayerDamage.tka" },			//ダメージアニメーション
											{ L"Assets/modelData/PlayerKaihiStay.tka" }	,		//回避アクション
											{ L"Assets/modelData/PlayerDeath.tka" },			//死亡アニメーション
											{ L"Assets/modelData/PlayerWire.tka" },				//ワイヤー移動アニメーション


											{ L"Assets/modelData/PlayerArrowAttack.tka" },		//弓の攻撃アニメーション
											{ L"Assets/modelData/PlayerArrowAttackEvent.tka" },
											{ L"Assets/modelData/PlayerLeageSwordAttack.tka" },	//大剣の攻撃アニメーション
											{ L"Assets/modelData/PlayerTwinSwordAttack.tka" }	//二刀流の攻撃アニメーション
		};

		m_animation.Init(animClip, enPlayerNum);
		m_animation.SetLoopFlg(enPlayerStand, true);
		m_animation.SetLoopFlg(enPlayerWalk, true);
		m_animation.SetLoopFlg(enPlayerRun, true);

		//アニメーションイベントリスナーの登録　呼び出される関数の登録？
		m_animation.AddAnimationEvent([&](auto animClipname, auto eventName) {
			OnInvokeAnimationEvent(animClipname, eventName);
		});
	}


	//プレイヤーのステータスの初期化
	{
		m_status.Strength	= 10;						//攻撃力
		m_status.Defense	= 3;						//防御力
		m_status.Health		= 100;						//体力
		m_status.MaxHealth = m_status.Health;			//レベルごとの最大HP
		m_status.Level		= 1;						//レベル
		m_status.OldExp		= 15;						//ひとつ前のレベルに必要な経験値
		m_status.NextExp	= ((m_status.OldExp * 1.1f + 0.5) + (m_status.Level * 12 )) / 2 + 0.5;		//次のレベルアップに必要な経験値
		m_status.ExperiencePoint = 0;					//経験値
		m_status.AccumulationExp += m_status.OldExp;	//累積経験値
		m_status.Gold = 0;								//所持金
	}
	
	m_PlayerStateMachine.Start();
	m_PlayerMove.Start();
	m_PlayerRotation.Start();
	Add(&m_PlayerStateMachine,0);
	Add(&m_PlayerMove, 0);
	Add(&m_PlayerRotation, 0);
	Add(this, 1);
	m_skinmodel.SetIsShadowCaster(true);
	
}

void CPlayer::Update()
{
	//アニメーションの更新
	m_animation.Update(GameTime().GetDeltaFrameTime());
	if (m_isDied) { return; }
	WeaponChange();

	//無敵時間の処理
	if (m_intervalOn)
	{
		m_intervalTime += GameTime().GetDeltaFrameTime();
		if (m_intervalTime >= INTERVAL)
		{
			m_intervalOn = false;
			m_intervalTime = 0.0f;
		}
	}

	StatusCalculation();	//ステータスの処理
	PlayerAttack();

	if (Pad().IsTriggerButton(enButtonB))
	{
		ExpUP(100);
	}
	
	std::list<CPlayerArrow*>::iterator it;
	it = m_arrowList.begin();
	while (it != m_arrowList.end()) {
		if ((*it)->IsDelete()) {
			//死亡していたらリストから削除
			CPlayerArrow* enemy = *it;
			it = m_arrowList.erase(it);
		}
		else {
			it++;
		}
	}

	//ワイヤーの処理
	if (Pad().IsTriggerButton(enButtonY) && !m_isWireMove)
	{
		float minLength = FLT_MAX;
		std::list<IEnemy*> enemyList = GetSceneManager().GetGameScene().GetMap()->GetEnemyList();
		//ワイヤーを飛ばす先を決める
		for (auto& enemy : enemyList)
		{
			CVector3 enemyPos = enemy->GetPosition();
			CVector3 toEnemyPos = enemyPos - GetPlayer().GetPosition();
			float length = toEnemyPos.Length();
			if (minLength > length) {
				minLength = length;
				//一番近い敵の位置を移動先とする
				m_wirePosition = enemyPos;
			}
		}

		if (!m_wireCollisionSolver.Execute(m_position, m_wirePosition)) {
			//レイを飛ばしてプレイヤーとの間に障害物がないならワイヤーを使う
			m_isWireMove = true;
			for (auto& enemy : enemyList)
			{
				CVector3 enemyPos = enemy->GetPosition();
				CVector3 toMovePos = m_wirePosition - enemyPos;
				float length = toMovePos.Length();
				if (length < 0.1f) {
					//一番近い敵にワイヤーが当たったフラグを設定する
					enemy->SetIsWireHit(true);
				}
			}
		}
	}
	if (Pad().IsPressButton(enButtonX))
	{
		Engine().GetPointLightManager().AddPointLight(m_position, { (float)Random().GetRandDouble(), (float)Random().GetRandDouble(), (float)Random().GetRandDouble() });
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

	//スキンモデルの更新
	m_skinmodel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);

	m_weaponskin[m_weaponState].Update(m_weaponPosition, m_weaponRotation, m_weaponScale, true);

	m_cameraTargetPos = m_position;
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
}

//描画処理
void CPlayer::Draw()
{
	if (m_isAttack)
	{
		CVector3 weponUpVec = { m_weaponskin[m_weaponState].GetWorldMatrix().m[2][0],m_weaponskin[m_weaponState].GetWorldMatrix().m[2][1],m_weaponskin[m_weaponState].GetWorldMatrix().m[2][2] };
		weponUpVec *= 0.7f;
		m_weaponPosition.Add(weponUpVec);
		m_weaponRigitBody.SetPosition(m_weaponPosition);

	}
	if (m_isZoom)
	{
		m_arrowtag.Draw();
	}
	m_weaponskin[m_weaponState].Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CPlayer::InitArrow()
{
	CPlayerArrow*	Arrow = New<CPlayerArrow>(0);
	Arrow->Start();
	m_arrowList.push_back(Arrow);
	m_initArrow = true;
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

			m_status.Strength	+= 9;
			m_status.Defense	+= 6;
			m_status.MaxHealth	+= 25;
			m_status.Health = m_status.MaxHealth;


		}
		//偶数レベルごとのステータスの上昇量
		else if (m_status.Level % 2 == 0)
		{

			m_status.Strength += 5;
			m_status.Defense += 3;
			m_status.MaxHealth += 14;
			m_status.Health = m_status.MaxHealth;


		}

		else
		{
			m_status.Strength += 2;
			m_status.Defense += 2;
			m_status.MaxHealth += 11;
			m_status.Health = m_status.MaxHealth;
		}

	}


}

void  CPlayer::WeaponChange()
{
	if (GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerAttack) { return; }
	if (m_weaponState == (EnPlayerWeapon)GetSceneManager().GetGameScene().GetWeaponSelect()->GetWeapon()) { return; }
	m_weaponState = (EnPlayerWeapon)GetSceneManager().GetGameScene().GetWeaponSelect()->GetWeapon();
	switch (m_weaponState)
	{
		//片手剣の時の攻撃モーションの設定
	case CWeaponSelect::enSword:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerAttack);
		break;
		//弓の時の攻撃モーションの設定
	case CWeaponSelect::enBow:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerArrowAttack);
		break;
		//大剣の時の攻撃モーションの設定
	case CWeaponSelect::enLargeSword:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerLongSwordAttack);
		break;
		//双剣の時の攻撃モーションの設定
	case CWeaponSelect::enTwinSword:
		GetPlayerStateMachine().SetAttackState(CPlayerState::enPlayerTwinSwordAttack);
		break;
	}
}

void CPlayer::PlayerAttack()
{
	if (!m_isAttack) { return; }
	
	//エネミーのリストを取得
	for (const auto& enemys : GetSceneManager().GetGameScene().GetMap()->GetEnemyList())
	{
		if (!enemys->IsDamage()) {

			CVector3 EnemyVec = enemys->GetPosition();
			EnemyVec.y += 1.3f;
			EnemyVec -= m_weaponPosition;
			float len = EnemyVec.Length();

			if (fabs(len) < 2.0f)
			{
				enemys->SetIsDamage(true);
			}

		}
	}
	

}