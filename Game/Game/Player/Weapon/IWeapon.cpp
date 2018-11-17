#include "IWeapon.h"
#include "../../Camera/GameCamera.h"
#include "../Player.h"
#include "../../Enemy/IEnemy.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/GameScene.h"
#include "../../Map/Map.h"
#include "../../Enemy/Maw.h"


void IWeapon::Init(CPlayer* player)
{
	m_pPlayer = player;
	m_normalBoneMat = &m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"LeftShoulder");
	m_attackBoneMat = &m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"RightHand");
	Init();
}

void IWeapon::Updater()
{
	Update();

	CVector3 position;
	CQuaternion rotation;
	const CMatrix* boneMat;
	if (m_pPlayer->GetWeaponManager().GetIsAttack())
	{
		boneMat = m_attackBoneMat;
		position = m_attackPosition;
		rotation = m_attackRotation;
	}
	else
	{
		boneMat = m_normalBoneMat;
		position = m_position;
		rotation = m_rotation;
	}
	position.Mul(*boneMat);
	m_attackCheckPos = position;
	CMatrix rotMat = *boneMat;
	((CVector3*)rotMat.m[0])->Div(((CVector3*)rotMat.m[0])->Length());
	((CVector3*)rotMat.m[1])->Div(((CVector3*)rotMat.m[1])->Length());
	((CVector3*)rotMat.m[2])->Div(((CVector3*)rotMat.m[2])->Length());
	rotMat.m[3][0] = 0.0f;
	rotMat.m[3][1] = 0.0f;
	rotMat.m[3][2] = 0.0f;
	CQuaternion multi;
	multi.SetRotation(rotMat);
	multi.Multiply(rotation);
	rotation = multi;
	m_skinModel.Update(position, rotation, CVector3::One);
}

void IWeapon::Drawer()
{
	Draw();
	const CCamera& camera = GetGameCamera().GetCamera();
	m_skinModel.Draw(camera.GetViewMatrix(), camera.GetProjectionMatrix());
}

void IWeapon::AfterDrawer()
{
	AfterDraw();
}


void IWeapon::EnemyAttack()
{
	if (!m_pPlayer->GetWeaponManager().GetIsAttackCheck())
	{
		return;
	}
	EnemyAttackPositionDecide();
	//エネミーのリストを取得
	for (const auto& enemys : GetSceneManager().GetGameScene().GetMap()->GetEnemyList())
	{
		if (enemys->IsDamagePossible())
		{

			CVector3 EnemyVec = enemys->GetPosition();
			EnemyVec.y += 1.3f;
			EnemyVec.Subtract(m_attackCheckPos);
			float len = EnemyVec.Length();

			if (fabs(len) < 2.0f)
			{
				enemys->SetIsDamage(true);
				enemys->SetIsDamagePossible(false);
			}

		}
	}

	//ボスが作られていなかったら
	if (&GetMaw() == NULL)
	{
		return;
	}
	//if (!GetMaw().GetIsBattle()) { return; }
	//ボスがダメージを受けていなかったら
	if (!GetMaw().GetIsDamage())
	{
		//ダウンしていなかったら
		if (!GetMaw().GetIsDown())
		{
			const float BossWeekLenge = 50.0f;
			//ボスの弱点の座標取得
			CVector3 EnemyVec = GetMaw().GetWeekPosition();
			EnemyVec -= m_attackCheckPos;
			float len = EnemyVec.Length();

			if (fabs(len) < BossWeekLenge)
			{
				GetMaw().SetIsDamage(true);
				return;
			}
		}
		else
		{
			const float BossHeight = 10.0f;
			const float BossLenge = 12.0f;
			//ボスの座標取得
			CVector3 EnemyVec = GetMaw().GetPosition();
			EnemyVec.y += BossHeight;
			EnemyVec -= m_attackCheckPos;
			float len = EnemyVec.Length();

			if (fabs(len) < BossLenge)
			{
				GetMaw().SetIsDamage(true);
				return;
			}
		}
	}
}