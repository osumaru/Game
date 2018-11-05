#include "stdafx.h"
#include "Maw.h"
#include "../Camera/GameCamera.h"
#include "../Player/Player.h"

CMaw *CMaw::m_maw = NULL;

//ダメージアニメーションは入れないようにしてダウンのアニメーションだけにする？
//攻撃モーションを複数入れたい
//

CMaw::CMaw()
{
}

CMaw::~CMaw()
{
}

//アニメーションイベントが呼ばれるごとに呼び出される
void CMaw::OnInvokeAnimationEvent(
	const wchar_t* animClipName,
	const wchar_t* eventName
)
{
	//もう一度呼ばれる間攻撃判定をオンにしておく
	//if (wcscmp(animClipName, L"Assets/modelData/MawAttack.tka") == 0&&!m_isAttack) 
	//{
	//	m_isAttack = true;
	//}
	//else if((wcscmp(animClipName, L"Assets/modelData/MawAttack.tka") == 0 &&m_isAttack))
	//{
	//	m_isAttack = false;
	//}
}
//初期化
void CMaw::Init(CVector3 position)
{
	//ステータスを設定
	m_status.Strength = 10;
	m_status.Defense = 0;
	m_status.Hp = 50;
	m_status.MaxHp = m_status.Hp;
	m_status.Gold = 100;

	//キャラコンの設定
	const float Height = 10.0f;
	const float radius = 3.0f;
	const float Gravity = -9.8f;

	//ライトの設定
	const CVector4 AmbientLight = { 0.5f,0.5f,0.5f,1.0f };
	const CVector4 DiffuseLight= { 1.0f,1.0f,1.0f,1.0f };
	const CVector4 DiffuseLightDir= { 0.0f, -1.0f, 1.0f, 1.0f };

	//プレイヤーのスキンンモデルのロード
	m_skinModel.Load(L"Assets/modelData/Maw.cmo", &m_animation);
	m_skinModel.LoadNormalmap(L"Assets/modelData/MAW_normal.png");

	m_position = position;
	m_characterController.Init(radius,Height, m_position);
	m_characterController.SetGravity(Gravity);
	//ライトの設定
	Light().SetAmbientLight(AmbientLight);
	Light().SetDiffuseLight(0,DiffuseLight);
	Light().SetDiffuseLightDir(0,DiffuseLightDir);

	//アニメーションの初期化
	{
		wchar_t* animClip[EnMawState::enState_Num] = {
			{ L"Assets/modelData/MawStand.tka"},	//待機アニメーション	
			{ L"Assets/modelData/MawWalk.tka" },	//歩行アニメーション
			{ L"Assets/modelData/MawAttack.tka" },	//攻撃アニメーション
			{ L"Assets/modelData/MawDamage.tka" },	//ダメージアニメーション
			{ L"Assets/modelData/MawDeath.tka" },	//死亡アニメーション
		};

		m_animation.Init(animClip, EnMawState::enState_Num);
		m_animation.SetLoopFlg(EnMawState::enState_Idle, true);
		m_animation.SetLoopFlg(EnMawState::enState_Walk, true);
		//最初に流すアニメーションを歩きに設定
		m_animation.Play(EnMawState::enState_Walk);
		//アニメーションイベントリスナーの登録　呼び出される関数の登録
		m_animation.AddAnimationEvent([&](auto animClipname, auto eventName) {
			OnInvokeAnimationEvent(animClipname, eventName);
		});
	}
	//最初の行動を選択
	//ActionStateOrder();
	m_actionPattern = EnMawActionPattern::enActionPatternFind;
}
//更新
void CMaw::Update()
{
	//行動パターンの選択
	switch (m_actionPattern)
	{
	case EnMawActionPattern::enActionPatternAttack:
		//通常攻撃
		Attack();
		break;
	case EnMawActionPattern::enActionPatternSpecialAttack:
		//特殊攻撃
		SpecialAttack();
		//次の行動の選択
		ActionStateOrder();
		break;
	case EnMawActionPattern::enActionPatternDown:
		//ダウン状態
		Down();
		break;
	case EnMawActionPattern::enActionPatternFind:
		//プレイヤーを探す回転など
		Find();
		break;
	case EnMawActionPattern::enActionPatternStand:
		//待機状態
		Stand();
		//次の行動の選択
		ActionStateOrder();
		break;
	case EnMawActionPattern::enActionPatternDeath:
		//死亡状態
		Death();
		break;
	default:
		break;
	}
	//ダウンさせるかつ死亡状態じゃなかったら
	if (m_isDown&&m_actionPattern !=EnMawActionPattern::enActionPatternDeath)
	{
		//ダウン状態へ
		m_actionPattern = EnMawActionPattern::enActionPatternDown;
	}

	//ダメージ間隔が0以上だったら
	if (m_damageInterval >= 0.0f)
	{
		m_damageInterval -= GameTime().GetDeltaFrameTime();
	}
	///////////////////////////////テスト用
	//攻撃時間が終わったら
	float MaxAttackTime = 3.0f;
	if (m_attackTime > MaxAttackTime)
	{
		m_attackTime = 0.0f;
		m_isAttack = false;
	}

	//攻撃していたら
	if (m_isAttack)
	{
		m_attackTime += GameTime().GetDeltaFrameTime();
	}

	//ボスの体が落ちるオブジェクトに触れていたら
	//if (m_characterController.GetGroundCollisionObject() != nullptr)
	//{
	//	//接触している地面のオブジェクトがCF_KINEMATIC_OBJECTだったら
	//	if (m_characterController.GetGroundCollisionObject()->getUserIndex() == m_characterController.GetGroundCollisionObject()->CF_KINEMATIC_OBJECT)
	//	{
	//		m_isBreakObjectHit = true;
	//	}

	//}
	/////////////////////////////////////////////////

	//キャラコンへの座標設定
	m_characterController.SetPosition(m_position);
	//キャラコンの実行
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	//座標をキャラコンから取得
	m_position=m_characterController.GetPosition();

	//アニメーションの更新
	m_animation.Update(GameTime().GetDeltaFrameTime());
	//スキンモデルの更新
	m_skinModel.Update(m_position, m_rotation,m_scale, true);
}
//行動の選択
void CMaw::ActionStateOrder()
{
	//int型ランダムを取得
	int RandomInt = Random().GetRandInt();
	//攻撃パターンの数に変更
	RandomInt %= m_attackPattern;
	//-にならないように絶対値に変換？
	RandomInt = fabs(RandomInt);
	//攻撃パターンの型に変換
	m_actionPattern = (EnMawActionPattern)RandomInt;
}
//攻撃行動
void CMaw::Attack()
{
	float interpolationTime = 0.3f;		//補間時間
	float PlayerHeight = 2.5f;			//プレイヤーの高さ
	float PlayerDamageLengthMax = 10.5f;//ダメージを受ける最大距離
	//現在のアニメーションが攻撃じゃなかったら
	if ( m_animation.GetCurrentAnimationNum() != EnMawState::enState_Attack)
	{
		//攻撃アニメーション再生
		m_animation.Play(EnMawState::enState_Attack,interpolationTime);
		m_isAttack = true;
	}
	//再生が終わっているかつ現在のアニメーションだったら
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Attack)
	{
		//次の行動の選択
		ActionStateOrder();
	}

	//プレイヤーがダメージを受けていなかったら
	if (!GetPlayer().GetIsDamage()) {
		//手のボーンのワールド行列を取得
		CVector3 leftHandPosition = GetLeftHandBone();
		//プレイヤー座標を取得
		CVector3 playerPosition = GetPlayer().GetPosition();
		//敵の攻撃との距離を計算
		CVector3 distance = leftHandPosition - playerPosition;
		float PlayerDamageLength = distance.Length();
		if (PlayerDamageLength < PlayerDamageLengthMax) {
			//プレイヤーがダメージを受けた
			GetPlayer().GetDamage();
		}
		
	}
}
//特殊攻撃
void CMaw::SpecialAttack()
{
	float interpolationTime = 0.3f;//補間時間
	//現在のアニメーションがダメージじゃなかったら
	if (m_animation.GetCurrentAnimationNum() != EnMawState::enState_Damage)
	{
		//アニメーション再生
		m_animation.Play(EnMawState::enState_Damage,interpolationTime);
	}
	//再生が終わっているかつ現在のアニメーションだったら
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Damage)
	{
		//次の行動の選択
		//ActionStateOrder();
	}
}
//ダウン状態
void CMaw::Down()
{
	float interpolationTime = 0.3f;	//補間時間
	float MaxDownTime = 50.0f;		//最大ダウン時間


	//現在のアニメーションがダウンじゃなかったら
	if ( m_animation.GetCurrentAnimationNum() != EnMawState::enState_Damage)
	{
		//アニメーション再生
		m_animation.Play(EnMawState::enState_Damage);
	}
	//再生が終わっているかつ現在のアニメーションだったら
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Damage)
	{
		//次の行動の選択
		//ActionStateOrder();
	}

	//ダウン中の攻撃をくらった時の処理
	//ここでHPバーを表示する？
	if (m_isDamage)
	{
		//ダメージ計算
		int playerStrength = GetPlayer().GetStatus().Strength;
		int damage = playerStrength - m_status.Defense;
		m_status.Hp -= damage;
		m_isDamage = false;
	}

	//HPが0以下になったら
	if (m_status.Hp <= 0)
	{
		//死亡ステートへ
		m_actionPattern = EnMawActionPattern::enActionPatternDeath;
	}
	m_downTime += GameTime().GetDeltaFrameTime();

	//最大ダウン時間を超えていたら
	if (m_downTime > MaxDownTime)
	{
		//次の行動の選択
		ActionStateOrder();
		m_downTime = 0.0f;
		m_isDown = false;
	}
}
//探す状態
void CMaw::Find()
{
	float interpolationTime = 0.3f;	//補間時間
	float FindDeg = 50.0f;			//発見範囲
	float FindLength = 15.0f;		//発見距離
	//現在のアニメーションが待機じゃなかったら
	if ( m_animation.GetCurrentAnimationNum() != EnMawState::enState_Idle)
	{
		//アニメーション再生
		m_animation.Play(EnMawState::enState_Idle,interpolationTime);
	}
	//再生が終わっているかつ現在のアニメーションだったら
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Idle)
	{
		//次の行動の選択
		ActionStateOrder();
	}
	//移動速度を取得
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();
	moveSpeed.y = 0.0f;

	CVector3 playerPos = GetPlayer().GetPosition();

	//ワールド行列からモデルの前方向を取得
	CMatrix enemyWorldMatrix = m_skinModel.GetWorldMatrix();
	CVector3 enemyForward;
	enemyForward.x = enemyWorldMatrix.m[2][0];
	enemyForward.y = 0.0f;
	enemyForward.z = enemyWorldMatrix.m[2][2];
	enemyForward.Normalize();

	CVector3 toPlayerDir = GetPlayer().GetPosition() - m_position;
	float length = toPlayerDir.Length();
	toPlayerDir.y = 0.0f;
	toPlayerDir.Normalize();

	float angle = toPlayerDir.Dot(enemyForward);
	angle = acosf(angle);

	//見つけたら
	if (fabsf(angle) < CMath::DegToRad(FindDeg) && length <FindLength) {
		//次の行動の選択
		ActionStateOrder();
	}
}
//待機状態
void CMaw::Stand()
{
	float interpolationTime = 0.3f;//補間時間
	//現在のアニメーションが待機じゃなかったら
	if ( m_animation.GetCurrentAnimationNum() != EnMawState::enState_Idle)
	{
		//アニメーション再生
		m_animation.Play(EnMawState::enState_Idle, interpolationTime);
	}
	//再生が終わっているかつ現在のアニメーションだったら
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Idle)
	{
		//次の行動の選択
		//ActionStateOrder();
	}
}
//死亡状態
void CMaw::Death()
{
	float interpolationTime = 0.3f;//補間時間
	//現在のアニメーションが死亡じゃなかったら
	if (m_animation.GetCurrentAnimationNum() != EnMawState::enState_Death)
	{
		//アニメーション再生
		m_animation.Play(EnMawState::enState_Death, interpolationTime);
	}
	//再生が終わっているかつ現在のアニメーションだったら
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Death)
	{
		//次の行動の選択
		//ActionStateOrder();
		//クリアシーンへ遷移？

		//this->SetIsActive(false);
	}
}
//ダメージ処理
void CMaw::SetIsDamage(bool isDamage)
{
	//ダメージ間隔が0より大きかったら
	if (m_damageInterval > 0.0f) { return; }
	float	MaxInterval = 5.0f;	//最大ダメージ間隔
	int		MaxDownCount = 3;	//最大ダウンカウント
	m_isDamage = isDamage;
	//ダウンしていなかったら
	if (!m_isDown)
	{
		m_downCount++;
		m_isDamage = false;
	}

	//ダウンカウントが最大ダウンカウントより大きかったら
	if (m_downCount > MaxDownCount)
	{
		m_isDown = true;//ダウンさせる
		m_downCount = 0;
	}
	//ダメージ間隔を最大にする
	m_damageInterval = MaxInterval;
}
//描画
void CMaw::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}