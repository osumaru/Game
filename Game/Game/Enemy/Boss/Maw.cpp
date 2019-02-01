#include "stdafx.h"
#include "Maw.h"
#include "../../Camera/GameCamera.h"
#include "../../Player/Player.h"
#include "../../UI/BossHp/BossHp.h"
#include "../../UI/WeekPoint/WeekPoint.h"
#include "../../Scene/SceneManager.h"
#include "../../GameSound/GameSound.h"
#include "AttackWave.h"

CMaw *CMaw::m_maw = NULL;

CMaw::CMaw()
{
	this->SetIsActive(false);
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
	//攻撃判定を切り替える
	if (wcscmp(animClipName, L"Assets/modelData/MawAttack.tka") == 0) 
	{
		m_isAttack = !m_isAttack;
	}

	//攻撃判定を切り替える
	if (wcscmp(animClipName, L"Assets/modelData/MawSpecialAttack.tka") == 0)
	{
		
		if (m_isAttack)
		{
			SpecialAttackEnd();
		}
		m_isAttack = !m_isAttack;
	}
}

//初期化
void CMaw::Init(CVector3 position)
{
	m_bossHp = New<CBossHp>(PRIORITY_UI);
	m_bossHp->Init();

	m_weekPoint = New<CWeekPoint>(PRIORITY_UI);
	m_weekPoint->Init();
	//ステータスを設定
	m_status.Strength = 10;
	m_status.Defense = 0;
	m_status.Hp = 100;
	m_status.MaxHp = m_status.Hp;
	m_status.Gold = 100;

	//キャラコンの設定
	const float Height = 3.0f;
	const float radius = 2.0f;
	const float Gravity = -9.8f;



	//プレイヤーのスキンモデルのロード
	m_skinModel.Load(L"Assets/modelData/Maw.cmo", &m_animation);
	//m_skinModel.LoadNormalmap(L"Assets/modelData/MAW_normal.png");

	m_position = position;
	m_characterController.Init(radius,Height, m_position);
	m_characterController.SetGravity(Gravity);

	//アニメーションの初期化
	{
		wchar_t* animClip[EnMawState::enState_Num] = {
			{ L"Assets/modelData/MawStand.tka"},			//待機アニメーション
			{ L"Assets/modelData/MawWalk.tka" },			//歩行アニメーション
			{ L"Assets/modelData/MawAttack.tka" },			//攻撃アニメーション
			{ L"Assets/modelData/MawSpecialAttack.tka" },	//攻撃アニメーション
			{ L"Assets/modelData/MawDamage.tka" },			//ダメージアニメーション
			{ L"Assets/modelData/MawDown.tka" },			//ダウンアニメーション
			{ L"Assets/modelData/MawDeath.tka" },			//死亡アニメーション
		};

		m_animation.Init(animClip, EnMawState::enState_Num);
		m_animation.SetLoopFlg(EnMawState::enState_Idle, true);
		m_animation.SetLoopFlg(EnMawState::enState_Walk, true);

		//アニメーションイベントリスナーの登録　呼び出される関数の登録
		m_animation.AddAnimationEvent([&](auto animClipname, auto eventName) {
			OnInvokeAnimationEvent(animClipname, eventName);
		});
		//最初に流すアニメーションを歩きに設定
		m_animation.Play(EnMawState::enState_Walk);
	}

	////エフェクトの初期化
	//m_rippleEffect.Init(L"Assets/Effect/rippleEffect.efk");
	//m_rippleEffect.SetScale({ 1.0f,1.0f,1.0f });

	//弱点の頭のボーンを取得
	CMatrix WeekMat = m_skinModel.FindBoneWorldMatrix(L"Head");
	m_weekPosition.x = WeekMat.m[3][0];
	m_weekPosition.y = WeekMat.m[3][1];
	m_weekPosition.z = WeekMat.m[3][2];

	//最初の行動を選択
	m_actionPattern = EnMawActionPattern::enActionPatternIdle;

	//ボスの下にプレイヤーが入ってしまうためプレイヤーの剛体は無視させる？
	m_characterController.SetIgnoreRigidBody(&GetPlayer().GetCharacterController().GetBody());

	m_weekPoint->SetIsActive(false);
	SetIsActive(true);
}

//更新
void CMaw::Update()
{
	//行動パターンの選択
	switch (m_actionPattern)
	{
	case EnMawActionPattern::enActionPatternAttack:
		Attack();//通常攻撃
		break;
	case EnMawActionPattern::enActionPatternSpecialAttack:
		SpecialAttack();//特殊攻撃
		break;
	case EnMawActionPattern::enActionPatternDown:
		Down();//ダウン状態
		break;
	case EnMawActionPattern::enActionPatternDamage:
		Damage();//ダメージ
		break;
	case EnMawActionPattern::enActionPatternSearch:
		Search();//プレイヤーを探す回転など
		break;
	case EnMawActionPattern::enActionPatternIdle:
		Idle();//待機状態
		break;
	case EnMawActionPattern::enActionPatternDeath:
		Death();//死亡状態
		break;
	default:
		break;
	}

	if (m_isDamage)
	{
		m_status.Hp -= 10;
		m_isDamage = false;
		//HPが0以下になったら
		if (m_status.Hp <= 0)
		{
			//死亡ステートへ
			m_actionPattern = EnMawActionPattern::enActionPatternDeath;
		}
	}

	WeekPointUpdate();//弱点の更新
	
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

//弱点描画の更新
void CMaw::WeekPointUpdate()
{
	CVector3 CameraForward = GetGameCamera().GetCamera().GetFlont();
	CameraForward.y = 0.0f;
	CameraForward.Normalize();
	CVector3 toEnemyDir = m_position - GetGameCamera().GetCamera().GetPosition();
	float length = toEnemyDir.Length();
	toEnemyDir.y = 0.0f;
	toEnemyDir.Normalize();
	float angle = toEnemyDir.Dot(CameraForward);

	//カメラの視界に入ったら
	if (angle > 0.0f && m_isDown)
	{
		m_weekPoint->SetIsActive(true);
	}
	else
	{
		m_weekPoint->SetIsActive(false);
	}

	//弱点の頭のボーンを取得
	CMatrix WeekMat = m_skinModel.FindBoneWorldMatrix(L"Head");
	m_weekPosition.x = WeekMat.m[3][0];
	m_weekPosition.y = WeekMat.m[3][1];
	m_weekPosition.z = WeekMat.m[3][2];
}

//行動の選択
//void CMaw::ActionStateOrder()
//{
//	//ランダムやめる？
//
//	/*const int AttackPattern = 2;
//	//int型ランダムを取得
//	int RandomInt = Random().GetRandInt();
//	//攻撃パターンの数に変更
//	RandomInt %= AttackPattern;
//	//-にならないように絶対値に変換？
//	RandomInt = fabs(RandomInt);
//	//攻撃パターンの型に変換
//	m_actionPattern = (EnMawActionPattern)RandomInt;
//	*/
//
//}

//攻撃行動
void CMaw::Attack()
{
	const float PlayerDamageLengthMax = 4.0f;//プレイヤーにダメージを与える最大距離
	//アニメーション再生
	bool IsAnimPlay=Anim(EnMawState::enState_Attack);
	//攻撃が終わっていたら
	if (!IsAnimPlay)
	{
		//索敵ステートへ
		m_waitTime = 0.0f;
		m_actionPattern = enActionPatternIdle;
	}
	if (m_isAttack)
	{
		HandAttack(PlayerDamageLengthMax);
	}
}

//特殊攻撃
void CMaw::SpecialAttack()
{
	const float PlayerDamageLengthMax = 2.5f;//プレイヤーにダメージを与える最大距離
	//アニメーション再生
	bool IsAnimPlay = Anim(EnMawState::enState_SpecialAttack);

	if (m_isAttack)
	{
		HandAttack(PlayerDamageLengthMax);
		m_isSpecialAttackRot = false;
	}
	if(m_isSpecialAttackRot)
	{
		CVector3 playerVec = GetPlayer().GetPosition() - m_position;
		Rotation(playerVec);
	}
	//攻撃が終わっていたら
	if (!IsAnimPlay)
	{
		//索敵ステートへ
		m_actionPattern = EnMawActionPattern::enActionPatternDown;
		m_isDown = true;
		m_isSpecialAttackRot = true;
	}
}

void CMaw::SpecialAttackEnd()
{
	//const CMatrix handMatrix = m_skinModel.FindBoneWorldMatrix(L"LeftHand");
	//float offsetY = 0.01f;
	//CVector3 handPosition;
	//handPosition.x = handMatrix.m[3][0];
	//handPosition.y = m_position.y + offsetY;
	//handPosition.z = handMatrix.m[3][2];
	//m_rippleEffect.SetPosition(handPosition);
	//m_rippleEffect.Play();
	//m_rippleEffect.Update();

	CAttackWave* wave = New<CAttackWave>(PRIORITY_PARTICLE);
	const CMatrix handMatrix = m_skinModel.FindBoneWorldMatrix(L"LeftHand");
	float offsetY = 0.01f;
	CVector3 handPosition;
	handPosition.x = handMatrix.m[3][0];
	handPosition.y = m_position.y + offsetY;
	handPosition.z = handMatrix.m[3][2];
	wave->Init(&GetGameCamera().GetCamera(), handPosition);

	CShakeCamera& shakeCamera = GetGameCamera().GetShakeCamera();
	shakeCamera.SetDamping(0.7f);
	shakeCamera.ShakeStart(0.7f);
}
//ダウン状態
void CMaw::Down()
{
	m_characterController.SetMoveSpeed(CVector3::Zero);
	const float MaxDownTime = 3.0f;	//最大ダウン時間
	//アニメーション再生
	Anim(EnMawState::enState_Down);

	//最大ダウン時間を超えていたら
	if (m_downTime > MaxDownTime)
	{
		m_downTime = 0.0f;
		m_isDown = false;
		//次の行動の選択
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
	}
	//ダウン中の攻撃をくらった時の処理
	//ここでHPバーを表示する？
	if (m_isDamage)
	{
		GameTime().SetFadeOutTime(0.5f);
		GameTime().SetSlowDelayTime(0.3f, 0.1f, 0.06f);
		//ダメージ計算
		int playerStrength = GetPlayer().GetStatus().Strength;
		int damage = playerStrength - m_status.Defense;
		damage *= 3;
		m_status.Hp -= damage;
		m_isDamage = false;

		m_downTime = 0.0f;
		m_isDown = false;
		//次の行動の選択
		m_actionPattern = EnMawActionPattern::enActionPatternDamage;
			
		//HPが0以下になったら
		if (m_status.Hp <= 0)
		{
			//死亡ステートへ
			m_actionPattern = EnMawActionPattern::enActionPatternDeath;
		}
	}
	m_downTime += GameTime().GetDeltaFrameTime();
}


void CMaw::Damage()
{
	//アニメーション再生
	bool IsAnimPlay = Anim(EnMawState::enState_Damage);
	//終わっていたら
	if (!IsAnimPlay)
	{
		//索敵ステートへ
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
	}
}

//探す状態
void CMaw::Search()
{
	const float AttackDeg = 40.0f;			//攻撃範囲
	const float SpecialAttackDeg = 15.0f;	//強つよ攻撃範囲
	const float FindLength = 3.0f;			//発見距離

	//アニメーション再生
	Anim(EnMawState::enState_Walk);

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

	//見つけて強攻撃範囲に入ったら
	if (fabsf(angle) < CMath::DegToRad(SpecialAttackDeg) && length < FindLength)
	{
		//移動をやめる
		m_characterController.SetMoveSpeed(CVector3::Zero);
		m_actionPattern = EnMawActionPattern::enActionPatternSpecialAttack;
	}
	else if (fabsf(angle) < CMath::DegToRad(AttackDeg) && length < FindLength)
	{
		//移動をやめる
		m_characterController.SetMoveSpeed(CVector3::Zero);
		//見つけて攻撃範囲に入ったら
		m_actionPattern = EnMawActionPattern::enActionPatternAttack;
	}
	else
	{
		float Speed = 2.5f;
		CVector3 moveSpeed = m_characterController.GetMoveSpeed();
		toPlayerDir *= Speed;
		moveSpeed.x = toPlayerDir.x;
		moveSpeed.z = toPlayerDir.z;
		m_characterController.SetMoveSpeed(moveSpeed);
		Rotation(m_characterController.GetMoveSpeed());
	}
}

//回転
void CMaw::Rotation(const CVector3& rotVec)
{
	CMatrix worldMatrix = m_maw->GetWorldMatrix();
	CVector3 forwardXZ;
	forwardXZ.x = worldMatrix.m[2][0];
	forwardXZ.y = 0.0f;
	forwardXZ.z = worldMatrix.m[2][2];
	forwardXZ.Normalize();

	//移動速度を取得
	CVector3 moveSpeed = rotVec;
	moveSpeed.y = 0.0f;
	if (moveSpeed.LengthSq() < 0.01f) {
		//移動していないと角度の計算ができないので返す
		return;
	}
	moveSpeed.Normalize();
	float angle = moveSpeed.Dot(forwardXZ);
	angle = max(-1.0f, min(1.0f, angle));
	angle = acosf(angle);
	CVector3 directionJudge;
	directionJudge.Cross(moveSpeed, forwardXZ);
	if (0.0f < directionJudge.y)
	{
		angle = -angle;
	}
	CQuaternion addRot;
	addRot.SetRotation(CVector3::AxisY, angle);
	addRot.Slerp(0.3f, CQuaternion::Identity, addRot);
	CQuaternion rot = m_rotation;
	rot.Multiply(rot, addRot);
	m_rotation = rot;
}

//待機状態
void CMaw::Idle()
{
	const float SearchLength = 60.0f;//範囲距離
	//アニメーション
	Anim(EnMawState::enState_Idle);

	CVector3 toPlayerDir = GetPlayer().GetPosition() - m_position;
	float length = toPlayerDir.Length();
	const float MAX_WAIT_TIME = 2.0f;
	if (m_waitTime < MAX_WAIT_TIME)
	{
		m_waitTime += GameTime().GetDeltaFrameTime();
	}
	else
	{
		//プレイヤーが近くに来たら
		if (length < SearchLength)
		{
			//索敵ステートへ
			m_actionPattern = EnMawActionPattern::enActionPatternSearch;
			m_isBattle = true;
		}
	}
}

//死亡状態
void CMaw::Death()
{
	//死亡アニメーション
	bool IsAnimPlay = Anim(EnMawState::enState_Death);
	//終わっていたら
	if (!IsAnimPlay)
	{
		//クリアシーンへ遷移
		GetSceneManager().ChangeScene(GetSceneManager().enClearScene);
	}
}

//アニメーション
bool CMaw::Anim(EnMawState animState)
{
	const float InterpolationTime = 0.3f;//補間時間
	//現在のアニメーションじゃなかったら
	if (m_animation.GetCurrentAnimationNum() != animState)
	{
		//アニメーション再生
		m_animation.Play(animState,InterpolationTime);
		return true;
	}
	//再生が終わっているかつ現在のアニメーションだったら
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() ==animState)
	{
		return false;
	}
	return true;
}

//手での攻撃
void CMaw::HandAttack(float DamageLength)
{
	//プレイヤーがダメージを受けていたら
	if (GetPlayer().GetStanDamage()) { return; }

	float PlayerDamageLengthMax=DamageLength;
	//手のボーンのワールド行列を取得
	CMatrix BossLeftHandMat = m_skinModel.FindBoneWorldMatrix(L"RightHand");
	CVector3 BossLeftHandPos;
	BossLeftHandPos.x = BossLeftHandMat.m[3][0];
	BossLeftHandPos.y = BossLeftHandMat.m[3][1];
	BossLeftHandPos.z = BossLeftHandMat.m[3][2];
	//プレイヤー座標を取得
	CVector3 playerPosition = GetPlayer().GetPosition();
	//敵の攻撃との距離を計算
	CVector3 distance = BossLeftHandPos - playerPosition;
	float PlayerDamageLength = distance.Length();
	if (PlayerDamageLength < PlayerDamageLengthMax) {
		//プレイヤーにスタンダメージを与える
		GetPlayer().SetStanDamage(m_status.Strength);
	}
}

//ダメージ処理
void CMaw::SetIsDamage(bool isDamage)
{
	m_isDamage = isDamage;
	m_characterController.SetMoveSpeed(CVector3::Zero);

}

//描画
void CMaw::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	//剛体描画
	m_characterController.Draw();
}

//死亡する前に呼ばれる関数
void CMaw::BeforeDead()
{
	Delete(m_bossHp);
	Delete(m_weekPoint);
}