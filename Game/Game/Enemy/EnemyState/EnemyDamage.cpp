#include "stdafx.h"
#include "EnemyDamage.h"
#include "../IEnemy.h"
#include "../../Player/Player.h"
#include "../../UI/DamageNumber/DamageNumber.h"

void CEnemyDamage::Init()
{
	//�_���[�W�A�j���[�V�������Đ�
	m_enemy->GetAnimation().Play(CEnemyState::enAnimation_Damage, 0.3f);

	//�_���[�W���l��������
	m_damageNumber = New<CDamageNumber>(PRIORITY_UI);
	m_damageNumber->Init(m_enemy);

	//�_���[�W���󂯂��t���O��߂�
	m_enemy->SetIsDamage(false);

	const CPlayerAttack* playerAttack = dynamic_cast<const CPlayerAttack*>(GetPlayer().GetStateMachine().GetState(CPlayerState::enPlayerStateAttack));
	float attackCount = (float)playerAttack->GetAttackCount();
	float maxAttackNum = (float)GetPlayer().GetWeaponManager().GetWeapon()->GetMaxAttackNum();

	//���C�̏�����
	m_friction = 0.03f;
	m_deceleration = 0.0f;
	m_knockBackScale = (attackCount + 1.0f) / maxAttackNum;
	//�X�^������U���ł��邩����
	m_wasStanAttack = GetPlayer().GetStanAttack();
	if (!m_wasStanAttack)
	{
		m_isNockBack = true;
	}
	//�ǂ̕���Ń_���[�W��H�������
	//m_enemy->SetAttackWeapon(*GetPlayer().GetWeaponManager().GetWeapon()->GetAttackWeapon());
	m_damageEffect.Init(L"Assets/Effect/DamageEffect.efk");
	m_damageEffect.Play();
	CVector3 effectPos = m_enemy->GetPosition();
	effectPos.y += 1.0f;
	m_damageEffect.SetPosition(effectPos);
	const float SCALE = 0.1f;
	m_damageEffect.SetScale({ SCALE, SCALE, SCALE });
	m_damageEffect.Update();

	//�_���[�W��
	const float DamageVolume = 0.3f;
	CSoundSource* DamageSound = New<CSoundSource>(0);
	DamageSound->Init("Assets/sound/Battle/EnemyDamage.wav");
	DamageSound->Play(false);
	DamageSound->SetVolume(DamageVolume);
}

bool CEnemyDamage::Start()
{
	//������
	Init();

	return true;
}

void CEnemyDamage::Update()
{
	m_enemy->Update();
	//�m�b�N�o�b�N������
	CVector3 moveSpeed = m_enemy->GetMoveSpeed();
	CVector3 knockBack = m_enemy->GetPosition() - GetPlayer().GetPosition();
	knockBack.y = 0.0f;
	knockBack.Normalize();
	if (m_deceleration >= m_knockBackSpeed * m_knockBackScale) {
		m_deceleration = m_knockBackSpeed * m_knockBackScale;
		m_isNockBack = false;
	}
	knockBack *= m_knockBackSpeed * m_knockBackScale - m_deceleration;
	m_friction += 0.03f;
	m_deceleration += m_friction;
	moveSpeed.x = knockBack.x;
	moveSpeed.z = knockBack.z;
	m_enemy->SetMoveSpeed(moveSpeed);

	//�v���C���[�Ƃ̋������v�Z����
	CVector3 playerPos = GetPlayer().GetPosition();
	CVector3 toPlayerPos = playerPos - m_enemy->GetPosition();
	float length = toPlayerPos.Length();
	//�U���͈͂ɂ��邩�ǂ�������
	bool isRange = m_enemy->CalucFanShape(10.0f, playerPos);

	if (m_enemy->GetStatus().hp <= 0)
	{
		//HP�������Ȃ�Ύ��S
		m_esm->ChangeState(CEnemyState::enState_Death);
	}
	else if (m_wasStanAttack)
	{
		//�X�^����ԂɂȂ�
		m_esm->ChangeState(CEnemyState::enState_Stan);
	}
	else if (!m_enemy->GetAnimation().IsPlay()) 
	{
		if (!m_isNockBack)
		{
			//�A�j���[�V�������I�����Ă���
			if (isRange && m_enemy->GetAttackLength())
			{
				//�߂���΍U��
				m_esm->ChangeState(CEnemyState::enState_Attack);
			}
			else
			{
				//�v���C���[��ǂ�������
				m_esm->ChangeState(CEnemyState::enState_Chase);
			}
		}
	}
	else if(m_enemy->GetIsDamage()) 
	{
		//������x�_���[�W���󂯂��珉����
		Init();
	}
}