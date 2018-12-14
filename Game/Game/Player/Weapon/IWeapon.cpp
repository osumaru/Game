#include "IWeapon.h"
#include "../../Camera/GameCamera.h"
#include "../Player.h"
#include "../../Enemy/IEnemy.h"
#include "../../Scene/SceneManager.h"
#include "../../Scene/GameScene.h"
#include "../../Map/Map.h"
#include "../../Enemy/Maw.h"
#include "../../Enemy/EnemyGroup.h"

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
	WeaponTraceDrawer();
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

void IWeapon::WeaponTraceDrawer()
{
	CWeaponTraceDraw& weaponTrace = m_pPlayer->GetWeaponManager().GetWeaponTraceDraw();
	if (m_pPlayer->GetWeaponManager().GetIsAttack())
	{
		SWeaponTraceDrawInfo info = WeaponTraceDraw();
		m_pPlayer->GetWeaponManager().SetIsTraceDraw(info.isDraw);
		if (info.isDraw)
		{
			weaponTrace.Add(info.rootPos, info.pointPos);
		}
	}
	else
	{
	}
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
	SWeaponEnemyAttackInfo info = EnemyAttackPositionDecide();
	if (!info.isAttack)
	{
		return;
	}

	//エネミーグループのリストを取得
	std::list<CEnemyGroup*> enemyGroup = GetSceneManager().GetGameScene().GetMap()->GetEnemyGroupList();
	for (const auto& group : enemyGroup)
	{
		CVector3 enemyGroupPos = group->GetPosition();
		CVector3 distance = enemyGroupPos - info.attackPos;
		float length = distance.Length();
		if (length < 50.0f)
		{
			for (const auto& enemy : group->GetGroupList()) 
			{
				if (enemy->IsDamagePossible())
				{
					CVector3 EnemyVec = enemy->GetSpinePos();
					EnemyVec.Subtract(info.attackPos);
					float len = EnemyVec.Length();

					if (fabs(len) < 2.0f)
					{
						enemy->SetIsDamage(true);
						enemy->SetIsDamagePossible(false);
					}
				}
			}
		}
	}

	//ボスが作られていたら
	if (&GetMaw() != NULL)
	{
		//ボスがダメージを受けていなかったら
		if (!GetMaw().GetIsDamage())
		{
			//ダウンしていなかったら
			if (!GetMaw().GetIsDown())
			{
				const float BossWeekLenge = 18.0f;
				//ボスの弱点の座標取得
				CVector3 EnemyVec = GetMaw().GetWeekPosition();
				EnemyVec -= info.attackPos;
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
				EnemyVec -= info.attackPos;
				float len = EnemyVec.Length();

				if (fabs(len) < BossLenge)
				{
					GetMaw().SetIsDamage(true);
					return;
				}
			}
		}
	}
}