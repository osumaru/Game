#include "Command.h"
#include "../Player/Player.h"


void StandCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateStand);
}


void WalkCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateWalk);
}


void RunCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateRun);
}


void JumpCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateJump);
}


void AttackCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateAttack);
}


void DamageCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateDamage);
}


void StunCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateStun);
}

void AvoidanceCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateAvoidance);
}

void DiedCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateDied);
}

void WireMoveCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateWireMove);
}

void WireAttackCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateWireAttack);
}

void ArrowAttackCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateArrowAttack);
}

void ArrowShootCommand::Execute()
{
	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateArrowShoot);
}

void SkyCommand::Execute()
{

	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateSky);
}

void DownCommand::Execute()
{

	m_player->GetStateMachine().SetState(CPlayerState::enPlayerStateDown);
}