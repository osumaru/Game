#include "stdafx.h"
#include "Ninja.h"
#include "../Player/Player.h"
#include "../Camera/GameCamera.h"

CNinja::CNinja()
{
	this->SetIsActive(false);
}

CNinja::~CNinja()
{
}

void CNinja::OnInvokeAnimationEvent(const wchar_t* animClipName, const wchar_t* eventName)
{
	if (wcscmp(animClipName, L"Assets/modelData/NinjaAttack.tka") == 0)
	{
		m_isAttack = !m_isAttack;
	}
}

void CNinja::Init(const CVector3& position)
{
	//���f����ǂݍ���
	m_skinModel.Load(L"Assets/modelData/Ninja.cmo", &m_animation);
	m_skinModel.LoadNormalmap(L"Assets/modelData/Ninja_normal.png");
	m_position = position;
	//�L�����N�^�[�R���g���[���[��������
	m_characterController.Init(0.5f, 0.9f, m_position);
	m_characterController.SetGravity(-9.8f);
	//�A�j���[�V�����̏�����
	wchar_t* animClip[CEnemyState::enAnimation_Num] = {
		L"Assets/modelData/NinjaStand.tka",
		L"Assets/modelData/NinjaWalk.tka",
		L"Assets/modelData/NinjaDash.tka",
		L"Assets/modelData/NinjaAttack.tka",
		L"Assets/modelData/NinjaDamageSmall.tka",
		L"Assets/modelData/NinjaDown.tka",
		L"Assets/modelData/NinjaUp.tka",
		L"Assets/modelData/NinjaDeath.tka"
	};
	m_animation.Init(animClip, CEnemyState::enAnimation_Num);
	m_animation.SetLoopFlg(CEnemyState::enAnimation_Idle, true);
	m_animation.SetLoopFlg(CEnemyState::enAnimation_Walk, true);
	m_animation.SetLoopFlg(CEnemyState::enAnimation_Chase, true);
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
	m_attackLength = 1.2f;

	m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
	{
		OnInvokeAnimationEvent(animClipname, eventName);
	});
}

bool CNinja::Start()
{
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CNinja::Update()
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
		CMatrix boneMatrix = GetBoneWorldMatrix(L"RightFoot");
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
			GetPlayer().SetDamage(m_status.strength);
			GetPlayer().SetDamageEnemyPos(m_position);
		}
	}

	if (!m_isWireHit) 
	{
		//�A�j���[�V�����̍X�V
		m_animation.Update(GameTime().GetDeltaFrameTime() * 2.0f);
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

void CNinja::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CNinja::Attack()
{
	m_animation.Play(CEnemyState::enAnimation_Attack, 0.3f);
}
