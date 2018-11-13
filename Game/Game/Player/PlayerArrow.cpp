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
//��̏�����
bool CPlayerArrow::Start()
{
	m_arrowskin.Load(L"Assets/modelData/Arrow.cmo", NULL);
	m_scale = ARROW_SCALE;
	return true;
}

void CPlayerArrow::Update()
{
	if (GetPlayer().GetPlayerStateMachine().GetState() == CPlayerState::EnPlayerState::enPlayerStateArrowAttack && !m_isMove)
	{
		m_arrowPosition =  GetPlayer().GetWeapon().GetPosition();
		//�J�����̑O�������擾
		CVector3 weaponFlont = GetGameCamera().GetCamera().GetFlont();
		weaponFlont.Normalize();
		m_moveSpeed = weaponFlont * MOVE_POWRE;
		CQuaternion rotY;
		m_arrowRot.SetRotation(CVector3::AxisY, atan2f(weaponFlont.x, weaponFlont.z));		//Y������̉�]
		rotY.SetRotation(CVector3::AxisX, atanf(-weaponFlont.y));		//X������̉�]
		m_arrowRot.Multiply(rotY);
	}
	//����΂�����
	else
	{
		m_isMove = true;
		CVector3 flont, newVec,oldpos;
		//�|�̑O����
		flont = { m_arrowskin.GetWorldMatrix().m[2][0],m_arrowskin.GetWorldMatrix().m[2][1],m_arrowskin.GetWorldMatrix().m[2][2] };
		//�P�t���[���O�̍��W
		oldpos = m_arrowPosition;
		//�ڕW�ʒu�̌v�Z
		m_moveSpeed.y += GRAVITY * GameTime().GetDeltaFrameTime();
		m_arrowPosition += m_moveSpeed * GameTime().GetDeltaFrameTime();
		//���̍��W����ڕW�n�_�Ɍ������x�N�g��
		newVec = m_arrowPosition - oldpos;
		//���K��
		newVec.Normalize();
		flont.Normalize();
		float rot = flont.Dot(newVec);
		rot = acos(rot) ;
		CQuaternion rotX = CQuaternion::Identity;
		rotX.SetRotation(CVector3::AxisX, CMath::DegToRad( rot));
		m_arrowRot.Multiply(rotX);
		m_lifeTime += GameTime().GetDeltaFrameTime();

		//�G�Ƃ̓����蔻��̌v�Z
		for (const auto& enemys :GetSceneManager().GetGameScene().GetMap()->GetEnemyList())
		{
			if (!enemys->IsDamage()) {

				CVector3 EnemyVec = enemys->GetPosition();
				EnemyVec.y += OFFSET_Y;
				EnemyVec.Subtract(m_arrowPosition);
				float len = EnemyVec.Length();

				if (fabs(len) < HIT_LENGTH)
				{
					enemys->SetIsDamage(true);
				}

			}
		}

		//�{�X������Ă�����
		if (&GetMaw() != NULL)
		{
		
		//�{�X���_���[�W���󂯂Ă��Ȃ�������
			if (!GetMaw().GetIsDamage()) {
				//�_�E�����Ă��Ȃ�������
				if (!GetMaw().GetIsDown())
				{
					const float BossWeekLenge = 50.0f;
					//�{�X�̎�_�̍��W�擾
					CVector3 EnemyVec = GetMaw().GetWeekPosition();
					EnemyVec -= m_arrowPosition;
					float len = EnemyVec.Length();

					//��_�Ƃ̔���
					if (fabs(len) < BossWeekLenge)
					{
						GetMaw().SetIsDamage(true);
						//return;
					}
				}
				else
				{
					const float BossHeight = 10.0f;
					const float BossLenge = 12.0f;
					//�{�X�̍��W�擾
					CVector3 EnemyVec = GetMaw().GetPosition();
					EnemyVec.y += BossHeight;
					EnemyVec -= m_arrowPosition;
					float len = EnemyVec.Length();
					//�{�X�Ƃ̔���
					if (fabs(len) < BossLenge)
					{
						GetMaw().SetIsDamage(true);
						//return;
					}
				}
			}
		}
		
	}
	
	if (m_lifeTime >= ARROW_LIFE)
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