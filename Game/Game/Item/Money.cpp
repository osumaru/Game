#include "stdafx.h"
#include "Money.h"
#include "../Player/Player.h"
#include"../../Game/Camera/GameCamera.h"

void CMoney::Init(const int gold)
{
	m_gold = gold;
}

bool CMoney::Start()
{
	return true;
}

void CMoney::Update()
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
		GetPlayer().GainGold(m_gold);
		Delete(this);
	}

	//�L�����N�^�[�R���g���[���[�Ɉړ����x��ݒ�
	m_characterController.SetMoveSpeed(m_moveSpeed);
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);

}

void CMoney::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}

void CMoney::Pop(CVector3 position)
{
	//���f���̏�����
	m_skinModel.Load(L"Assets/modelData/money.cmo");
	m_position = position;
	m_characterController.Init(0.2f, 0.2f, m_position);
	m_characterController.SetUserIndex(EnCollisionAttr::enCollisionAttr_Item);
	float distance = 3.0f;
	float popUpSpeed = 6.0f;
	//�����_���n�_�Ƀ|�b�v������
	RamdomPop(distance, popUpSpeed);
}