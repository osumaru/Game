#include "stdafx.h"
#include "Samurai.h"
#include "../Player/Player.h"
#include "../Camera/GameCamera.h"

CSamurai::CSamurai()
{
	this->SetIsActive(false);
}

CSamurai::~CSamurai()
{
}

void CSamurai::Init(CVector3 position)
{
	//���f����ǂݍ���
	m_skinModel.Load(L"Assets/modelData/Samurai.cmo", &m_animation);
	m_skinModel.LoadNormalmap(L"Assets/modelData/Samurai_normal.png");
	m_position = position;
	//�L�����N�^�[�R���g���[���[��������
	m_characterController.Init(0.5f, 0.9f, m_position);
	m_characterController.SetGravity(-9.8f);
	//�A�j���[�V�����̍X�V
	wchar_t* animClip[CEnemyState::enAnimation_Num] = {
		L"Assets/modelData/SamuraiStand.tka",
		L"Assets/modelData/SamuraiWalk.tka",
		L"Assets/modelData/SamuraiDash.tka",
		L"Assets/modelData/SamuraiAttack.tka",
		L"Assets/modelData/SamuraiDamage.tka",
		L"Assets/modelData/SamuraiDown.tka",
		L"Assets/modelData/SamuraiUp.tka",
		L"Assets/modelData/SamuraiDeath.tka"
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
}

bool CSamurai::Start()
{
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CSamurai::Update()
{
	//�����蔻��p�̍��̍��W���X�V
	UpdateSpinePos();

	if (!m_isWireHit) {
		//�A�j���[�V�����̍X�V
		m_animation.Update(GameTime().GetDeltaFrameTime());
	}

	if (!m_isRemovedRigidBody && !m_isWireHit) {
		//���W�̍X�V
		m_characterController.SetPosition(m_position);
		m_characterController.Execute(GameTime().GetDeltaFrameTime());
		m_position = m_characterController.GetPosition();
	}

	//���f���̍X�V
	m_skinModel.Update(m_position, m_rotation, { 1.0f, 1.0f, 1.0f }, true);
}

void CSamurai::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CSamurai::Attack()
{
	m_animation.Play(CEnemyState::enAnimation_Attack, 0.3f);
}
