#include "stdafx.h"
#include "Maw.h"
#include "../Camera/GameCamera.h"
#include "../Player/Player.h"
#include "../UI/BossHp/BossHp.h"
#include "../UI/WeekPoint/WeekPoint.h"
#include "../Scene/SceneManager.h"
#include"../GameSound/GameSound.h"

CMaw *CMaw::m_maw = NULL;

//�_���[�W�A�j���[�V�����͓���Ȃ��悤�ɂ��ă_�E���̃A�j���[�V���������ɂ���H
//�U�����[�V�����𕡐����ꂽ��
//

CMaw::CMaw()
{
	this->SetIsActive(false);
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
	if (wcscmp(animClipName, L"Assets/modelData/MawAttack.tka") == 0&&!m_isAttack) 
	{
		m_isAttack = true;
	}
	else if((wcscmp(animClipName, L"Assets/modelData/MawAttack.tka") == 0 &&m_isAttack))
	{
		m_isAttack = false;
	}

	//������x�Ă΂��ԍU��������I���ɂ��Ă���
	if (wcscmp(animClipName, L"Assets/modelData/MawSpecialAttack.tka") == 0 && !m_isAttack)
	{
		m_isAttack = true;
	}
	else if ((wcscmp(animClipName, L"Assets/modelData/MawSpecialAttack.tka") == 0 && m_isAttack))
	{
		m_isAttack = false;
	}
}

//������
void CMaw::Init(CVector3 position)
{
	m_bossHp = New<CBossHp>(PRIORITY_UI);
	m_bossHp->Init();

	m_weekPoint = New<CWeekPoint>(PRIORITY_UI);
	m_weekPoint->Init();
	//�X�e�[�^�X��ݒ�
	m_status.Strength = 10;
	m_status.Defense = 0;
	m_status.Hp = 50;
	m_status.MaxHp = m_status.Hp;
	m_status.Gold = 100;

	//�L�����R���̐ݒ�
	const float Height = 12.0f;
	const float radius = 4.0f;
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
			{ L"Assets/modelData/MawAttack2.tka" },			//�U���A�j���[�V����
			{ L"Assets/modelData/MawSpecialAttack2.tka" },	//�U���A�j���[�V����
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
	//��_�̓��̃{�[�����擾
	CMatrix WeekMat = m_skinModel.FindBoneWorldMatrix(L"Head");
	m_weekPosition.x = WeekMat.m[3][0];
	m_weekPosition.y = WeekMat.m[3][1];
	m_weekPosition.z = WeekMat.m[3][2];
	//m_weekPosition.Normalize();
	//�ŏ��̍s����I��
	m_actionPattern = EnMawActionPattern::enActionPatternIdle;

	m_weekPoint->SetIsActive(false);
	m_bossHp->SetIsActive(false);
	SetIsActive(true);
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
	case EnMawActionPattern::enActionPatternSearch:
		//�v���C���[��T����]�Ȃ�
		Search();
		break;
	case EnMawActionPattern::enActionPatternIdle:
		//�ҋ@���
		Idle();
		break;
	case EnMawActionPattern::enActionPatternDeath:
		//���S���
		Death();
		break;
	default:
		break;
	}

	//��_�`��̍X�V
	WeekPointUpdate();

	
	//��_�̓��̃{�[�����擾
	CMatrix WeekMat=m_skinModel.FindBoneWorldMatrix(L"Head");
	m_weekPosition.x = WeekMat.m[3][0];
	m_weekPosition.y = WeekMat.m[3][1];
	m_weekPosition.z = WeekMat.m[3][2];
	
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

//��_�`��̍X�V
void CMaw::WeekPointUpdate()
{
	CVector3 CameraForward = GetGameCamera().GetCamera().GetFlont();
	CameraForward.y = 0.0f;
	CameraForward.Normalize();
	CVector3 toEnemyDir = m_position - GetGameCamera().GetCamera().GetPosition();
	float length = toEnemyDir.Length();
	toEnemyDir.y = 0.0f;
	toEnemyDir.Normalize();

	float angle = toEnemyDir.Dot(CameraForward);

	//�J�����̎��E�ɓ�������
	if (angle > 0.0f&&length<40.0f)
	{
		m_weekPoint->SetIsActive(true);
		
	}
	else
	{
		m_weekPoint->SetIsActive(false);
	}



}

//�s���̑I��
//void CMaw::ActionStateOrder()
//{
//	//�����_����߂�H
//
//	/*const int AttackPattern = 2;
//	//int�^�����_�����擾
//	int RandomInt = Random().GetRandInt();
//	//�U���p�^�[���̐��ɕύX
//	RandomInt %= AttackPattern;
//	//-�ɂȂ�Ȃ��悤�ɐ�Βl�ɕϊ��H
//	RandomInt = fabs(RandomInt);
//	//�U���p�^�[���̌^�ɕϊ�
//	m_actionPattern = (EnMawActionPattern)RandomInt;
//	*/
//
//}

//�U���s��
void CMaw::Attack()
{
	const float PlayerDamageLengthMax = 8.5f;//�v���C���[�Ƀ_���[�W��^����ő勗��

	//�A�j���[�V�����Đ�
	bool IsAnim=Anim(EnMawState::enState_Attack);
	
	//�U�����I����Ă�����
	if (!IsAnim)
	{
		//���G�X�e�[�g��
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
	}

	HandAttack(PlayerDamageLengthMax);
}
//����U��
void CMaw::SpecialAttack()
{
	const float PlayerDamageLengthMax = 7.5f;//�v���C���[�Ƀ_���[�W��^����ő勗��

	//�A�j���[�V�����Đ�
	bool IsAnim = Anim(EnMawState::enState_SpecialAttack);

	//�U�����I����Ă�����
	if (!IsAnim)
	{
		//���G�X�e�[�g��
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
	}

	HandAttack(PlayerDamageLengthMax);
}

//�_�E�����
void CMaw::Down()
{
	const float MaxDownTime = 10.0f;		//�ő�_�E������

	//�A�j���[�V�����Đ�
	Anim(EnMawState::enState_Down);
	m_bossHp->SetIsActive(true);
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
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
		//ActionStateOrder();
		m_downTime = 0.0f;
		m_isDown = false;
		m_weekPoint->SetIsActive(true);
		m_bossHp->SetIsActive(false);
	}
}

//�T�����
void CMaw::Search()
{
	const float AttackDeg = 40.0f;			//�U���͈�
	const float SpecialAttackDeg = 30.0f;	//����U���͈�
	const float FindLength = 18.0f;			//��������

	//�A�j���[�V�����Đ�
	Anim(EnMawState::enState_Walk);

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

	//�����ċ��U���͈͂ɓ�������
	if (fabsf(angle) < CMath::DegToRad(SpecialAttackDeg) && length < FindLength)
	{
		m_actionPattern = EnMawActionPattern::enActionPatternSpecialAttack;
	}
	else if (fabsf(angle) < CMath::DegToRad(AttackDeg) && length < FindLength)
	{
		//�����čU���͈͂ɓ�������	//�����čU���͈͂ɓ�������
		m_actionPattern = EnMawActionPattern::enActionPatternAttack;
	}
	else
	{
		
		//������Ȃ�������T��
		CQuaternion addRot;
		const float RotSpeed = 0.01f;
		//Y���̃N�H�[�^�j�I�����쐬
		addRot.SetRotation(CVector3::AxisY,RotSpeed);

		CQuaternion rot = m_rotation;
		//�N�H�[�^�j�I������Z
		rot.Multiply(rot, addRot);
		m_rotation = rot;

	}
	//const float LengeAttackLength = 30.0f;		//�������U������
	//const float StandLength = 75.0f;			//�퓬�I������
	////�������U���A�j���[�V����
	////Anim(EnMawState::enState_Idle);

	//CVector3 toPlayerDir = GetPlayer().GetPosition() - m_position;
	//float length = toPlayerDir.Length();

	////�v���C���[�������ɗ��ꂽ��
	//if (length > StandLength)
	//{
	//	//�ҋ@�X�e�[�g��
	//	m_actionPattern = EnMawActionPattern::enActionPatternIdle;
	//}
	//else if (length > LengeAttackLength)
	//{
	//	//�������U���X�e�[�g��
	//}
}

//�ҋ@���
void CMaw::Idle()
{
	const float SearchLength = 70.0f;//�͈͋���
	//�A�j���[�V����
	Anim(EnMawState::enState_Idle);

	CVector3 toPlayerDir = GetPlayer().GetPosition() - m_position;
	float length = toPlayerDir.Length();

	//�v���C���[���߂��ɗ�����
	if (length < SearchLength)
	{
		//���G�X�e�[�g��
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
		m_isBattle = true;
	}
}

//���S���
void CMaw::Death()
{
	//���S�A�j���[�V����
	bool IsAnim = Anim(EnMawState::enState_Death);
	if (!IsAnim)
	{
		//�N���A�V�[���֑J��
		GetSceneManager().ChangeScene(GetSceneManager().enClearScene);
	}
}

//�A�j���[�V����
bool CMaw::Anim(EnMawState animState)
{
	const float InterpolationTime = 0.3f;//��Ԏ���
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
	CMatrix BossLeftHandMat = m_skinModel.FindBoneWorldMatrix(L"RightHand");
	CVector3 BossLeftHandPos;
	BossLeftHandPos.x = BossLeftHandMat.m[3][0];
	BossLeftHandPos.y = BossLeftHandMat.m[3][1];
	BossLeftHandPos.z = BossLeftHandMat.m[3][2];
	//�v���C���[���W���擾
	CVector3 playerPosition = GetPlayer().GetPosition();
	//�G�̍U���Ƃ̋������v�Z
	CVector3 distance = BossLeftHandPos - playerPosition;
	float PlayerDamageLength = distance.Length();
	if (PlayerDamageLength < PlayerDamageLengthMax) {
		//�v���C���[���_���[�W���󂯂�
		GetPlayer().SetDamage(m_status.Strength);
	}
	
}

//�_���[�W����
void CMaw::SetIsDamage(bool isDamage)
{
	//�_���[�W�Ԋu��0���傫��������
	if (m_damageInterval > 0.0f) { return; }
	const float		MaxInterval = 5.0f;	//�ő�_���[�W�Ԋu
	const int		MaxDownCount = 0;	//�ő�_�E���J�E���g

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
		//�_�E��������
		m_isDamage = isDamage;
		m_actionPattern = EnMawActionPattern::enActionPatternDown;
		m_isDown = true;
		m_weekPoint->SetIsActive(false);
		m_downCount = 0;
	}
	//�_���[�W�Ԋu���ő�ɂ���
	m_damageInterval = MaxInterval;
}

//�`��
void CMaw::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	//���̕`��
	m_characterController.Draw();
}

//���S����O�ɌĂ΂��֐�
void CMaw::BeforeDead()
{
	Delete(m_bossHp);
	Delete(m_weekPoint);
}