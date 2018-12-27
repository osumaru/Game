#include "Rock.h"
#include "../../Camera/GameCamera.h"
#include "../../Player/Player.h"

void CRock::Init(CVector3 position)
{
	//���f����������
	m_skinModel.Load(L"Assets/modelData/Rock.cmo");
	//�U�������G�̍��W��ۑ�
	m_enemyPos = position;
	//���W��������
	m_position = position;
	m_position.y += 2.0f;
	//�^�[�Q�b�g�̍��W(�v���C���[�̍�)��ݒ�
	CMatrix playerMatrix = GetPlayer().GetSkinmodel().FindBoneWorldMatrix(L"Spine");
	m_targetPos.x = playerMatrix.m[3][0];
	m_targetPos.y = playerMatrix.m[3][1];
	m_targetPos.z = playerMatrix.m[3][2];
	//�L�����N�^�[�R���g���[���[��������
	m_characterController.Init(1.0f, 0.1f, m_position);
	m_characterController.SetGravity(-4.9f);
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
	if (m_characterController.GetWallCollisionObject() != nullptr)
	{
		//�ǂɓ�������
		if(m_characterController.GetWallCollisionObject()->getUserIndex() == enCollisionAttr_Player)
		{
			//�v���C���[�ɓ�������
			GetPlayer().SetDamage(10);
			GetPlayer().SetDamageEnemyPos(m_enemyPos);
			GetPlayer().SetDamage(true);
		}
		if (m_characterController.GetWallCollisionObject()->getUserIndex() != enCollisionAttr_Character)
		{
			Delete(this);
		}
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
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();
	CVector3 modelPos = m_position;
	float offset = 0.2f;
	modelPos.y += offset;
	m_skinModel.Update(modelPos, m_rotation, { 1.0f, 1.0f, 1.0f });
}

void CRock::Draw()
{
	m_characterController.Draw();
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}
