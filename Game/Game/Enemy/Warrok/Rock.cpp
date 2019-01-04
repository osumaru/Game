#include "Rock.h"
#include "../../Camera/GameCamera.h"
#include "../../Player/Player.h"
#include "../../Scene/SceneManager.h"
#include "../IEnemy.h"

void CRock::Init(IEnemy* enemy, CVector3 enemyPos)
{
	//���f����������
	m_skinModel.Load(L"Assets/modelData/Rock.cmo");
	//�U�������G�̍��W��ۑ�
	m_enemyPos = enemyPos;
	//���W��������
	m_enemyHandMatrix = &enemy->GetBoneWorldMatrix(L"LeftHand");
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
	m_characterController.SetIgnoreRigidBody(&enemy->GetCharacterController().GetBody());
}

bool CRock::Start()
{
	//��𓊂�����������߂�
	CVector3 attackPos = m_targetPos;
	attackPos.y += 5.0f;
	CVector3 attackDir = attackPos - m_position;
	attackDir.Normalize();
	//������p�x��ݒ�
	float angle = CMath::PI / 6;
	//�^�[�Q�b�g�Ƃ̋��������߂�
	CVector3 distance = m_targetPos - m_position;
	float length = distance.Length();
	//�ړ����x��ݒ�
	CVector3 moveSpeed;
	moveSpeed.x = attackDir.x * length * cos(angle);
	moveSpeed.y = attackDir.y * length * sin(angle);
	moveSpeed.z = attackDir.z * length * cos(angle);
	m_characterController.SetMoveSpeed(moveSpeed);

	return true;
}

void CRock::Update()
{
	if (GetSceneManager().GetSceneChange())
	{
		Delete(this);
	}
	if (m_characterController.GetWallCollisionObject() != nullptr)
	{
		if(m_characterController.GetWallCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			//�v���C���[�ɓ�������
			GetPlayer().SetDamage(10);
			GetPlayer().SetDamageEnemyPos(m_enemyPos);
			GetPlayer().SetDamage(true);
		}
		//�ǂɓ�������
		Delete(this);
	}

	if (m_characterController.GetGroundCollisionObject() != nullptr)
	{
		if (m_characterController.GetGroundCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			//�v���C���[�ɓ�������
			GetPlayer().SetDamage(10);
			GetPlayer().SetDamageEnemyPos(m_enemyPos);
			GetPlayer().SetDamage(true);
		}
		//�n�ʂɓ�������
		Delete(this);
	}

	//���W���X�V
	if (m_isThrow) {
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GameTime().GetDeltaFrameTime());
		m_position = m_characterController.GetPosition();
	}
	else {
		m_position.x = m_enemyHandMatrix->m[3][0];
		m_position.y = m_enemyHandMatrix->m[3][1];
		m_position.z = m_enemyHandMatrix->m[3][2];
	}
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void CRock::Draw()
{
	m_characterController.Draw();
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
