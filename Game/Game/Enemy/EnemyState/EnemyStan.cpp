#include "EnemyStan.h"
#include "../IEnemy.h"
#include "../../UI/DamageNumber/DamageNumber.h"

bool CEnemyStan::Start()
{
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Down, 0.3f);

	//タイマーを初期化
	m_timer = 0.0f;

	//移動速度を設定
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	//ダメージを受けたフラグを戻す
	m_enemy->SetIsDamage(false);

	return true;
}

void CEnemyStan::Update()
{
	//剛体の座標を更新する
	const CMatrix* spineMatrix = m_enemy->GetWorldMatrixSpine();
	CVector3 position;
	position.x = spineMatrix->m[3][0];
	position.y = spineMatrix->m[3][1];
	position.z = spineMatrix->m[3][2];
	m_enemy->GetCharacterController().SetPosition(position);

	//ダメージを受けたか判定する
	if (m_enemy->GetIsDamage())
	{
		//ダメージ数値を初期化
		m_damageNumber = New<CDamageNumber>(PRIORITY_UI);
		m_damageNumber->Init(m_enemy);
		//ダメージを受けたフラグを戻す
		m_enemy->SetIsDamage(false);
	}

	if (!m_enemy->GetAnimation().IsPlay()
		&& m_enemy->GetAnimation().GetCurrentAnimationNum() == CEnemyState::enAnimation_Down)
	{
		//ダウン中はタイマーをカウントする
		m_timer += GameTime().GetDeltaFrameTime();
	}

	const int DOWN_TIME = 3.0f;
	if (m_timer > DOWN_TIME)
	{
		//移動しているので座標を更新
		m_enemy->SetPosition(position);
		//タイマーが一定値を超えたら立ち上がる
		m_enemy->GetAnimation().Play(CEnemyState::enAnimation_StandUp);
		m_timer = 0.0f;
	}

	if (!m_enemy->GetAnimation().IsPlay()
		&& m_enemy->GetAnimation().GetCurrentAnimationNum() == CEnemyState::enAnimation_StandUp) 
	{
		//立ち上がったら追跡状態にする
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
	else if (m_enemy->GetStatus().hp <= 0)
	{
		//HPがなければ死亡する
		m_esm->ChangeState(CEnemyState::enState_Death);
	}
}
