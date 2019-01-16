#include "EnemyStan.h"
#include "../IEnemy.h"
#include "../../UI/DamageNumber/DamageNumber.h"

bool CEnemyStan::Start()
{
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Down, 0.3f);

	//�^�C�}�[��������
	m_timer = 0.0f;

	//�ړ����x��ݒ�
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	moveSpeed.x = 0.0f;
	moveSpeed.z = 0.0f;
	m_enemy->SetMoveSpeed(moveSpeed);

	//�_���[�W���󂯂��t���O��߂�
	m_enemy->SetIsDamage(false);

	return true;
}

void CEnemyStan::Update()
{
	//�_���[�W���󂯂������肷��
	if (m_enemy->GetIsDamage())
	{
		//�_���[�W���l��������
		m_damageNumber = New<CDamageNumber>(PRIORITY_UI);
		m_damageNumber->Init(m_enemy);
		//�_���[�W���󂯂��t���O��߂�
		m_enemy->SetIsDamage(false);
	}

	if (!m_enemy->GetAnimation().IsPlay()
		&& m_enemy->GetAnimation().GetCurrentAnimationNum() == CEnemyState::enAnimation_Down)
	{
		//�_�E�����̓^�C�}�[���J�E���g����
		m_timer += GameTime().GetDeltaFrameTime();
	}

	if (m_timer > 3.0f)
	{
		//�ړ����Ă���̂ō��W���X�V
		CMatrix spineMatrix = m_enemy->GetBoneWorldMatrix(L"Spine");
		CVector3 position;
		position.x = spineMatrix.m[3][0];
		position.y = spineMatrix.m[3][1];
		position.z = spineMatrix.m[3][2];
		m_enemy->SetPosition(position);
		//�^�C�}�[�����l�𒴂����痧���オ��
		m_enemy->GetAnimation().Play(CEnemyState::enAnimation_StandUp);
		m_timer = 0.0f;
	}

	if (!m_enemy->GetAnimation().IsPlay()
		&& m_enemy->GetAnimation().GetCurrentAnimationNum() == CEnemyState::enAnimation_StandUp) 
	{
		//�����オ������ǐՏ�Ԃɂ���
		m_esm->ChangeState(CEnemyState::enState_Chase);
	}
	else if (m_enemy->GetIsDead())
	{
		//HP���Ȃ���Ύ��S����
		m_esm->ChangeState(CEnemyState::enState_Death);
	}
}
