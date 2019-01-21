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
	m_normalBoneMat = &m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"Spine");
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
	CWeaponTraceDraw *weaponTrace = &m_pPlayer->GetWeaponManager().GetWeaponTraceDraw();
	if (m_pPlayer->GetWeaponManager().GetIsAttack())
	{
		SWeaponTraceDrawInfo info = WeaponTraceDraw();
		m_pPlayer->GetWeaponManager().SetIsTraceDraw(info.isDraw);
		if (info.isDraw)
		{
			for (int i = 0; i < m_maxWeaponHitNum; i++)
			{
				weaponTrace[i].Add(info.rootPos[i], info.pointPos[i]);
			}
		}
	}
	else
	{
	}
}

void IWeapon::WeaponTraceDrawStart()
{
	CWeaponTraceDraw *weaponTrace=&m_pPlayer->GetWeaponManager().GetWeaponTraceDraw();
	SWeaponTraceDrawInfo info = WeaponTraceDraw();
	for (int i = 0; i < m_maxWeaponHitNum; i++)
	{
		weaponTrace[i].Start(info.rootPos[i], info.pointPos[i]);
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

	//�G�l�~�[�O���[�v�̃��X�g���擾
	std::list<CEnemyGroup*> enemyGroup = GetSceneManager().GetMap()->GetEnemyGroupList();
	for (const auto& group : enemyGroup)
	{
		for (int i = 0; i < m_maxWeaponHitNum; i++)
		{
			CVector3 enemyGroupPos = group->GetPosition();
			CVector3 distance = enemyGroupPos - info.attackPos[i];
			float length = distance.Length();
			if (length < 50.0f)
			{
				for (const auto& enemy : group->GetGroupList())
				{
					if (enemy->GetIsDead())
					{
						continue;
					}
					bool* damagePossible = enemy->IsDamagePossible();
					if(damagePossible[i])
					{
						const CMatrix* enemySpineMatrix = enemy->GetWorldMatrixSpine();
						CVector3 EnemyVec;
						EnemyVec.x = enemySpineMatrix->m[3][0];
						EnemyVec.y = enemySpineMatrix->m[3][1];
						EnemyVec.z = enemySpineMatrix->m[3][2];
						EnemyVec.Subtract(info.attackPos[i]);
						float len = EnemyVec.Length();
						if (fabs(len) < 2.0f)
						{
							int attackNum = m_pPlayer->GetWeaponManager().GetAttackCount();
							GameTime().SetSlowDelayTime(m_hitEffectParam[attackNum].slowTime, m_hitEffectParam[attackNum].slowScale, m_hitEffectParam[attackNum].slowDelayTime);
							GetGameCamera().GetShakeCamera().ShakeStart(m_hitEffectParam[attackNum].shakePower);
							GetGameCamera().GetShakeCamera().SetDelayTime(m_hitEffectParam[attackNum].shakeDelayTime);
							enemy->SetIsDamage(true);
							damagePossible[i] = false;
						}
					}
				}
			}
		}
	}

	//�{�X������Ă�����
	if (&GetMaw() != NULL)
	{
		//�{�X���_���[�W���󂯂Ă��Ȃ�������
		if (!GetMaw().GetIsDamage())
		{
			for (int i = 0; i < m_maxWeaponHitNum; i++)
			{
				//�_�E�����Ă��Ȃ�������
				if (!GetMaw().GetIsDown())
				{
					const float BossWeekLenge = 0.3f;
					//�{�X�̎�_�̍��W�擾
					CVector3 EnemyVec = GetMaw().GetWeekPosition();
					EnemyVec -= info.attackPos[i];
					float len = EnemyVec.Length();

					if (fabs(len) < BossWeekLenge)
					{
						GetMaw().SetIsDamage(true);
					}
				}
				else
				{
					const float BossHeight = 3.0f;
					const float BossLenge = 3.0f;
					//�{�X�̍��W�擾
					CVector3 EnemyVec = GetMaw().GetPosition();
					EnemyVec.y += BossHeight;
					EnemyVec -= info.attackPos[i];
					float len = EnemyVec.Length();

					if (fabs(len) < BossLenge)
					{
						GetMaw().SetIsDamage(true);
					}
				}
			}
		}
	}

}