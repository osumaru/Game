#include "stdafx.h"
#include "PlayerWireMove.h"
#include "../Player.h"
#include "../../Scene/SceneManager.h"
#include "../../Map/Map.h"
#include "../../Enemy/IEnemy.h"

void CPlayerWireMove::Init()
{
	m_pPlayerGetter->GetAnimation().Play(enPlayerAnimationWireThrow, 0.25f);
	m_movePosition = m_pPlayer->GetWireAction().GetWirePosition();
	m_accel = 0.0f;
	m_moveSpeed = 0.0f;
	m_wireSpeed = 1.0f;
	m_isWireThrow = true;
	//�v���C���[�̎�̃��[���h�s����擾
	m_playerHandMatrix = &m_pPlayer->GetSkinmodel().FindBoneWorldMatrix(L"LeftHand");
	//���C���[�`����X�V
	UpdateWireDraw();
}

void CPlayerWireMove::Update()
{
	//�_���[�W���󂯂��ꍇ�̏���
	if (m_pPlayer->GetIsStateCondition(CPlayerState::enPlayerStateDamage))
	{
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
	CVector3 moveVec = toMovePos;
	float length = toMovePos.Length();
	toMovePos.Normalize();
	m_accel += 0.3f;
	m_moveSpeed += m_accel;
	if (m_speed < m_moveSpeed)
	{
		m_moveSpeed = m_speed;
	}
	toMovePos *= m_moveSpeed;
	m_previousMoveSpeed = toMovePos;
	float range = 2.0f;

	float angle = 0.0f;
	switch (m_pPlayer->GetWireAction().GetState())
	{
	case CWireAction::enStateEnemy:
		range = 2.0f;
		break;
	case CWireAction::enStateMap:
		range = 1.0f;
		angle = moveVec.Dot(m_previousMoveSpeed);
		break;
	}
	if (length < range || angle < 0.0f) {
		isMoveEnd = true;
		if (angle)
		{
			m_pPlayerGetter->SetPosition(m_movePosition);
		}

	}
	else {
		//�ڕW�Ƃ̋���������Ă���Έړ���ɐi��
		m_pPlayerGetter->SetMoveSpeed(toMovePos);
		m_pPlayerGetter->GetCharacterController().Execute(GameTime().GetDeltaFrameTime());
		m_pPlayerGetter->SetPosition(m_pPlayerGetter->GetCharacterController().GetPosition());
	}

	if (isMoveEnd) {
		//�ړ����I�����
		GetPlayer().GetWireAction().SetIsWireMove(false);
		IEnemy* enemy = GetPlayer().GetWireAction().GetHitEnemy();
		switch(m_pPlayer->GetWireAction().GetState())
		{
		case CWireAction::enStateEnemy:
			m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateWireAttack);
			//�G�l�~�[�Ƀ_���[�W�t���O�𗧂Ă�
			enemy->SetIsDamage(true);
			//�G�l�~�[�̃��C���[�ɓ��������t���O��߂�
			enemy->SetIsWireHit(false);
			break;
		case CWireAction::enStateMap:
			if (Pad().IsPressButton(enButtonRightTrigger))
			{

				m_previousMoveSpeed.y = 10.0f;
				m_pPlayerGetter->SetMoveSpeed(m_previousMoveSpeed);
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateJump);
			}
			else
			{
				m_pPlayerGetter->SetPosition(m_movePosition);
				m_pPlayer->GetStateMachine().SetState(CPlayerState::enPlayerStateSky);
				m_pPlayerGetter->SetMoveSpeed(CVector3::Zero);
			}
			break;
		}
	}

	m_previousMoveSpeed = toMovePos;
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
