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

	////������x�Ă΂��ԍU��������I���ɂ��Ă���
	//if (wcscmp(animClipName, L"Assets/modelData/MawSpecialAttack.tka") == 0 && !m_isAttack)
	//{
	//	m_isAttack = true;
	//}
	//else if ((wcscmp(animClipName, L"Assets/modelData/MawSpecialAttack.tka") == 0 && m_isAttack))
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
	//m_skinModel.LoadNormalmap(L"Assets/modelData/MAW_normal.png");

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
			{ L"Assets/modelData/MawStand.tka"},			//�ҋ@�A�j���[�V����	
			{ L"Assets/modelData/MawWalk.tka" },			//���s�A�j���[�V����
			{ L"Assets/modelData/MawAttack.tka" },			//�U���A�j���[�V����
			{ L"Assets/modelData/MawSpecialAttack.tka" },	//�U���A�j���[�V����
			{ L"Assets/modelData/MawDamage.tka" },			//�_���[�W�A�j���[�V����
			{ L"Assets/modelData/MawDown.tka" },			//�_�E���A�j���[�V����
			{ L"Assets/modelData/MawDeath.tka" },			//���S�A�j���[�V����
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
	m_actionPattern = EnMawActionPattern::enActionPatternStand;
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
		break;
	case EnMawActionPattern::enActionPatternDeath:
		//���S���
		Death();
		break;
	default:
		break;
	}
	
	//�_���[�W�Ԋu��0�ȏゾ������
	if (m_damageInterval >= 0.0f&&!m_isDeath)
	{
		m_damageInterval -= GameTime().GetDeltaFrameTime();
	}

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
	const int AttackPattern = 2;
	//int�^�����_�����擾
	int RandomInt = Random().GetRandInt();
	//�U���p�^�[���̐��ɕύX
	RandomInt %= AttackPattern;
	//-�ɂȂ�Ȃ��悤�ɐ�Βl�ɕϊ��H
	RandomInt = fabs(RandomInt);
	//�U���p�^�[���̌^�ɕϊ�
	m_actionPattern = (EnMawActionPattern)RandomInt;

	//�_�E�������邩���S��Ԃ���Ȃ�������
	if (m_isDown&&m_actionPattern != EnMawActionPattern::enActionPatternDeath)
	{
		//�_�E����Ԃ�
		m_actionPattern = EnMawActionPattern::enActionPatternDown;
		return;
	}

	float Length = 30.0f;//�͈͋���
	//�������U���A�j���[�V����
	//Anim(EnMawState::enState_Idle);

	CVector3 toPlayerDir = GetPlayer().GetPosition() - m_position;
	float length = toPlayerDir.Length();

	//�v���C���[�������ɗ��ꂽ��
	if (length > Length)
	{
		//�������U���X�e�[�g��
	}
}
//�U���s��
void CMaw::Attack()
{
	float PlayerDamageLengthMax = 10.5f;//�_���[�W���󂯂�ő勗��

	//�A�j���[�V�����Đ�
	bool IsAnim=Anim(EnMawState::enState_Attack);
	
	//�U�����I����Ă�����
	if (!IsAnim)
	{
		//�����X�e�[�g��
		m_actionPattern = EnMawActionPattern::enActionPatternFind;
	}

	HandAttack(PlayerDamageLengthMax);
}
//����U��
void CMaw::SpecialAttack()
{
	float PlayerDamageLengthMax = 10.5f;//�_���[�W���󂯂�ő勗��

	//�A�j���[�V�����Đ�
	bool IsAnim = Anim(EnMawState::enState_SpecialAttack);

	//�U�����I����Ă�����
	if (!IsAnim)
	{
		//�����X�e�[�g��
		m_actionPattern = EnMawActionPattern::enActionPatternFind;
	}

	HandAttack(PlayerDamageLengthMax);
}
//�_�E�����
void CMaw::Down()
{
	float MaxDownTime = 50.0f;		//�ő�_�E������

	//�A�j���[�V�����Đ�
	Anim(EnMawState::enState_Down);

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
	float FindDeg = 50.0f;			//�����͈�
	float FindLength = 30.0f;		//��������

	//�A�j���[�V�����Đ�
	Anim(EnMawState::enState_Idle);

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
		m_isFind = true;
	}
	else
	{
		CQuaternion addRot;
		float RotSpeed = 0.005f;
		//Y���̃N�H�[�^�j�I�����쐬
		addRot.SetRotation(CVector3::AxisY,RotSpeed);

		CQuaternion rot = m_rotation;
		//�N�H�[�^�j�I������Z
		rot.Multiply(rot, addRot);
		m_rotation = rot;

	}
}
//�ҋ@���
void CMaw::Stand()
{
	float FindLength = 80.0f;//�͈͋���
	//�A�j���[�V����
	Anim(EnMawState::enState_Idle);

	CVector3 toPlayerDir = GetPlayer().GetPosition() - m_position;
	float length = toPlayerDir.Length();

	//�v���C���[���߂��ɗ�����
	if (length < FindLength)
	{
		//�����X�e�[�g��
		m_actionPattern = EnMawActionPattern::enActionPatternFind;
	}
}
//���S���
void CMaw::Death()
{
	//���S�A�j���[�V����
	bool IsAnim = Anim(EnMawState::enState_Death);
	if (!IsAnim)
	{
		//�N���A�V�[���֑J�ځH
	}
}
//�A�j���[�V����
bool CMaw::Anim(EnMawState animState)
{
	float InterpolationTime = 0.3f;//��Ԏ���
	//���݂̃A�j���[�V��������Ȃ�������
	if (m_animation.GetCurrentAnimationNum() != animState)
	{
		//�A�j���[�V�����Đ�
		m_animation.Play(animState,InterpolationTime);
		return true;
	}
	//�Đ����I����Ă��邩���݂̃A�j���[�V������������
	else if (!m_animation.IsPlay() && m_animation.GetCurrentAnimationNum() ==animState)
	{
		return false;
	}
	return true;
}
//��ł̍U��
void CMaw::HandAttack(float DamageLength)
{
	//�v���C���[���_���[�W���󂯂Ă��Ȃ�������
	if (GetPlayer().GetIsDamage()) { return; }

	float PlayerDamageLengthMax=DamageLength;
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
//�_���[�W����
void CMaw::SetIsDamage(bool isDamage)
{
	//�_���[�W�Ԋu��0���傫��������
	if (m_damageInterval > 0.0f) { return; }
	float		MaxInterval = 5.0f;	//�ő�_���[�W�Ԋu
	const int	MaxDownCount = 3;	//�ő�_�E���J�E���g

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