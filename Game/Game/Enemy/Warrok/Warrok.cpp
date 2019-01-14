#include "stdafx.h"
#include "Warrok.h"
#include "../../Player/Player.h"
#include "../../Camera/GameCamera.h"
#include "Rock.h"

CWarrok::CWarrok()
{
	this->SetIsActive(false);
}

CWarrok::~CWarrok()
{
}

void CWarrok::OnInvokeAnimationEvent(//�A�j���[�V�����C�x���g���Ă΂�邲�ƂɌĂяo�����H
	const wchar_t* animClipName,
	const wchar_t* eventName)
{
	if (wcscmp(animClipName, L"Assets/modelData/WarrokAttack.tka") == 0) 
	{
		m_isAttack = !m_isAttack;
	}

	if (wcscmp(animClipName, L"Assets/modelData/WarrokRock.tka") == 0)
	{
		//�₩��v���C���[�ւ̃x�N�g�������߂�
		CVector3 distance = GetPlayer().GetPosition() - m_rock->GetPosition();
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
		m_rock->SetMoveSpeed(moveSpeed);
		//������t���O�𗧂Ă�
		m_rock->SetIsThrow(true);
	}
}

void CWarrok::Init(const CVector3& position)
{
	//���f����ǂݍ���
	m_skinModel.Load(L"Assets/modelData/Warrok.cmo", &m_animation);
	m_skinModel.LoadNormalmap(L"Assets/modelData/Warrok_normal.png");
	m_position = position;
	//�L�����N�^�[�R���g���[���[��������
	m_characterController.Init(0.5f, 0.9f, m_position);
	m_characterController.SetGravity(-9.8f);
	//�A�j���[�V�����̏�����
	wchar_t* animClip[CEnemyState::enAnimationWarrok_Num] = {
		L"Assets/modelData/WarrokStand.tka",
		L"Assets/modelData/WarrokWalk.tka",
		L"Assets/modelData/WarrokDash.tka",
		L"Assets/modelData/WarrokAttack.tka",
		L"Assets/modelData/WarrokDamageSmall.tka",
		L"Assets/modelData/WarrokDown.tka",
		L"Assets/modelData/WarrokUp.tka",
		L"Assets/modelData/WarrokDeath.tka",
		L"Assets/modelData/WarrokRock.tka"
	};
	m_animation.Init(animClip, CEnemyState::enAnimationWarrok_Num);
	m_animation.SetLoopFlg(CEnemyState::enAnimationWarrok_Idle, true);
	m_animation.SetLoopFlg(CEnemyState::enAnimationWarrok_Walk, true);
	m_animation.SetLoopFlg(CEnemyState::enAnimationWarrok_Chase, true);
	//Add(&m_enemyStateMachine, 0);
	//Add(&m_enemyTurn, 0);
	//Add(&m_enemySearch, 0);

	//�X�e�[�^�X��ݒ�
	m_status.strength = 10;
	m_status.defense = 0;
	m_status.hp = 50;
	m_status.maxHp = m_status.hp;
	m_status.gold = 100;
	m_status.exp = 10;
	this->SetIsActive(true);
	//���̃��[���h�s����擾
	m_spineMatrix = &GetBoneWorldMatrix(L"Spine");
	//�U���ł��鋗����ݒ�
	m_attackLength = 10.0f;
	//�U���^�C�v��ݒ�
	m_attackType = enAttackType_Far;

	m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
	{
		OnInvokeAnimationEvent(animClipname, eventName);
	});
}

bool CWarrok::Start()
{
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CWarrok::Update()
{
	if (m_status.hp <= 0)
	{
		m_isDead = true;
		//���̂��폜����
		m_characterController.RemovedRigidBody();
	}

	if (m_isAttack) 
	{
		//�U�����̓v���C���[�Ƃ̓����蔻����Ƃ�
		//�{�[���̃��[���h�s����擾
		CMatrix boneMatrix = GetBoneWorldMatrix(L"LeftHand");
		CVector3 bonePosition;
		bonePosition.x = boneMatrix.m[3][0];
		bonePosition.y = boneMatrix.m[3][1];
		bonePosition.z = boneMatrix.m[3][2];
		//�G�̍U���Ƃ̋������v�Z
		CVector3 playerPosition = GetPlayer().GetPosition();
		playerPosition.y += 0.5f;
		CVector3 distance = bonePosition - playerPosition;
		float length = distance.Length();
		if (length < 1.0f)
		{
			//�v���C���[���_���[�W���󂯂�
			GetPlayer().SetStanDamage(m_status.strength);
			GetPlayer().SetDamageEnemyPos(m_position);
		}
	}

	if (!m_isWireHit) 
	{
		//�A�j���[�V�����̍X�V
		m_animation.Update(GameTime().GetDeltaFrameTime());
	}

	if (!m_isDead && !m_isWireHit)
	{
		//���W�̍X�V
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GameTime().GetDeltaFrameTime());
		m_position = m_characterController.GetPosition();
	}

	//���f���̍X�V
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
}

void CWarrok::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CWarrok::Attack()
{
	//XZ���ʂł̃v���C���[�Ƃ̋��������߂�
	CVector3 toPlayer = GetPlayer().GetPosition() - m_position;
	toPlayer.y = 0.0f;
	float length = toPlayer.Length();
	if (length > 4.0f)
	{
		//��𓊂���
		m_animation.Play(CEnemyState::enAnimationWarrok_throw, 0.3f);
		m_rock = New<CRock>(PRIORITY_ENEMY);
		m_rock->Init(this, m_position);
	}
	else 
	{
		//�ʏ�U��
		m_animation.Play(CEnemyState::enAnimationWarrok_Attack, 0.3f);
	}
}
