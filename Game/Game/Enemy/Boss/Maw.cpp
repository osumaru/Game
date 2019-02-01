#include "stdafx.h"
#include "Maw.h"
#include "../../Camera/GameCamera.h"
#include "../../Player/Player.h"
#include "../../UI/BossHp/BossHp.h"
#include "../../UI/WeekPoint/WeekPoint.h"
#include "../../Scene/SceneManager.h"
#include "../../GameSound/GameSound.h"
#include "AttackWave.h"

CMaw *CMaw::m_maw = NULL;

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
	//�U�������؂�ւ���
	if (wcscmp(animClipName, L"Assets/modelData/MawAttack.tka") == 0) 
	{
		m_isAttack = !m_isAttack;
	}

	//�U�������؂�ւ���
	if (wcscmp(animClipName, L"Assets/modelData/MawSpecialAttack.tka") == 0)
	{
		
		if (m_isAttack)
		{
			SpecialAttackEnd();
		}
		m_isAttack = !m_isAttack;
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
	m_status.Hp = 100;
	m_status.MaxHp = m_status.Hp;
	m_status.Gold = 100;

	//�L�����R���̐ݒ�
	const float Height = 3.0f;
	const float radius = 2.0f;
	const float Gravity = -9.8f;



	//�v���C���[�̃X�L�����f���̃��[�h
	m_skinModel.Load(L"Assets/modelData/Maw.cmo", &m_animation);
	//m_skinModel.LoadNormalmap(L"Assets/modelData/MAW_normal.png");

	m_position = position;
	m_characterController.Init(radius,Height, m_position);
	m_characterController.SetGravity(Gravity);

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

		//�A�j���[�V�����C�x���g���X�i�[�̓o�^�@�Ăяo�����֐��̓o�^
		m_animation.AddAnimationEvent([&](auto animClipname, auto eventName) {
			OnInvokeAnimationEvent(animClipname, eventName);
		});
		//�ŏ��ɗ����A�j���[�V����������ɐݒ�
		m_animation.Play(EnMawState::enState_Walk);
	}

	////�G�t�F�N�g�̏�����
	//m_rippleEffect.Init(L"Assets/Effect/rippleEffect.efk");
	//m_rippleEffect.SetScale({ 1.0f,1.0f,1.0f });

	//��_�̓��̃{�[�����擾
	CMatrix WeekMat = m_skinModel.FindBoneWorldMatrix(L"Head");
	m_weekPosition.x = WeekMat.m[3][0];
	m_weekPosition.y = WeekMat.m[3][1];
	m_weekPosition.z = WeekMat.m[3][2];

	//�ŏ��̍s����I��
	m_actionPattern = EnMawActionPattern::enActionPatternIdle;

	//�{�X�̉��Ƀv���C���[�������Ă��܂����߃v���C���[�̍��͖̂���������H
	m_characterController.SetIgnoreRigidBody(&GetPlayer().GetCharacterController().GetBody());

	m_weekPoint->SetIsActive(false);
	SetIsActive(true);
}

//�X�V
void CMaw::Update()
{
	//�s���p�^�[���̑I��
	switch (m_actionPattern)
	{
	case EnMawActionPattern::enActionPatternAttack:
		Attack();//�ʏ�U��
		break;
	case EnMawActionPattern::enActionPatternSpecialAttack:
		SpecialAttack();//����U��
		break;
	case EnMawActionPattern::enActionPatternDown:
		Down();//�_�E�����
		break;
	case EnMawActionPattern::enActionPatternDamage:
		Damage();//�_���[�W
		break;
	case EnMawActionPattern::enActionPatternSearch:
		Search();//�v���C���[��T����]�Ȃ�
		break;
	case EnMawActionPattern::enActionPatternIdle:
		Idle();//�ҋ@���
		break;
	case EnMawActionPattern::enActionPatternDeath:
		Death();//���S���
		break;
	default:
		break;
	}

	if (m_isDamage)
	{
		m_status.Hp -= 10;
		m_isDamage = false;
		//HP��0�ȉ��ɂȂ�����
		if (m_status.Hp <= 0)
		{
			//���S�X�e�[�g��
			m_actionPattern = EnMawActionPattern::enActionPatternDeath;
		}
	}

	WeekPointUpdate();//��_�̍X�V
	
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
	if (angle > 0.0f && m_isDown)
	{
		m_weekPoint->SetIsActive(true);
	}
	else
	{
		m_weekPoint->SetIsActive(false);
	}

	//��_�̓��̃{�[�����擾
	CMatrix WeekMat = m_skinModel.FindBoneWorldMatrix(L"Head");
	m_weekPosition.x = WeekMat.m[3][0];
	m_weekPosition.y = WeekMat.m[3][1];
	m_weekPosition.z = WeekMat.m[3][2];
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
	const float PlayerDamageLengthMax = 4.0f;//�v���C���[�Ƀ_���[�W��^����ő勗��
	//�A�j���[�V�����Đ�
	bool IsAnimPlay=Anim(EnMawState::enState_Attack);
	//�U�����I����Ă�����
	if (!IsAnimPlay)
	{
		//���G�X�e�[�g��
		m_waitTime = 0.0f;
		m_actionPattern = enActionPatternIdle;
	}
	if (m_isAttack)
	{
		HandAttack(PlayerDamageLengthMax);
	}
}

//����U��
void CMaw::SpecialAttack()
{
	const float PlayerDamageLengthMax = 2.5f;//�v���C���[�Ƀ_���[�W��^����ő勗��
	//�A�j���[�V�����Đ�
	bool IsAnimPlay = Anim(EnMawState::enState_SpecialAttack);

	if (m_isAttack)
	{
		HandAttack(PlayerDamageLengthMax);
		m_isSpecialAttackRot = false;
	}
	if(m_isSpecialAttackRot)
	{
		CVector3 playerVec = GetPlayer().GetPosition() - m_position;
		Rotation(playerVec);
	}
	//�U�����I����Ă�����
	if (!IsAnimPlay)
	{
		//���G�X�e�[�g��
		m_actionPattern = EnMawActionPattern::enActionPatternDown;
		m_isDown = true;
		m_isSpecialAttackRot = true;
	}
}

void CMaw::SpecialAttackEnd()
{
	//const CMatrix handMatrix = m_skinModel.FindBoneWorldMatrix(L"LeftHand");
	//float offsetY = 0.01f;
	//CVector3 handPosition;
	//handPosition.x = handMatrix.m[3][0];
	//handPosition.y = m_position.y + offsetY;
	//handPosition.z = handMatrix.m[3][2];
	//m_rippleEffect.SetPosition(handPosition);
	//m_rippleEffect.Play();
	//m_rippleEffect.Update();

	CAttackWave* wave = New<CAttackWave>(PRIORITY_PARTICLE);
	const CMatrix handMatrix = m_skinModel.FindBoneWorldMatrix(L"LeftHand");
	float offsetY = 0.01f;
	CVector3 handPosition;
	handPosition.x = handMatrix.m[3][0];
	handPosition.y = m_position.y + offsetY;
	handPosition.z = handMatrix.m[3][2];
	wave->Init(&GetGameCamera().GetCamera(), handPosition);

	CShakeCamera& shakeCamera = GetGameCamera().GetShakeCamera();
	shakeCamera.SetDamping(0.7f);
	shakeCamera.ShakeStart(0.7f);
}
//�_�E�����
void CMaw::Down()
{
	m_characterController.SetMoveSpeed(CVector3::Zero);
	const float MaxDownTime = 3.0f;	//�ő�_�E������
	//�A�j���[�V�����Đ�
	Anim(EnMawState::enState_Down);

	//�ő�_�E�����Ԃ𒴂��Ă�����
	if (m_downTime > MaxDownTime)
	{
		m_downTime = 0.0f;
		m_isDown = false;
		//���̍s���̑I��
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
	}
	//�_�E�����̍U��������������̏���
	//������HP�o�[��\������H
	if (m_isDamage)
	{
		GameTime().SetFadeOutTime(0.5f);
		GameTime().SetSlowDelayTime(0.3f, 0.1f, 0.06f);
		//�_���[�W�v�Z
		int playerStrength = GetPlayer().GetStatus().Strength;
		int damage = playerStrength - m_status.Defense;
		damage *= 3;
		m_status.Hp -= damage;
		m_isDamage = false;

		m_downTime = 0.0f;
		m_isDown = false;
		//���̍s���̑I��
		m_actionPattern = EnMawActionPattern::enActionPatternDamage;
			
		//HP��0�ȉ��ɂȂ�����
		if (m_status.Hp <= 0)
		{
			//���S�X�e�[�g��
			m_actionPattern = EnMawActionPattern::enActionPatternDeath;
		}
	}
	m_downTime += GameTime().GetDeltaFrameTime();
}


void CMaw::Damage()
{
	//�A�j���[�V�����Đ�
	bool IsAnimPlay = Anim(EnMawState::enState_Damage);
	//�I����Ă�����
	if (!IsAnimPlay)
	{
		//���G�X�e�[�g��
		m_actionPattern = EnMawActionPattern::enActionPatternSearch;
	}
}

//�T�����
void CMaw::Search()
{
	const float AttackDeg = 40.0f;			//�U���͈�
	const float SpecialAttackDeg = 15.0f;	//����U���͈�
	const float FindLength = 3.0f;			//��������

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
		//�ړ�����߂�
		m_characterController.SetMoveSpeed(CVector3::Zero);
		m_actionPattern = EnMawActionPattern::enActionPatternSpecialAttack;
	}
	else if (fabsf(angle) < CMath::DegToRad(AttackDeg) && length < FindLength)
	{
		//�ړ�����߂�
		m_characterController.SetMoveSpeed(CVector3::Zero);
		//�����čU���͈͂ɓ�������
		m_actionPattern = EnMawActionPattern::enActionPatternAttack;
	}
	else
	{
		float Speed = 2.5f;
		CVector3 moveSpeed = m_characterController.GetMoveSpeed();
		toPlayerDir *= Speed;
		moveSpeed.x = toPlayerDir.x;
		moveSpeed.z = toPlayerDir.z;
		m_characterController.SetMoveSpeed(moveSpeed);
		Rotation(m_characterController.GetMoveSpeed());
	}
}

//��]
void CMaw::Rotation(const CVector3& rotVec)
{
	CMatrix worldMatrix = m_maw->GetWorldMatrix();
	CVector3 forwardXZ;
	forwardXZ.x = worldMatrix.m[2][0];
	forwardXZ.y = 0.0f;
	forwardXZ.z = worldMatrix.m[2][2];
	forwardXZ.Normalize();

	//�ړ����x���擾
	CVector3 moveSpeed = rotVec;
	moveSpeed.y = 0.0f;
	if (moveSpeed.LengthSq() < 0.01f) {
		//�ړ����Ă��Ȃ��Ɗp�x�̌v�Z���ł��Ȃ��̂ŕԂ�
		return;
	}
	moveSpeed.Normalize();
	float angle = moveSpeed.Dot(forwardXZ);
	angle = max(-1.0f, min(1.0f, angle));
	angle = acosf(angle);
	CVector3 directionJudge;
	directionJudge.Cross(moveSpeed, forwardXZ);
	if (0.0f < directionJudge.y)
	{
		angle = -angle;
	}
	CQuaternion addRot;
	addRot.SetRotation(CVector3::AxisY, angle);
	addRot.Slerp(0.3f, CQuaternion::Identity, addRot);
	CQuaternion rot = m_rotation;
	rot.Multiply(rot, addRot);
	m_rotation = rot;
}

//�ҋ@���
void CMaw::Idle()
{
	const float SearchLength = 60.0f;//�͈͋���
	//�A�j���[�V����
	Anim(EnMawState::enState_Idle);

	CVector3 toPlayerDir = GetPlayer().GetPosition() - m_position;
	float length = toPlayerDir.Length();
	const float MAX_WAIT_TIME = 2.0f;
	if (m_waitTime < MAX_WAIT_TIME)
	{
		m_waitTime += GameTime().GetDeltaFrameTime();
	}
	else
	{
		//�v���C���[���߂��ɗ�����
		if (length < SearchLength)
		{
			//���G�X�e�[�g��
			m_actionPattern = EnMawActionPattern::enActionPatternSearch;
			m_isBattle = true;
		}
	}
}

//���S���
void CMaw::Death()
{
	//���S�A�j���[�V����
	bool IsAnimPlay = Anim(EnMawState::enState_Death);
	//�I����Ă�����
	if (!IsAnimPlay)
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
	//�v���C���[���_���[�W���󂯂Ă�����
	if (GetPlayer().GetStanDamage()) { return; }

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
		//�v���C���[�ɃX�^���_���[�W��^����
		GetPlayer().SetStanDamage(m_status.Strength);
	}
}

//�_���[�W����
void CMaw::SetIsDamage(bool isDamage)
{
	m_isDamage = isDamage;
	m_characterController.SetMoveSpeed(CVector3::Zero);

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