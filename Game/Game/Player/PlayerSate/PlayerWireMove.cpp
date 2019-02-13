#include "stdafx.h"
#include "PlayerWireMove.h"
#include "../Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"
CPlayerWireMove::CPlayerWireMove()
{
	m_hitEffect.Init(L"Assets/Effect/DamageEffect.efk");
}

void CPlayerWireMove::Init()
{
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationWireThrow, 0.25f);
	m_movePosition = m_pPlayer->GetWireAction().GetWirePosition();	
	CVector3 playerPos = GetPlayer().GetPosition();
	playerPos.y += m_pPlayer->GetWireAction().GetOffsetY();
	m_moveDirection = m_movePosition - playerPos;
	m_moveDirection.Normalize();
	m_accel = 0.0f;
	m_moveSpeed = 0.0f;
	m_wireSpeed = 1.0f;
	m_isWireThrow = true;
	//�v���C���[�̎�̃��[���h�s����擾
	m_playerHandMatrix = &m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"LeftHand");
	//���C���[�`����X�V
	UpdateWireDraw();

	const float WireAttackVolume = 0.3f;
	CSoundSource* WireAttackSound = New<CSoundSource>(0);
	WireAttackSound->Init("Assets/sound/Battle/WireThrow.wav");
	WireAttackSound->Play(false);
	WireAttackSound->SetVolume(WireAttackVolume);
	const float WindVolume = 0.1f;
	m_windSound = New<CSoundSource>(0);
	m_windSound->Init("Assets/sound/Battle/magic-wind.wav");
	//m_windSound->Play(true);
	m_windSound->SetVolume(WindVolume);
}

void CPlayerWireMove::Update()
{
	//�_���[�W���󂯂��ꍇ�̏���
	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
		//�Đ���~
		m_windSound->Stop();
		const float DamageVolume = 0.3f;
		CSoundSource* DamageSound = New<CSoundSource>(0);
		DamageSound->Init("Assets/sound/Battle/Damage.wav");
		DamageSound->Play(false);
		DamageSound->SetVolume(DamageVolume);
		//�ړ����I�����
		GetPlayer().GetWireAction().SetIsWireMove(false);
		//���C���[���G�l�~�[�ɓ��ĂĂ���
		if (GetPlayer().GetWireAction().GetHitEnemy() != nullptr)
		{
			//���C���[�ɓ��������t���O��߂�
			GetPlayer().GetWireAction().GetHitEnemy()->SetIsWireHit(false);
		}
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
		return;
	}

	//���C���[�`����X�V
	UpdateWireDraw();

	//���C���[�𓊂���A�j���[�V�������I������������
	if (m_pPlayerGetter->GetAnimation().GetCurrentAnimationNum() == enPlayerAnimationWireThrow
		&& !m_pPlayerGetter->GetAnimation().IsPlay())
	{
		m_windSound->Play(true);
		//���C���[�ړ�����A�j���[�V�����ɐ؂�ւ�
		m_isWireThrow = false;
		m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationWireMove, 0.25f);
	}
	if (m_isWireThrow)
	{
		//���C���[�𓊂���A�j���[�V���������Ă���
		return;
	}

	bool isMoveEnd = false;
	CVector3 playerPos = GetPlayer().GetPosition();
	playerPos.y += m_pPlayer->GetWireAction().GetOffsetY();
	CVector3 toMovePos = m_movePosition - playerPos;
	float angle = m_moveDirection.Dot(toMovePos);
	float length = toMovePos.Length();
	toMovePos = m_moveDirection;
	toMovePos.Normalize();
	m_accel += 0.1f;
	m_moveSpeed += m_accel;
	m_moveSpeed = min(m_moveSpeed, m_speed);
	toMovePos *= m_moveSpeed;
	float range = 2.0f;
	switch (m_pPlayer->GetWireAction().GetState())
	{
	case CWireAction::enStateEnemy:
		range = 2.0f;
		break;
	case CWireAction::enStateMap:
		range = 1.0f;
		break;
	}

	if (length < range || angle < 0.0f) {
		isMoveEnd = true;
		m_pPlayerGetter->SetPosition(m_movePosition);

	}
	else {
		//�ڕW�Ƃ̋���������Ă���Έړ���ɐi��
		float gravityBackup = m_pPlayerGetter->GetCharacterController().GetGravity();
		m_pPlayerGetter->GetCharacterController().SetGravity(0.0f);
		m_pPlayerGetter->SetMoveSpeed(toMovePos);
		m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());
		m_pPlayerGetter->SetPosition(m_pPlayerGetter->GetCharacterController().GetPosition());
		m_pPlayerGetter->GetCharacterController().SetGravity(gravityBackup);
	}

	if (isMoveEnd) {
		//�Đ���~
		m_windSound->Stop();

		//�ړ����I�����
		GetPlayer().GetWireAction().SetIsWireMove(false);
		IEnemy* enemy = GetPlayer().GetWireAction().GetHitEnemy();
		const float SCALE = 0.1f;
		switch(m_pPlayer->GetWireAction().GetState())
		{
		case CWireAction::enStateEnemy:
			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateWireAttack);
			//�G�l�~�[�Ƀ_���[�W�t���O�𗧂Ă�
			enemy->SetIsDamage(true);
			m_hitEffect.Play();
			m_hitEffect.SetPosition(enemy->GetPosition());
			m_hitEffect.SetScale({ SCALE, SCALE, SCALE });
			m_hitEffect.Update();
			//�G�l�~�[�̃��C���[�ɓ��������t���O��߂�
			enemy->SetIsWireHit(false);
			break;
		case CWireAction::enStateMap:
			if (0.0f < m_moveDirection.y)
			{
				//toMovePos.y = 10.0f;
				m_pPlayerGetter->SetMoveSpeed(toMovePos);
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateJump);
			}
			else
			{
				if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateRun))
				{
					m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateRun);
				}
				else
				{
					m_pPlayerGetter->SetPosition(m_movePosition);
					m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateSky);
					m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
				}
			}
			break;
		}
	}
	if (m_pPlayer->GetWireAction().GetState() == CWireAction::enStateMap && !Pad().IsPressButton(enButtonRightTrigger))
	{
		m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateSky);
		GetPlayer().GetWireAction().SetIsWireMove(false);
	}
}

void CPlayerWireMove::UpdateWireDraw()
{
	//���C���[�̎n�_�����߂�
	m_playerHandPos.x = m_playerHandMatrix->m[3][0];
	m_playerHandPos.y = m_playerHandMatrix->m[3][1];
	m_playerHandPos.z = m_playerHandMatrix->m[3][2];
	m_pPlayerGetter->GetWireDraw().SetStartPosition(m_playerHandPos);
	//���C���[�̏I�_�����߂�
	CVector3 currentWireDir = m_movePosition - m_playerHandPos;
	float length = currentWireDir.Length();
	CVector3 wireDir = currentWireDir;
	wireDir.Normalize();
	wireDir *= m_wireSpeed;
	m_wireSpeed += m_wireSpeed;
	//���C���[�̒������^�[�Q�b�g�܂ł̋����𒴂��Ă��邩
	if (length < wireDir.Length())
	{
		wireDir = currentWireDir;
	}
	CVector3 wireEndPos = m_playerHandPos + wireDir;
	m_pPlayerGetter->GetWireDraw().SetEndPosition(wireEndPos);
	//���C���[�`����X�V
	m_pPlayerGetter->GetWireDraw().Update();
}
