#include "stdafx.h"
#include "Maw.h"
#include "../Camera/GameCamera.h"
#include "../Player/Player.h"

CMaw *CMaw::m_maw = NULL;

//�_���[�W�A�j���[�V�����͓���Ȃ��悤�ɂ��ă_�E���̃A�j���[�V���������ɂ���H
//�U�����[�V�����𕡐����ꂽ��
//

CMaw::CMaw()
{
}

CMaw::~CMaw()
{
}

//�A�j���[�V�����C�x���g���Ă΂�邲�ƂɌĂяo�����
void CMaw::OnInvokeAnimationEvent(
	const wchar_t* animClipName,
	const wchar_t* eventName
)
{
	//������x�Ă΂��ԍU��������I���ɂ��Ă���
	//if (wcscmp(animClipName, L"Assets/modelData/MawAttack.tka") == 0&&!m_isAttack) 
	//{
	//	m_isAttack = true;
	//}
	//else if((wcscmp(animClipName, L"Assets/modelData/MawAttack.tka") == 0 &&m_isAttack))
	//{
	//	m_isAttack = false;
	//}
}
//������
void CMaw::Init(CVector3 position)
{
	//�X�e�[�^�X��ݒ�
	m_status.Strength = 10;
	m_status.Defense = 0;
	m_status.Hp = 50;
	m_status.MaxHp = m_status.Hp;
	m_status.Gold = 100;

	//�L�����R���̐ݒ�
	const float Height = 10.0f;
	const float radius = 3.0f;
	const float Gravity = -9.8f;

	//���C�g�̐ݒ�
	const CVector4 AmbientLight = { 0.5f,0.5f,0.5f,1.0f };
	const CVector4 DiffuseLight= { 1.0f,1.0f,1.0f,1.0f };
	const CVector4 DiffuseLightDir= { 0.0f, -1.0f, 1.0f, 1.0f };

	//�v���C���[�̃X�L�������f���̃��[�h
	m_skinModel.Load(L"Assets/modelData/Maw.cmo", &m_animation);
	m_skinModel.LoadNormalmap(L"Assets/modelData/MAW_normal.png");

	m_position = position;
	m_characterController.Init(radius,Height, m_position);
	m_characterController.SetGravity(Gravity);
	//���C�g�̐ݒ�
	Light().SetAmbientLight(AmbientLight);
	Light().SetDiffuseLight(0,DiffuseLight);
	Light().SetDiffuseLightDir(0,DiffuseLightDir);

	//�A�j���[�V�����̏�����
	{
		wchar_t* animClip[EnMawState::enState_Num] = {
			{ L"Assets/modelData/MawStand.tka"},	//�ҋ@�A�j���[�V����	
			{ L"Assets/modelData/MawWalk.tka" },	//���s�A�j���[�V����
			{ L"Assets/modelData/MawAttack.tka" },	//�U���A�j���[�V����
			{ L"Assets/modelData/MawDamage.tka" },	//�_���[�W�A�j���[�V����
			{ L"Assets/modelData/MawDeath.tka" },	//���S�A�j���[�V����
		};

		m_animation.Init(animClip, EnMawState::enState_Num);
		m_animation.SetLoopFlg(EnMawState::enState_Idle, true);
		m_animation.SetLoopFlg(EnMawState::enState_Walk, true);
		//�ŏ��ɗ����A�j���[�V����������ɐݒ�
		m_animation.Play(EnMawState::enState_Walk);
		//�A�j���[�V�����C�x���g���X�i�[�̓o�^�@�Ăяo�����֐��̓o�^
		m_animation.AddAnimationEvent([&](auto animClipname, auto eventName) {
			OnInvokeAnimationEvent(animClipname, eventName);
		});
	}
	//�ŏ��̍s����I��
	//ActionStateOrder();
	m_actionPattern = EnMawActionPattern::enActionPatternFind;
}
//�X�V
void CMaw::Update()
{
	//�s���p�^�[���̑I��
	switch (m_actionPattern)
	{
	case EnMawActionPattern::enActionPatternAttack:
		//�ʏ�U��
		Attack();
		break;
	case EnMawActionPattern::enActionPatternSpecialAttack:
		//����U��
		SpecialAttack();
		//���̍s���̑I��
		ActionStateOrder();
		break;
	case EnMawActionPattern::enActionPatternDown:
		//�_�E�����
		Down();
		break;
	case EnMawActionPattern::enActionPatternFind:
		//�v���C���[��T����]�Ȃ�
		Find();
		break;
	case EnMawActionPattern::enActionPatternStand:
		//�ҋ@���
		Stand();
		//���̍s���̑I��
		ActionStateOrder();
		break;
	case EnMawActionPattern::enActionPatternDeath:
		//���S���
		Death();
		break;
	default:
		break;
	}
	//�_�E�������邩���S��Ԃ���Ȃ�������
	if (m_isDown&&m_actionPattern !=EnMawActionPattern::enActionPatternDeath)
	{
		//�_�E����Ԃ�
		m_actionPattern = EnMawActionPattern::enActionPatternDown;
	}

	//�_���[�W�Ԋu��0�ȏゾ������
	if (m_damageInterval >= 0.0f)
	{
		m_damageInterval -= GameTime().GetDeltaFrameTime();
	}
	///////////////////////////////�e�X�g�p
	//�U�����Ԃ��I�������
	float MaxAttackTime = 3.0f;
	if (m_attackTime > MaxAttackTime)
	{
		m_attackTime = 0.0f;
		m_isAttack = false;
	}

	//�U�����Ă�����
	if (m_isAttack)
	{
		m_attackTime += GameTime().GetDeltaFrameTime();
	}

	//�{�X�̑̂�������I�u�W�F�N�g�ɐG��Ă�����
	//if (m_characterController.GetGroundCollisionObject() != nullptr)
	//{
	//	//�ڐG���Ă���n�ʂ̃I�u�W�F�N�g��CF_KINEMATIC_OBJECT��������
	//	if (m_characterController.GetGroundCollisionObject()->getUserIndex() == m_characterController.GetGroundCollisionObject()->CF_KINEMATIC_OBJECT)
	//	{
	//		m_isBreakObjectHit = true;
	//	}

	//}
	/////////////////////////////////////////////////

	//�L�����R���ւ̍��W�ݒ�
	m_characterController.SetPosition(m_position);
	//�L�����R���̎��s
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	//���W���L�����R������擾
	m_position=m_characterController.GetPosition();

	//�A�j���[�V�����̍X�V
	m_animation.Update(GameTime().GetDeltaFrameTime());
	//�X�L�����f���̍X�V
	m_skinModel.Update(m_position, m_rotation,m_scale, true);
}
//�s���̑I��
void CMaw::ActionStateOrder()
{
	//int�^�����_�����擾
	int RandomInt = Random().GetRandInt();
	//�U���p�^�[���̐��ɕύX
	RandomInt %= m_attackPattern;
	//-�ɂȂ�Ȃ��悤�ɐ�Βl�ɕϊ��H
	RandomInt = fabs(RandomInt);
	//�U���p�^�[���̌^�ɕϊ�
	m_actionPattern = (EnMawActionPattern)RandomInt;
}
//�U���s��
void CMaw::Attack()
{
	float interpolationTime = 0.3f;		//��Ԏ���
	float PlayerHeight = 2.5f;			//�v���C���[�̍���
	float PlayerDamageLengthMax = 10.5f;//�_���[�W���󂯂�ő勗��
	//���݂̃A�j���[�V�������U������Ȃ�������
	if ( m_animation.GetCurrentAnimationNum() != EnMawState::enState_Attack)
	{
		//�U���A�j���[�V�����Đ�
		m_animation.Play(EnMawState::enState_Attack,interpolationTime);
		m_isAttack = true;
	}
	//�Đ����I����Ă��邩���݂̃A�j���[�V������������
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Attack)
	{
		//���̍s���̑I��
		ActionStateOrder();
	}

	//�v���C���[���_���[�W���󂯂Ă��Ȃ�������
	if (!GetPlayer().GetIsDamage()) {
		//��̃{�[���̃��[���h�s����擾
		CVector3 leftHandPosition = GetLeftHandBone();
		//�v���C���[���W���擾
		CVector3 playerPosition = GetPlayer().GetPosition();
		//�G�̍U���Ƃ̋������v�Z
		CVector3 distance = leftHandPosition - playerPosition;
		float PlayerDamageLength = distance.Length();
		if (PlayerDamageLength < PlayerDamageLengthMax) {
			//�v���C���[���_���[�W���󂯂�
			GetPlayer().GetDamage();
		}
		
	}
}
//����U��
void CMaw::SpecialAttack()
{
	float interpolationTime = 0.3f;//��Ԏ���
	//���݂̃A�j���[�V�������_���[�W����Ȃ�������
	if (m_animation.GetCurrentAnimationNum() != EnMawState::enState_Damage)
	{
		//�A�j���[�V�����Đ�
		m_animation.Play(EnMawState::enState_Damage,interpolationTime);
	}
	//�Đ����I����Ă��邩���݂̃A�j���[�V������������
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Damage)
	{
		//���̍s���̑I��
		//ActionStateOrder();
	}
}
//�_�E�����
void CMaw::Down()
{
	float interpolationTime = 0.3f;	//��Ԏ���
	float MaxDownTime = 50.0f;		//�ő�_�E������


	//���݂̃A�j���[�V�������_�E������Ȃ�������
	if ( m_animation.GetCurrentAnimationNum() != EnMawState::enState_Damage)
	{
		//�A�j���[�V�����Đ�
		m_animation.Play(EnMawState::enState_Damage);
	}
	//�Đ����I����Ă��邩���݂̃A�j���[�V������������
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Damage)
	{
		//���̍s���̑I��
		//ActionStateOrder();
	}

	//�_�E�����̍U��������������̏���
	//������HP�o�[��\������H
	if (m_isDamage)
	{
		//�_���[�W�v�Z
		int playerStrength = GetPlayer().GetStatus().Strength;
		int damage = playerStrength - m_status.Defense;
		m_status.Hp -= damage;
		m_isDamage = false;
	}

	//HP��0�ȉ��ɂȂ�����
	if (m_status.Hp <= 0)
	{
		//���S�X�e�[�g��
		m_actionPattern = EnMawActionPattern::enActionPatternDeath;
	}
	m_downTime += GameTime().GetDeltaFrameTime();

	//�ő�_�E�����Ԃ𒴂��Ă�����
	if (m_downTime > MaxDownTime)
	{
		//���̍s���̑I��
		ActionStateOrder();
		m_downTime = 0.0f;
		m_isDown = false;
	}
}
//�T�����
void CMaw::Find()
{
	float interpolationTime = 0.3f;	//��Ԏ���
	float FindDeg = 50.0f;			//�����͈�
	float FindLength = 15.0f;		//��������
	//���݂̃A�j���[�V�������ҋ@����Ȃ�������
	if ( m_animation.GetCurrentAnimationNum() != EnMawState::enState_Idle)
	{
		//�A�j���[�V�����Đ�
		m_animation.Play(EnMawState::enState_Idle,interpolationTime);
	}
	//�Đ����I����Ă��邩���݂̃A�j���[�V������������
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Idle)
	{
		//���̍s���̑I��
		ActionStateOrder();
	}
	//�ړ����x���擾
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();
	moveSpeed.y = 0.0f;

	CVector3 playerPos = GetPlayer().GetPosition();

	//���[���h�s�񂩂烂�f���̑O�������擾
	CMatrix enemyWorldMatrix = m_skinModel.GetWorldMatrix();
	CVector3 enemyForward;
	enemyForward.x = enemyWorldMatrix.m[2][0];
	enemyForward.y = 0.0f;
	enemyForward.z = enemyWorldMatrix.m[2][2];
	enemyForward.Normalize();

	CVector3 toPlayerDir = GetPlayer().GetPosition() - m_position;
	float length = toPlayerDir.Length();
	toPlayerDir.y = 0.0f;
	toPlayerDir.Normalize();

	float angle = toPlayerDir.Dot(enemyForward);
	angle = acosf(angle);

	//��������
	if (fabsf(angle) < CMath::DegToRad(FindDeg) && length <FindLength) {
		//���̍s���̑I��
		ActionStateOrder();
	}
}
//�ҋ@���
void CMaw::Stand()
{
	float interpolationTime = 0.3f;//��Ԏ���
	//���݂̃A�j���[�V�������ҋ@����Ȃ�������
	if ( m_animation.GetCurrentAnimationNum() != EnMawState::enState_Idle)
	{
		//�A�j���[�V�����Đ�
		m_animation.Play(EnMawState::enState_Idle, interpolationTime);
	}
	//�Đ����I����Ă��邩���݂̃A�j���[�V������������
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Idle)
	{
		//���̍s���̑I��
		//ActionStateOrder();
	}
}
//���S���
void CMaw::Death()
{
	float interpolationTime = 0.3f;//��Ԏ���
	//���݂̃A�j���[�V���������S����Ȃ�������
	if (m_animation.GetCurrentAnimationNum() != EnMawState::enState_Death)
	{
		//�A�j���[�V�����Đ�
		m_animation.Play(EnMawState::enState_Death, interpolationTime);
	}
	//�Đ����I����Ă��邩���݂̃A�j���[�V������������
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() == EnMawState::enState_Death)
	{
		//���̍s���̑I��
		//ActionStateOrder();
		//�N���A�V�[���֑J�ځH

		//this->SetIsActive(false);
	}
}
//�_���[�W����
void CMaw::SetIsDamage(bool isDamage)
{
	//�_���[�W�Ԋu��0���傫��������
	if (m_damageInterval > 0.0f) { return; }
	float	MaxInterval = 5.0f;	//�ő�_���[�W�Ԋu
	int		MaxDownCount = 3;	//�ő�_�E���J�E���g
	m_isDamage = isDamage;
	//�_�E�����Ă��Ȃ�������
	if (!m_isDown)
	{
		m_downCount++;
		m_isDamage = false;
	}

	//�_�E���J�E���g���ő�_�E���J�E���g���傫��������
	if (m_downCount > MaxDownCount)
	{
		m_isDown = true;//�_�E��������
		m_downCount = 0;
	}
	//�_���[�W�Ԋu���ő�ɂ���
	m_damageInterval = MaxInterval;
}
//�`��
void CMaw::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}