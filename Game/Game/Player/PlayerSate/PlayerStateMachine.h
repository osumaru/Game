#pragma once
#include "PlayerState.h"
#include "PlayerStateCommon.h"
#include "PlayerStand.h"
#include "PlayerWalk.h"
#include "PlayerRun.h"
#include "PlayerAttack.h"
#include "PlayerArrowAttack.h"
#include "PlayerDamage.h"
#include "PlayerDied.h"
#include "PlayerJump.h"
#include "PlayerAvoidance.h"
#include "PlayerArrowShoot.h"
#include "PlayerWireMove.h"

class CPlayer;

class CPlayerStateMachine
{
public:
	void Init();

	// �X�V
	void Update();
			
	//�X�e�[�g�̐؂�ւ�
	void SetState(CPlayerState::EnPlayerState nextState);

	//���݂̃v���C���[�̏�Ԃ��擾
	CPlayerState::EnPlayerState GetState() const
	{
		return m_state;
	}

	void SetPlayer(CPlayer* player)
	{
		m_playerStand.SetPlayer(player);
		m_playerWalk.SetPlayer(player);
		m_playerRun.SetPlayer(player);
		m_playerAttack.SetPlayer(player);
		m_playerDamege.SetPlayer(player);
		m_playerDied.SetPlayer(player);
		m_playerJump.SetPlayer(player);
		m_playerAvoidance.SetPlayer(player);
		m_playerArrowAtack.SetPlayer(player);
		m_playerArrowShoot.SetPlayer(player);
		m_playerWireMove.SetPlayer(player);
	}

private:
	CPlayerState::EnPlayerState		m_state = CPlayerState::enState_Invald;				//�v���C���[�̃A�j���[�V�����̏��
	CPlayerState::EnPlayerState		m_AttackState = CPlayerState::enPlayerAttack;		//�U�����̃A�j���[�V�����̏��
	CPlayerState::EnPlayerState		m_ArrowAttackState = CPlayerState::enPlayerArrowAttack;	//�|��ł̍U�����̃A�j���[�V�����̏��
	
	IPlayerState*					m_currentState = nullptr;
	CPlayerStand					m_playerStand;			//�ҋ@���[�V����
	CPlayerWalk						m_playerWalk;			//���s���[�V����
	CPlayerRun						m_playerRun;			//���胂�[�V����
	CPlayerAttack					m_playerAttack;			//�U�����[�V����
	CPlayerDamage					m_playerDamege;			//�_���[�W���[�V����
	CPlayerDied						m_playerDied;			//���S���[�V����
	CPlayerJump						m_playerJump;			//�W�����v���[�V����
	CPlayerAvoidance				m_playerAvoidance;		//������[�V����
	CPlayerArrowAttack				m_playerArrowAtack;		//�|�ł̍U�����[�V����
	CPlayerArrowShoot				m_playerArrowShoot;		//�|������[�V����
	CPlayerWireMove					m_playerWireMove;		//���C���[���[�V����
};

