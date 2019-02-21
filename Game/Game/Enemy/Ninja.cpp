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
		if (!m_isAttack)
		{
			//�U����
			const float AttackVolume = 0.3f;
			CSoundSource* AttackSound = New<CSoundSource>(0);
			AttackSound->Init("Assets/sound/Battle/WarrokEnemyAttackSE.wav");
			AttackSound->Play(false);
			AttackSound->SetVolume(AttackVolume);
		}
		m_isAttack = !m_isAttack;
	}
}

void CNinja::Init(int level)
{
	//���f����ǂݍ���info
	m_skinModel.LoadNormalmap(L"Assets/modelData/Ninja_normal.png");
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
	m_animation.Play(CEnemyState::enAnimation_Idle, 0.3f);

	//���C�g�̐ݒ�
	CVector4 ambientLight = { 0.2f,0.2f,0.2f,0.6f };
	m_light.SetAmbientLight(ambientLight);
	m_skinModel.SetLight(m_light);

	//�X�e�[�^�X��ݒ�
	m_status.level = level;
	m_status.strength = 15 + level * 2;
	m_status.defense = 10 + level * 2;
	m_status.hp = 85 + level * 5;
	m_status.maxHp = m_status.hp;
	m_status.gold = 80 + level * 20;
	m_status.exp = 7 + level * 3;

	this->SetIsActive(true);

	//�G�t�F�N�g��������
	m_auraEffect.Init(L"Assets/Effect/auraEffect.efk");
	m_auraEffect.SetPosition(m_position);
	m_auraEffect.SetScale({ 1.0f, 1.0f, 1.0f });
	//���̃��[���h�s����擾
	m_spineMatrix = &GetBoneWorldMatrix(L"Spine");
	//�U���ł��鋗����ݒ�
	m_attackLength = 1.2f;
	//�G�l�~�[�̎�ނ�ݒ�
	m_type = enEnemy_Ninja;

	m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
	{
		OnInvokeAnimationEvent(animClipname, eventName);
	});
}

bool CNinja::Start()
{
	IEnemy::Start();
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CNinja::Update()
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

void CNinja::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CNinja::Attack()
{
	m_animation.Play(CEnemyState::enAnimation_Attack, 0.3f);
}
