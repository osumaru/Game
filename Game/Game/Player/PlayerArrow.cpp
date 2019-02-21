#include "stdafx.h"
#include"../../Game/Camera/GameCamera.h"
#include "../Scene/SceneManager.h"
#include "../Map/Map.h"
#include "../Enemy/IEnemy.h"
#include "PlayerArrow.h"
#include "Player.h"
#include "../Enemy/Boss/Maw.h"

CPlayerArrow::CPlayerArrow()
{
}


CPlayerArrow::~CPlayerArrow()
{

}
//矢の初期化
bool CPlayerArrow::Start()
{
	m_skinmodel.Load(L"Assets/modelData/Arrow.cmo", NULL);
	m_scale = ARROW_SCALE;
	return true;
}

void CPlayerArrow::Update()
{
	bool deleteFlg = false;
	if (GetPlayer().GetStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerStateArrowAttack && !m_isMove)
	{
		m_position =  *((CVector3*)GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"LeftHand").m[3]);
		//プレイヤーのボーンの前方向を取得
		const CMatrix& playerBoneWorldMat = GetPlayer().GetSkinmodel().GetSkelton()->GetBoneWorldMatrix(GetPlayer().GetSpineBoneID());
		CVector3 weaponFlont;
		weaponFlont.x = playerBoneWorldMat.m[0][0];
		weaponFlont.y = playerBoneWorldMat.m[0][1];
		weaponFlont.z = playerBoneWorldMat.m[0][2];
		weaponFlont.Normalize();
		const CMatrix& playerWorldMat = GetPlayer().GetSkinmodel().GetWorldMatrix();
		CVector3 playerFront;
		playerFront.x = playerWorldMat.m[2][0];
		playerFront.y = playerWorldMat.m[2][1];
		playerFront.z = playerWorldMat.m[2][2];
		playerFront.Normalize();
		//矢の前方向を取得
		const CMatrix& skinWorldMatrix = m_skinmodel.GetWorldMatrix();
		m_moveSpeed.x = skinWorldMatrix.m[2][0];
		m_moveSpeed.y = skinWorldMatrix.m[2][1];
		m_moveSpeed.z = skinWorldMatrix.m[2][2];
		m_moveSpeed.Normalize();
		m_moveSpeed *= MOVE_POWRE;
		CQuaternion rotY;
		m_rotation.SetRotation(CVector3::AxisY, atan2f(playerFront.x, playerFront.z));		//Y軸周りの回転
		rotY.SetRotation(CVector3::AxisX, atanf(-weaponFlont.y));		//X軸周りの回転
		//回転の補正、ボーンの回転をそのまま使うと変な方向を向くため
		CQuaternion multi;
		multi.SetRotation(CVector3::AxisX, CMath::DegToRad(-10.0f));
		m_rotation.Multiply(rotY);
		m_rotation.Multiply(multi);
	}
	//矢を飛ばす処理
	else
	{
		m_isMove = true;
		CVector3 flont, newVec,oldpos;
		//弓の前方向
		flont = { m_skinmodel.GetWorldMatrix().m[2][0],m_skinmodel.GetWorldMatrix().m[2][1],m_skinmodel.GetWorldMatrix().m[2][2] };
		//１フレーム前の座標
		oldpos = m_position;
		//目標位置の計算
		m_moveSpeed.y += GRAVITY * GameTime().GetDeltaFrameTime();
		m_position += m_moveSpeed * GameTime().GetDeltaFrameTime();
		//今の座標から目標地点に向かうベクトル
		newVec = m_position - oldpos;
		//正規化
		newVec.Normalize();
		flont.Normalize();
		float rot = flont.Dot(newVec);
		rot = acos(rot) ;
		CQuaternion rotX = CQuaternion::Identity;
		rotX.SetRotation(CVector3::AxisX, CMath::DegToRad( rot));
		m_rotation.Multiply(rotX);
		m_lifeTime += GameTime().GetDeltaFrameTime();
		CVector3 areaPos = m_position;
		Map* map = GetSceneManager().GetMap();
		int areaPosX = map->GetAreaPosX(areaPos);
		int areaPosY = map->GetAreaPosY(areaPos);
		std::list<MapChip*>& mapChips = map->GetMapChips(areaPosX, areaPosY);
		//敵との当たり判定の計算
		for (auto& mapChip : mapChips)
		{
			IEnemy* enemy = dynamic_cast<IEnemy*>(mapChip);
			if (enemy == nullptr)
			{
				continue;
			}
			if (!enemy->GetIsDamage()) {

				//CVector3 EnemyVec = enemys->GetPosition();
				//EnemyVec.y += OFFSET_Y;
				const CMatrix* enemySpineMatrix = enemy->GetWorldMatrixSpine();
				CVector3 EnemyVec;
				EnemyVec.x = enemySpineMatrix->m[3][0];
				EnemyVec.y = enemySpineMatrix->m[3][1];
				EnemyVec.z = enemySpineMatrix->m[3][2];
				EnemyVec.Subtract(m_position);
				float len = EnemyVec.Length();

				if (fabs(len) < HIT_LENGTH)
				{
					enemy->SetIsDamage(true);
					deleteFlg = true;
					m_effect.Init(L"Assets/Effect/DamageEffect.efk");
					m_effect.Play();
					CVector3 effectPos = m_position;
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
					EnemyVec -= m_position;
					float len = EnemyVec.Length();

					//弱点との判定
					if (fabs(len) < BossWeekLenge)
					{
						GetMaw().SetIsDamage(true);
						deleteFlg = true;
						m_effect.Init(L"Assets/Effect/DamageEffect.efk");
						m_effect.Play();
						CVector3 effectPos = m_position;
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
					EnemyVec -= m_position;
					float len = EnemyVec.Length();
					//ボスとの判定
					if (fabs(len) < BossLenge)
					{
						GetMaw().SetIsDamage(true);
						deleteFlg = true;
						m_effect.Init(L"Assets/Effect/DamageEffect.efk");
						m_effect.Play();
						CVector3 effectPos = m_position;
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

	m_skinmodel.Update(m_position, m_rotation, m_scale);
}

void CPlayerArrow::Draw()
{
	m_skinmodel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}