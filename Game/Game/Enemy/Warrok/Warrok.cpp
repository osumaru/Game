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
		if (!m_isAttack)
		{
			//�U����
			const float AttackVolume = 0.3f;
			CSoundSource* AttackSound = New<CSoundSource>(0);
			AttackSound->Init("Assets/sound/Battle/WarrokEnemyAttackSE.wav");
			AttackSound->Play(false);
			AttackSound->SetVolume(AttackVolume);
		}
		//�U���t���O��؂�ւ���
		m_isAttack = !m_isAttack;
	}

	if (wcscmp(animClipName, L"Assets/modelData/WarrokRock.tka") == 0)
	{
		//�ړ����x��ݒ�
		m_rock->SetMoveSpeed();
		//������t���O�𗧂Ă�
		m_rock->SetIsThrow(true);
		//��𓊂���Ƃ��̉���炷
		CSoundSource* rockThrowSound = New<CSoundSource>(0);
		rockThrowSound->Init("Assets/sound/SystemSound/StoneThrow.wav", true);
		rockThrowSound->Play(false);
		rockThrowSound->SetPosition(m_position);
	}
}

void CWarrok::Init(int level)
{
	//���f����ǂݍ���
	m_skinModel.LoadNormalmap(L"Assets/modelData/Warrok_normal.png");
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
	m_animation.Play(CEnemyState::enAnimation_Idle, 0.3f);

	//���C�g�̐ݒ�
	CVector4 ambientLight = { 0.2f,0.2f,0.2f,0.4f };
	m_light.SetAmbientLight(ambientLight);
	m_skinModel.SetLight(m_light);

	//�X�e�[�^�X��ݒ�
	m_status.level = level;
	m_status.strength = 30 + level * 2;
	m_status.defense = 15 + level * 2;
	m_status.hp = 100 + level * 5;
	m_status.maxHp = m_status.hp;
	m_status.gold = 100 + level * 20;
	m_status.exp = 10 + level * 3;

	this->SetIsActive(true);

	//�G�t�F�N�g��������
	m_auraEffect.Init(L"Assets/Effect/auraEffect.efk");
	m_auraEffect.SetPosition(m_position);
	m_auraEffect.SetScale({ 1.0f, 1.0f, 1.0f });
	//���̃��[���h�s����擾
	m_spineMatrix = &GetBoneWorldMatrix(L"Spine");
	//�U���ł��鋗����ݒ�
	m_attackLength = 10.0f;
	//�U���^�C�v��ݒ�
	m_attackType = enAttackType_Far;
	//�G�l�~�[�̎�ނ�ݒ�
	m_type = enEnemy_Warrok;

	m_animation.AddAnimationEvent([&](auto animClipname, auto eventName)
	{
		OnInvokeAnimationEvent(animClipname, eventName);
	});
}

bool CWarrok::Start()
{
	IEnemy::Start();
	m_enemyStateMachine.SetEnemyGroup(m_enemyGroup);

	return true;
}

void CWarrok::Update()
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

void CWarrok::RockAttackRotation()
{
	//�U��������������߂�
	CVector3 attackDir = GetPlayer().GetPosition() - m_position;
	attackDir.y = 0.0f;
	attackDir.Normalize();
	//�G�l�~�[�̑O�������擾
	CMatrix worldMatrix = GetWorldMatrix();
	CVector3 enemyFront;
	enemyFront.x = worldMatrix.m[2][0];
	enemyFront.y = worldMatrix.m[2][1];
	enemyFront.z = worldMatrix.m[2][2];
	enemyFront.Normalize();
	//�p�x���v�Z
	float angle = attackDir.Dot(enemyFront);
	if (angle > 1.0f)
	{
		angle = 1.0f;
	}
	else if (angle < -1.0f)
	{
		angle = -1.0f;
	}
	angle = acosf(angle);
	//��]������������߂�
	CVector3 cross = attackDir;
	cross.Cross(enemyFront);
	if (cross.y > 0.0f)
	{
		angle *= -1.0f;
	}
	//��]������
	CQuaternion addRotation;
	addRotation.SetRotation(CVector3::AxisY, angle);
	m_rotation.Multiply(addRotation);
}
