#include "stdafx.h"
#include "Maw.h"
#include "../Camera/GameCamera.h"
#include "../Player/Player.h"
#include "../UI/BossHp/BossHp.h"
#include "../UI/WeekPoint/WeekPoint.h"
#include "../Scene/SceneManager.h"
#include"../GameSound/GameSound.h"

CMaw *CMaw::m_maw = NULL;

//ダメージアニメーションは入れないようにしてダウンのアニメーションだけにする？
//攻撃モーションを複数入れたい
//

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
	//もう一度呼ばれる間攻撃判定をオンにしておく
	if (wcscmp(animClipName, L"Assets/modelData/MawAttack.tka") == 0&&!m_isAttack) 
	{
		m_isAttack = true;
	}
	else if((wcscmp(animClipName, L"Assets/modelData/MawAttack.tka") == 0 &&m_isAttack))
	{
		m_isAttack = false;
	}

	//もう一度呼ばれる間攻撃判定をオンにしておく
	if (wcscmp(animClipName, L"Assets/modelData/MawSpecialAttack.tka") == 0 && !m_isAttack)
	{
		m_isAttack = true;
	}
	else if ((wcscmp(animClipName, L"Assets/modelData/MawSpecialAttack.tka") == 0 && m_isAttack))
	{
		m_isAttack = false;
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
	m_status.Hp = 50;
	m_status.MaxHp = m_status.Hp;
	m_status.Gold = 100;

	//キャラコンの設定
	const float Height = 12.0f;
	const float radius = 4.0f;
	const float Gravity = -9.8f;

	//ライトの設定
	const CVector4 AmbientLight = { 0.5f,0.5f,0.5f,1.0f };
	const CVector4 DiffuseLight= { 1.0f,1.0f,1.0f,1.0f };
	const CVector4 DiffuseLightDir= { 0.0f, -1.0f, 1.0f, 1.0f };

	//プレイヤーのスキンンモデルのロード
	m_skinModel.Load(L"Assets/modelData/Maw.cmo", &m_animation);
	//m_skinModel.LoadNormalmap(L"Assets/modelData/MAW_normal.png");

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
			{ L"Assets/modelData/MawStand.tka"},			//待機アニメーション	
			{ L"Assets/modelData/MawWalk.tka" },			//歩行アニメーション
			{ L"Assets/modelData/MawAttack2.tka" },			//攻撃アニメーション
			{ L"Assets/modelData/MawSpecialAttack2.tka" },	//攻撃アニメーション
			{ L"Assets/modelData/MawDamage.tka" },			//ダメージアニメーション
			{ L"Assets/modelData/MawDown.tka" },			//ダウンアニメーション
			{ L"Assets/modelData/MawDeath.tka" },			//死亡アニメーション
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
	//弱点の頭のボーンを取得
	CMatrix WeekMat = m_skinModel.FindBoneWorldMatrix(L"Head");
	m_weekPosition.x = WeekMat.m[3][0];
	m_weekPosition.y = WeekMat.m[3][1];
	m_weekPosition.z = WeekMat.m[3][2];
	//m_weekPosition.Normalize();
	//最初の行動を選択
	m_actionPattern = EnMawActionPattern::enActionPatternIdle;

	m_weekPoint->SetIsActive(false);
	m_bossHp->SetIsActive(false);
	SetIsActive(true);
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
		break;
	case EnMawActionPattern::enActionPatternDown:
		//ダウン状態
		Down();
		break;
	case EnMawActionPattern::enActionPatternSearch:
		//プレイヤーを探す回転など
		Search();
		break;
	case EnMawActionPattern::enActionPatternIdle:
		//待機状態
		Idle();
		break;
	case EnMawActionPattern::enActionPatternDeath:
		//死亡状態
		Death();
		break;
	default:
		break;
	}

	//弱点描画の更新
	WeekPointUpdate();

	
	//弱点の頭のボーンを取得
	CMatrix WeekMat=m_skinModel.FindBoneWorldMatrix(L"Head");
	m_weekPosition.x = WeekMat.m[3][0];
	m_weekPosition.y = WeekMat.m[3][1];
	m_weekPosition.z = WeekMat.m[3][2];
	
	//ダメージ間隔が0以上だったら
	if (m_damageInterval >= 0.0f&&!m_isDeath)
	{
		m_damageInterval -= GameTime().GetDeltaFrameTime();
	}

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
	if (angle > 0.0f&&length<40.0f)
	{
		m_weekPoint->SetIsActive(true);
		
	}
	else
	{
		m_weekPoint->SetIsActive(false);
	}



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
	const float PlayerDamageLengthMax = 8.5f;//プレイヤーにダメージを与える最大距離

	//アニメーション再生
	bool IsAnim=Anim(EnMawState::enState_Attack);
	
	//攻撃が終わっていたら
	if (!IsAnim)
	{
		//索敵ステートへ
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
	}

	HandAttack(PlayerDamageLengthMax);
}
//特殊攻撃
void CMaw::SpecialAttack()
{
	const float PlayerDamageLengthMax = 7.5f;//プレイヤーにダメージを与える最大距離

	//アニメーション再生
	bool IsAnim = Anim(EnMawState::enState_SpecialAttack);

	//攻撃が終わっていたら
	if (!IsAnim)
	{
		//索敵ステートへ
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
	}

	HandAttack(PlayerDamageLengthMax);
}

//ダウン状態
void CMaw::Down()
{
	const float MaxDownTime = 10.0f;		//最大ダウン時間

	//アニメーション再生
	Anim(EnMawState::enState_Down);
	m_bossHp->SetIsActive(true);
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
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
		//ActionStateOrder();
		m_downTime = 0.0f;
		m_isDown = false;
		m_weekPoint->SetIsActive(true);
		m_bossHp->SetIsActive(false);
	}
}

//探す状態
void CMaw::Search()
{
	const float AttackDeg = 40.0f;			//攻撃範囲
	const float SpecialAttackDeg = 30.0f;	//強つよ攻撃範囲
	const float FindLength = 18.0f;			//発見距離

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
		m_actionPattern = EnMawActionPattern::enActionPatternSpecialAttack;
	}
	else if (fabsf(angle) < CMath::DegToRad(AttackDeg) && length < FindLength)
	{
		//見つけて攻撃範囲に入ったら	//見つけて攻撃範囲に入ったら
		m_actionPattern = EnMawActionPattern::enActionPatternAttack;
	}
	else
	{
		
		//見つけれなかったら探す
		CQuaternion addRot;
		const float RotSpeed = 0.01f;
		//Y軸のクォータニオンを作成
		addRot.SetRotation(CVector3::AxisY,RotSpeed);

		CQuaternion rot = m_rotation;
		//クォータニオンを乗算
		rot.Multiply(rot, addRot);
		m_rotation = rot;

	}
	//const float LengeAttackLength = 30.0f;		//遠距離攻撃距離
	//const float StandLength = 75.0f;			//戦闘終了距離
	////遠距離攻撃アニメーション
	////Anim(EnMawState::enState_Idle);

	//CVector3 toPlayerDir = GetPlayer().GetPosition() - m_position;
	//float length = toPlayerDir.Length();

	////プレイヤーが遠くに離れたら
	//if (length > StandLength)
	//{
	//	//待機ステートへ
	//	m_actionPattern = EnMawActionPattern::enActionPatternIdle;
	//}
	//else if (length > LengeAttackLength)
	//{
	//	//遠距離攻撃ステートへ
	//}
}

//待機状態
void CMaw::Idle()
{
	const float SearchLength = 70.0f;//範囲距離
	//アニメーション
	Anim(EnMawState::enState_Idle);

	CVector3 toPlayerDir = GetPlayer().GetPosition() - m_position;
	float length = toPlayerDir.Length();

	//プレイヤーが近くに来たら
	if (length < SearchLength)
	{
		//索敵ステートへ
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
		m_isBattle = true;
	}
}

//死亡状態
void CMaw::Death()
{
	//死亡アニメーション
	bool IsAnim = Anim(EnMawState::enState_Death);
	if (!IsAnim)
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
	//プレイヤーがダメージを受けていなかったら
	if (GetPlayer().GetIsDamage()) { return; }

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
		//プレイヤーがダメージを受けた
		GetPlayer().SetDamage(m_status.Strength);
	}
	
}

//ダメージ処理
void CMaw::SetIsDamage(bool isDamage)
{
	//ダメージ間隔が0より大きかったら
	if (m_damageInterval > 0.0f) { return; }
	const float		MaxInterval = 5.0f;	//最大ダメージ間隔
	const int		MaxDownCount = 0;	//最大ダウンカウント

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
		//ダウンさせる
		m_isDamage = isDamage;
		m_actionPattern = EnMawActionPattern::enActionPatternDown;
		m_isDown = true;
		m_weekPoint->SetIsActive(false);
		m_downCount = 0;
	}
	//ダメージ間隔を最大にする
	m_damageInterval = MaxInterval;
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