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
#include "PlayerStun.h"
#include "PlayerWireAttack.h"
#include "PlayerSky.h"

class CPlayer;
class CPlayerGetter;

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

	void SetPlayer(CPlayer* player, CPlayerGetter* playerGetter)
	{
		m_playerStand.SetPlayer(player, playerGetter);
		m_playerWalk.SetPlayer(player, playerGetter);
		m_playerRun.SetPlayer(player, playerGetter);
		m_playerAttack.SetPlayer(player, playerGetter);
		m_playerDamage.SetPlayer(player, playerGetter);
		m_playerDied.SetPlayer(player, playerGetter);
		m_playerJump.SetPlayer(player, playerGetter);
		m_playerAvoidance.SetPlayer(player, playerGetter);
		m_playerArrowAttack.SetPlayer(player, playerGetter);
		m_playerArrowShoot.SetPlayer(player, playerGetter);
		m_playerWireMove.SetPlayer(player, playerGetter);
		m_playerStun.SetPlayer(player, playerGetter);
		m_playerWireAttack.SetPlayer(player, playerGetter);
		m_playerSky.SetPlayer(player, playerGetter);
	}

	//���݂̃X�e�[�g���擾
	IPlayerState* GetCurrentState()
	{
		return m_currentState;
	}

	//�w�肵���X�e�[�g���擾
	IPlayerState* GetState(CPlayerState::EnPlayerState state)
	{
		return m_pStates[state];
	}


private:
	CPlayerState::EnPlayerState		m_state = (CPlayerState::EnPlayerState)-1;				//�v���C���[�̃A�j���[�V�����̏��
	
	IPlayerState*					m_currentState = nullptr;
	IPlayerState*					m_pStates[CPlayerState::enPlayerStateNum];
	CPlayerStand					m_playerStand;			//�ҋ@���[�V����
	CPlayerWalk						m_playerWalk;			//���s���[�V����
	CPlayerRun						m_playerRun;			//���胂�[�V����
	CPlayerAttack					m_playerAttack;			//�U�����[�V����
	CPlayerDamage					m_playerDamage;			//�_���[�W���[�V����
	CPlayerDied						m_playerDied;			//���S���[�V����
	CPlayerJump						m_playerJump;			//�W�����v���[�V����
	CPlayerAvoidance				m_playerAvoidance;		//������[�V����
	CPlayerArrowAttack				m_playerArrowAttack;	//�|�ł̍U�����[�V����
	CPlayerArrowShoot				m_playerArrowShoot;		//�|������[�V����
	CPlayerWireMove					m_playerWireMove;		//���C���[���[�V����
	CPlayerStun						m_playerStun;			//�X�^�����
	CPlayerWireAttack				m_playerWireAttack;		//���C���[�U�����[�V����
	CPlayerSky						m_playerSky;			//�󒆂ɂ�����
};

