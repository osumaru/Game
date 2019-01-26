#include "stdafx.h"
#include"../../Game/Camera/GameCamera.h"
#include "../Scene/SceneManager.h"
#include "../Map/Map.h"
#include "../Enemy/IEnemy.h"
#include "PlayerArrow.h"
#include "Player.h"
#include "../Enemy/Maw.h"

CPlayerArrow::CPlayerArrow()
{
}


CPlayerArrow::~CPlayerArrow()
{

}
//矢の初期化
bool CPlayerArrow::Start()
{
	m_arrowskin.Load(L"Assets/modelData/Arrow.cmo", NULL);
	m_scale = ARROW_SCALE;
	return true;
}

void CPlayerArrow::Update()
{
	bool deleteFlg = false;
	if (GetPlayer().GetStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerStateArrowAttack && !m_isMove)
	{
		m_arrowPosition =  *((CVector3*)GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"LeftHand").m[3]);
		//プレイヤーの前方向を取得
		const CMatrix& playerWorldMat = GetPlayer().GetSkinmodel().GetSkelton()->GetBoneWorldMatrix(GetPlayer().GetSpineBoneID());
		CVector3 weaponFlont;
		weaponFlont.x = playerWorldMat.m[0][0];
		weaponFlont.y = playerWorldMat.m[0][1];
		weaponFlont.z = playerWorldMat.m[0][2];
		weaponFlont.Normalize();
		const CMatrix& skinWorldMatrix = m_arrowskin.GetWorldMatrix();
		m_moveSpeed.x = skinWorldMatrix.m[2][0];
		m_moveSpeed.y = skinWorldMatrix.m[2][1];
		m_moveSpeed.z = skinWorldMatrix.m[2][2];
		m_moveSpeed.Normalize();
		m_moveSpeed *= MOVE_POWRE;
		CQuaternion rotY;
		m_arrowRot.SetRotation(CVector3::AxisY, atan2f(weaponFlont.x, weaponFlont.z));		//Y軸周りの回転
		rotY.SetRotation(CVector3::AxisX, atanf(-weaponFlont.y));		//X軸周りの回転
		CQuaternion multi;
		multi.SetRotation(CVector3::AxisX, CMath::DegToRad(-10.0f));
		m_arrowRot.Multiply(rotY);
		m_arrowRot.Multiply(multi);
	}
	//矢を飛ばす処理
	else
	{
		m_isMove = true;
		CVector3 flont, newVec,oldpos;
		//弓の前方向
		flont = { m_arrowskin.GetWorldMatrix().m[2][0],m_arrowskin.GetWorldMatrix().m[2][1],m_arrowskin.GetWorldMatrix().m[2][2] };
		//１フレーム前の座標
		oldpos = m_arrowPosition;
		//目標位置の計算
		m_moveSpeed.y += GRAVITY * GameTime().GetDeltaFrameTime();
		m_arrowPosition += m_moveSpeed * GameTime().GetDeltaFrameTime();
		//今の座標から目標地点に向かうベクトル
		newVec = m_arrowPosition - oldpos;
		//正規化
		newVec.Normalize();
		flont.Normalize();
		float rot = flont.Dot(newVec);
		rot = acos(rot) ;
		CQuaternion rotX = CQuaternion::Identity;
		rotX.SetRotation(CVector3::AxisX, CMath::DegToRad( rot));
		m_arrowRot.Multiply(rotX);
		m_lifeTime += GameTime().GetDeltaFrameTime();

		//敵との当たり判定の計算
		for (const auto& enemys :GetSceneManager().GetGameScene().GetMap()->GetEnemyList())
		{
			if (!enemys->GetIsDamage()) {

				//CVector3 EnemyVec = enemys->GetPosition();
				//EnemyVec.y += OFFSET_Y;
				const CMatrix* enemySpineMatrix = enemys->GetWorldMatrixSpine();
				CVector3 EnemyVec;
				EnemyVec.x = enemySpineMatrix->m[3][0];
				EnemyVec.y = enemySpineMatrix->m[3][1];
				EnemyVec.z = enemySpineMatrix->m[3][2];
				EnemyVec.Subtract(m_arrowPosition);
				float len = EnemyVec.Length();

				if (fabs(len) < HIT_LENGTH)
				{
					enemys->SetIsDamage(true);
					deleteFlg = true;
					m_effect.Init(L"Assets/Effect/DamageEffect.efk");
					m_effect.Play();
					CVector3 effectPos = m_arrowPosition;
					effectPos.y += 1.0f;
					m_effect.SetPosition(effectPos);
					const float SCALE = 0.1f;
					m_effect.SetScale({ SCALE, SCALE, SCALE });
					m_effect.Update();
					break;
				}

			}
		}

		//ボスが作られていたら
		if (&GetMaw() != NULL)
		{
		
		//ボスがダメージを受けていなかったら
			if (!GetMaw().GetIsDamage()) {
				//ダウンしていなかったら
				if (!GetMaw().GetIsDown())
				{
					const float BossWeekLenge = 3.0f;
					//ボスの弱点の座標取得
					CVector3 EnemyVec = GetMaw().GetWeekPosition();
					EnemyVec -= m_arrowPosition;
					float len = EnemyVec.Length();

					//弱点との判定
					if (fabs(len) < BossWeekLenge)
					{
						GetMaw().SetIsDamage(true);
						deleteFlg = true;
						m_effect.Init(L"Assets/Effect/DamageEffect.efk");
						m_effect.Play();
						CVector3 effectPos = m_arrowPosition;
						effectPos.y += 1.0f;
						m_effect.SetPosition(effectPos);
						const float SCALE = 0.1f;
						m_effect.SetScale({ SCALE, SCALE, SCALE });
						m_effect.Update();
					}
				}
				else
				{
					const float BossHeight = 3.0f;
					const float BossLenge = 3.0f;
					//ボスの座標取得
					CVector3 EnemyVec = GetMaw().GetPosition();
					EnemyVec.y += BossHeight;
					EnemyVec -= m_arrowPosition;
					float len = EnemyVec.Length();
					//ボスとの判定
					if (fabs(len) < BossLenge)
					{
						GetMaw().SetIsDamage(true);
						deleteFlg = true;
						m_effect.Init(L"Assets/Effect/DamageEffect.efk");
						m_effect.Play();
						CVector3 effectPos = m_arrowPosition;
						effectPos.y += 1.0f;
						m_effect.SetPosition(effectPos);
						const float SCALE = 0.1f;
						m_effect.SetScale({ SCALE, SCALE, SCALE });
						m_effect.Update();
					}
				}
			}
		}
		
	}
	
	if (m_lifeTime >= ARROW_LIFE)
	{
		deleteFlg = true;
	}
	if(deleteFlg)
	{
		Delete(this);
		return;
	}

	m_arrowskin.Update(m_arrowPosition, m_arrowRot, m_scale);
}

void CPlayerArrow::Draw()
{
	m_arrowskin.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}