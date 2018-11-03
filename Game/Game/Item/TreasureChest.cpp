#include "stdafx.h"
#include "TreasureChest.h"
#include "../Player/Player.h"
#include "../../Game/Camera/GameCamera.h"

void CTreasureChest::Init(CVector3 position)
{
	//���f���̏�����
	m_skinModel.Load(L"Assets/modelData/heart.cmo");
	m_position = position;
	m_characterController.Init(0.2f, 0.2f, m_position);

	//���ɓ���镐��̎�ނƃX�e�[�^�X�������_���Ō��߂�
	//���
	int weaponNumber = Random().GetRandSInt();
	weaponNumber %= CWeapon::enWeaponNum;
	//�X�e�[�^�X
	int weaponAttack = Random().GetRandSInt();
	weaponAttack %= 100;
	if (weaponNumber == CWeapon::EnPlayerWeapon::enSword)
	{
		//��
		m_weaponStatus.weaponNum = CWeapon::EnPlayerWeapon::enSword;
		weaponAttack += 50;
	}
	else if (weaponNumber == CWeapon::EnPlayerWeapon::enLongSword)
	{
		//�匕
		m_weaponStatus.weaponNum = CWeapon::EnPlayerWeapon::enLongSword;
		weaponAttack += 70;
	}
	else if (weaponNumber == CWeapon::EnPlayerWeapon::enArrow)
	{
		//�|
		m_weaponStatus.weaponNum = CWeapon::EnPlayerWeapon::enArrow;
		weaponAttack += 20;
	}
	else if (weaponNumber == CWeapon::EnPlayerWeapon::enTwinSword) 
	{
		//�o��
		m_weaponStatus.weaponNum = CWeapon::EnPlayerWeapon::enTwinSword;
		weaponAttack += 30;
	}
	m_weaponStatus.attack = weaponAttack;
}

bool CTreasureChest::Start()
{
	CVector3 popSpeed = CVector3::Zero;
	popSpeed.y = m_speed / 2.0f;
	m_characterController.SetMoveSpeed(popSpeed);

	return true;
}

void CTreasureChest::Update()
{
	if (GetPlayer().GetIsDied() || m_timer > m_itemDeadTime)
	{
		//�v���C���[�����S�������͈�莞�Ԃō폜
		Delete(this);
		return;
	}
	m_timer += GameTime().GetDeltaFrameTime();

	//�ړ����x���擾
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();

	//�n�ʂɐڒn������~�߂�
	if (!m_popEnd && m_characterController.IsOnGround()) {
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
		m_popEnd = true;
	}

	//�L�����N�^�[�R���g���[���[�Ɉړ����x��ݒ�
	m_characterController.SetMoveSpeed(moveSpeed);

	//�v���C���[�Ƃ̋������v�Z
	CVector3 toPlayer = GetPlayer().GetPosition() - m_position;
	float length = toPlayer.Length();
	if (m_popEnd && length < 2.0f && Pad().IsTriggerButton(enButtonA)) {
		//�߂���Ίl��
		//if (!m_animation.IsPlay())
		//{
			GetPlayer().AddEquipList(m_weaponStatus);
			m_characterController.RemovedRigidBody();
			SetIsActive(false);
			return;
		//}
	}

	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);
}

void CTreasureChest::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}