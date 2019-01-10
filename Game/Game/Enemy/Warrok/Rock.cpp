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
	m_enemy = enemy;
}

void CRock::Update()
{
	if (GetSceneManager().GetSceneChange() 
		|| (!m_isThrow && m_enemy->GetIsDamage()))
	{
		Delete(this);
	}
	if (m_characterController.GetWallCollisionObject() != nullptr)
	{
		if(m_characterController.GetWallCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			//�v���C���[�ɓ�������
			GetPlayer().SetDamage(m_enemy->GetStatus().strength);
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
			GetPlayer().SetDamage(m_enemy->GetStatus().strength);
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
