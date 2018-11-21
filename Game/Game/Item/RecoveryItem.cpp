#include "stdafx.h"
#include "RecoveryItem.h"
#include"../../Game/Camera/GameCamera.h"
#include "../Player/Player.h"

void CRecoveryItem::Init()
{
	m_itemType = Recovery;
}

bool CRecoveryItem::Start()
{
	return true;
}

void CRecoveryItem::Update()
{
	if (GetPlayer().GetIsDied() || m_timer > m_deadTime)
	{
		//�v���C���[�����S�������͈�莞�Ԃō폜
		Delete(this);
		return;
	}
	m_timer += GameTime().GetDeltaFrameTime();

	//�ړ����x���擾
	m_moveSpeed = m_characterController.GetMoveSpeed();
	//�n�ʂɐڒn���Ă��邩����
	bool isPopEnd = m_characterController.IsOnGround();
	if (isPopEnd) {
		//�|�b�v���I����Ă���
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 0.0f;
	}

	//�E�����Ƃ��ł��邩����
	bool isPickUp = PickUp(isPopEnd, 0.8f);
	if (isPickUp) {
		//�E�����Ƃ��ł���
		GetPlayer().AddItemList(this);
		SetIsActive(false);
	}

	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);
}

void CRecoveryItem::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

bool CRecoveryItem::Use()
{
	SplayerStatus playerStatus = GetPlayer().GetStatus();
	int playerHP = playerStatus.Health;
	int playerHPMax = playerStatus.MaxHealth;
	//�v���C���[��HP�ƍő�HP���r����
	if (playerHP < playerHPMax)
	{
		//�v���C���[��HP���񕜂�����
		GetPlayer().RecoveryHP(m_recoveryValue);
		Delete(this);
		return true;
	}
	return false;
}

void CRecoveryItem::Pop(CVector3 position)
{
	//���f���̏�����
	m_skinModel.Load(L"Assets/modelData/heart.cmo");
	m_position = position;
	m_characterController.Init(0.2f, 0.2f, m_position);
	m_characterController.SetUserIndex(EnCollisionAttr::enCollisionAttr_Item);
	float distance = 3.0f;
	float popUpSpeed = 6.0f;
	//�����_���n�_�Ƀ|�b�v������
	RamdomPop(distance, popUpSpeed);
}