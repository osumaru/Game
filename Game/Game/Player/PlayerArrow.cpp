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
//��̏�����
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
		//�v���C���[�̃{�[���̑O�������擾
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
		//��̑O�������擾
		const CMatrix& skinWorldMatrix = m_skinmodel.GetWorldMatrix();
		m_moveSpeed.x = skinWorldMatrix.m[2][0];
		m_moveSpeed.y = skinWorldMatrix.m[2][1];
		m_moveSpeed.z = skinWorldMatrix.m[2][2];
		m_moveSpeed.Normalize();
		m_moveSpeed *= MOVE_POWRE;
		CQuaternion rotY;
		m_rotation.SetRotation(CVector3::AxisY, atan2f(playerFront.x, playerFront.z));		//Y������̉�]
		rotY.SetRotation(CVector3::AxisX, atanf(-weaponFlont.y));		//X������̉�]
		//��]�̕␳�A�{�[���̉�]�����̂܂܎g���ƕςȕ�������������
		CQuaternion multi;
		multi.SetRotation(CVector3::AxisX, CMath::DegToRad(-10.0f));
		m_rotation.Multiply(rotY);
		m_rotation.Multiply(multi);
	}
	//����΂�����
	else
	{
		m_isMove = true;
		CVector3 flont, newVec,oldpos;
		//�|�̑O����
		flont = { m_skinmodel.GetWorldMatrix().m[2][0],m_skinmodel.GetWorldMatrix().m[2][1],m_skinmodel.GetWorldMatrix().m[2][2] };
		//�P�t���[���O�̍��W
		oldpos = m_position;
		//�ڕW�ʒu�̌v�Z
		m_moveSpeed.y += GRAVITY * GameTime().GetDeltaFrameTime();
		m_position += m_moveSpeed * GameTime().GetDeltaFrameTime();
		//���̍��W����ڕW�n�_�Ɍ������x�N�g��
		newVec = m_position - oldpos;
		//���K��
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
		//�G�Ƃ̓����蔻��̌v�Z
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

		//�{�X������Ă�����
		if (&GetMaw() != NULL)
		{
		
			//�{�X���_���[�W���󂯂Ă��Ȃ�������
			if (!GetMaw().GetIsDamage()) {
				//�_�E�����Ă��Ȃ�������
				if (!GetMaw().GetIsDown())
				{
					const float BossWeekLenge = 3.0f;
					//�{�X�̎�_�̍��W�擾
					CVector3 EnemyVec = GetMaw().GetWeekPosition();
					EnemyVec -= m_position;
					float len = EnemyVec.Length();

					//��_�Ƃ̔���
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
					//�{�X�̍��W�擾
					CVector3 EnemyVec = GetMaw().GetPosition();
					EnemyVec.y += BossHeight;
					EnemyVec -= m_position;
					float len = EnemyVec.Length();
					//�{�X�Ƃ̔���
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