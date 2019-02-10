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

void CSamurai::OnInvokeAnimationEvent(const wchar_t * animClipName, const wchar_t * eventName)
{
	if (wcscmp(animClipName, L"Assets/modelData/SamuraiAttack.tka") == 0)
	{
		m_isAttack = !m_isAttack;
	}
}

void CSamurai::Init(const CVector3& position, int level)
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

	//���C�g�̐ݒ�
	CVector4 ambientLight = { 0.2f,0.2f,0.2f,0.8f };
	m_light.SetAmbientLight(ambientLight);
	m_skinModel.SetLight(m_light);

	//�X�e�[�^�X��ݒ�
	m_status.level = level;
	m_status.strength = 10 + level * 2;
	m_status.defense = 8 + level * 2;
	m_status.hp = 70 + level * 5;
	m_status.maxHp = m_status.hp;
	m_status.gold = 60 + level * 20;
	m_status.exp = 4 + level * 3;

	this->SetIsActive(true);

	//�G�t�F�N�g��������
	m_auraEffect.Init(L"Assets/Effect/auraEffect.efk");
	m_auraEffect.SetPosition(position);
	m_auraEffect.SetScale({ 1.0f, 1.0f, 1.0f });
	//���̃��[���h�s����擾
	m_spineMatrix = &GetBoneWorldMatrix(L"Spine");
	//�U���ł��鋗����ݒ�
	m_attackLength = 1.2f;
	//�G�l�~�[�̎�ނ�ݒ�
	m_type = enEnemy_Samurai;

	m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
	{
		OnInvokeAnimationEvent(animClipname, eventName);
	});
}

bool CSamurai::Start()
{
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CSamurai::Update()
{
	if (m_isDead)
	{
		//���̂��폜����
		m_characterController.RemovedRigidBody();
	}

	//�v���C���[�Ƃ̃��x���������߂�
	int levelDifference = m_status.level - GetPlayer().GetStatus().Level;
	//�|���₷���G�̃��x������ݒ�
	const int LEVEL_DIFFERENCE_LIMIT = 5;
	//���x�������傫����
	if (levelDifference > LEVEL_DIFFERENCE_LIMIT)
	{
		m_effectInterval++;
		const int EFFECT_INTERVAL = 40;
		if (m_effectInterval % EFFECT_INTERVAL == 0)
		{
			m_effectInterval = 0;
			//�G�t�F�N�g���Đ�
			m_auraEffect.Play();
		}
		//�G�t�F�N�g�̍��W��ݒ�
		m_auraEffect.SetPosition(m_position);
		//�G�t�F�N�g�̍X�V
		m_auraEffect.Update();
	}

	if (m_isAttack)
	{
		//�U�����̓v���C���[�Ƃ̓����蔻����Ƃ�
		//�{�[���̃��[���h�s����擾
		CMatrix boneMatrix = GetBoneWorldMatrix(L"RightHand");
		CVector3 bonePosition;
		bonePosition.x = boneMatrix.m[3][0];
		bonePosition.y = boneMatrix.m[3][1];
		bonePosition.z = boneMatrix.m[3][2];
		//�G�̍U���Ƃ̋������v�Z
		CVector3 playerPosition = GetPlayer().GetPosition();
		playerPosition.y += 0.5f;
		CVector3 distance = bonePosition - playerPosition;
		float length = distance.Length();
		if (length < 1.2f)
		{
			//�v���C���[���_���[�W���󂯂�
			GetPlayer().SetDamage(m_status.strength);
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

void CSamurai::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CSamurai::Attack()
{
	m_animation.Play(CEnemyState::enAnimation_Attack, 0.3f);
}
