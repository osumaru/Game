#include "stdafx.h"
#include"../../Game/Camera/GameCamera.h"
#include "../Scene/SceneManager.h"
#include "../Map/Map.h"
#include "../Enemy/IEnemy.h"
#include "PlayerArrow.h"
#include "Player.h"


CPlayerArrow::CPlayerArrow()
{
}


CPlayerArrow::~CPlayerArrow()
{

}

bool CPlayerArrow::Start()
{
	m_arrowskin.Load(L"Assets/modelData/Arrow.cmo", NULL);
	m_scale = { 3.0f,3.0f,3.0f };
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
		rotX.SetRotation(CVector3::AxisX, CMath::DegToRad(rot));
		m_arrowRot.Multiply(rotX);



		m_lifeTime += GameTime().GetDeltaFrameTime();

		for (const auto& enemys :GetSceneManager().GetGameScene().GetMap()->GetEnemyList())
		{
			if (!enemys->IsDamage()) {

				CVector3 EnemyVec = enemys->GetPosition();
				EnemyVec.y += OFFSET_Y;
				EnemyVec.Subtract(m_arrowPosition);
				float len = EnemyVec.Length();

				if (fabs(len) < 0.5f)
				{
					enemys->SetIsDamage(true);
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