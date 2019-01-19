#include "Rock.h"
#include "../../Camera/GameCamera.h"
#include "../../Player/Player.h"
#include "../../Scene/SceneManager.h"
#include "Warrok.h"

void CRock::Init(CWarrok* warrok, const CVector3& enemyPos)
{
	//���f����������
	m_skinModel.Load(L"Assets/modelData/Rock.cmo");
	//�U�������G�̍��W��ۑ�
	m_enemyPos = enemyPos;
	//���W��������
	m_enemyHandMatrix = &warrok->GetBoneWorldMatrix(L"LeftHand");
	m_position.x = m_enemyHandMatrix->m[3][0];
	m_position.y = m_enemyHandMatrix->m[3][1];
	m_position.z = m_enemyHandMatrix->m[3][2];
	//�^�[�Q�b�g�̍��W(�v���C���[�̍�)��ݒ�
	CMatrix playerMatrix = GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Spine");
	m_targetPos.x = playerMatrix.m[3][0];
	m_targetPos.y = playerMatrix.m[3][1];
	m_targetPos.z = playerMatrix.m[3][2];
	//�L�����N�^�[�R���g���[���[��������
	m_characterController.Init(1.0f, 0.1f, m_position);
	m_characterController.SetGravity(-4.9f);
	m_characterController.SetIgnoreRigidBody(&warrok->GetCharacterController().GetBody());
	m_warrok = warrok;

	//�p�[�e�B�N���̏�����
	m_particleInfo.filePath = L"Assets/particle/rockEffect.png";
	m_particleInfo.width = 0.5f;
	m_particleInfo.height = 0.5f;
	m_particleInfo.uv = { 0.0f,0.0f,1.0f,1.0f };
	m_particleInfo.randomPosition = { 0.0f, 0.0f, 0.0f };
	m_particleInfo.gravity = { 0.0f, -9.8f, 0.0f };
	m_particleInfo.lifeTime = 3.0f;
	m_particleInfo.emittIntervalTime = 2.0f;
	m_particleInfo.emitterLifeTime = 1.0f;
	m_particleInfo.emitterPosition = m_position;
	m_particleInfo.moveSpeed = { 0.0f, 5.0f, 0.0f };
	m_particleInfo.randomMoveSpeed = { 3.0f, 3.0f, 3.0f };
	m_particleInfo.particleNum = 10;
	m_particleInfo.isFirstTimeRandom = false;
}

void CRock::Update()
{
	if (GetSceneManager().GetSceneChange() 
		|| (!m_isThrow && (m_warrok->GetStateMachine().GetCurrentState() != CEnemyState::enState_Attack && m_warrok->GetStateMachine().GetCurrentState() != CEnemyState::enState_AttackWait)))
	{
		Delete(this);
	}

	//�ǂɓ�������
	if (m_characterController.GetWallCollisionObject() != nullptr)
	{
		//�v���C���[�ɓ�������
		if(m_characterController.GetWallCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			GetPlayer().SetDamage(m_warrok->GetStatus().strength);
			GetPlayer().SetDamageEnemyPos(m_enemyPos);
			GetPlayer().SetDamage(true);
		}
		m_isHit = true;
		Delete(this);
	}

	//�n�ʂɓ�������
	if (m_characterController.GetGroundCollisionObject() != nullptr)
	{
		//�v���C���[�ɓ�������
		if (m_characterController.GetGroundCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			GetPlayer().SetDamage(m_warrok->GetStatus().strength);
			GetPlayer().SetDamageEnemyPos(m_enemyPos);
			GetPlayer().SetDamage(true);
		}
		m_isHit = true;
		Delete(this);
	}

	if (m_isHit)
	{
		//�����ɓ������Ă�����p�[�e�B�N�����o��
		CParticleEmitter* particleEmitter = New<CParticleEmitter>(PRIORITY_UI);
		particleEmitter->Init(m_particleInfo, &GetGameCamera().GetCamera());
		particleEmitter->SetPosition(m_position);
		m_isHit = false;
	}

	//���W���X�V
	if (m_isThrow) 
	{
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GameTime().GetDeltaFrameTime());
		m_position = m_characterController.GetPosition();
	}
	else 
	{
		m_position.x = m_enemyHandMatrix->m[3][0];
		m_position.y = m_enemyHandMatrix->m[3][1];
		m_position.z = m_enemyHandMatrix->m[3][2];
	}
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void CRock::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CRock::SetMoveSpeed()
{
	//�₩��v���C���[�ւ̃x�N�g�������߂�
	CVector3 distance = GetPlayer().GetPosition() - m_position;
	//XZ���ʂł̋��������߂�
	CVector3 distanceXZ = distance;
	distanceXZ.y = 0.0f;
	float lengthXZ = distanceXZ.Length();
	//������p�x��ݒ�
	float angle = CMath::PI / 6;
	//�����鍂�������߂�
	float height = tan(angle) * lengthXZ;
	//��������������߂�
	CVector3 moveDir = distance;
	moveDir.y += height;
	float length = moveDir.Length();
	moveDir.Normalize();
	//�ړ����x��ݒ�
	CVector3 moveSpeed;
	moveSpeed.x = moveDir.x * length * cos(angle);
	moveSpeed.y = moveDir.y * length * sin(angle);
	moveSpeed.z = moveDir.z * length * cos(angle);
	m_characterController.SetMoveSpeed(moveSpeed);
}
