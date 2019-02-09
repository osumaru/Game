#include "stdafx.h"
#include "RecoveryItem.h"
#include"../../Game/Camera/GameCamera.h"
#include "../Player/Player.h"
#include "../UI/Menu/ItemInventory.h"
#include "InventoryItem/InventoryRecoveryItem.h"
#include "../Scene/SceneManager.h"

void CRecoveryItem::Init(const CVector3& position)
{
	//���f���̏�����
	m_skinModel.Load(L"Assets/modelData/Potion.cmo");
	m_position = position;
	m_characterController.Init(0.2f, 0.2f, m_position);
	m_characterController.SetUserIndex(EnCollisionAttr::enCollisionAttr_Item);
	m_characterController.SetIgnoreRigidBody(&GetPlayer().GetCharacterController().GetBody());
}

bool CRecoveryItem::Start()
{
	float distance = 3.0f;
	float popUpSpeed = 6.0f;
	//�����_���n�_�Ƀ|�b�v������
	RamdomPop(distance, popUpSpeed);

	return true;
}

void CRecoveryItem::Update()
{
	if (GetSceneManager().GetSceneChange() || GetPlayer().GetIsDied() || (m_timer > m_deadTime && !m_isMove))
	{
		//�v���C���[�����S�������͈�莞�Ԃō폜
		Delete(this);
		return;
	}
	m_timer += GameTime().GetDeltaFrameTime();

	//�ړ����x���擾
	CVector3 moveSpeed = m_characterController.GetMoveSpeed();
	//�n�ʂɐڒn���Ă��邩����
	if (!m_isPopEnd && m_characterController.IsOnGround())
	{
		m_isPopEnd = true;
		moveSpeed.x = 0.0f;
		moveSpeed.z = 0.0f;
	}

	if (m_isPopEnd && !m_isMove)
	{
		//��]������
		const float angle = 3.0f;
		CVector3 axisY = CVector3::AxisY;
		CQuaternion addRot;
		addRot.SetRotationDeg(axisY, angle);
		m_rotation.Multiply(addRot);
		//�v���C���[�Ƃ̋��������߂�
		CVector3 playerPos = GetPlayer().GetPosition();
		CVector3 toPlayer = playerPos - m_position;
		float length = toPlayer.Length();
		//�A�C�e�����l���ł���͈͂Ƀv���C���[�����邩���肷��
		if (length < 5.0f)
		{
			m_isMove = true;
		}
	}

	if (m_isMove)
	{
		//�v���C���[�̕��Ɉړ�����
		moveSpeed = Move();
	}

	//�E�����Ƃ��ł��邩����
	bool isPickUp = PickUp(m_isPopEnd, 0.8f);
	if (isPickUp) {
		const float GetVolume = 0.3f;
		CSoundSource* GetSound = New<CSoundSource>(0);
		GetSound->Init("Assets/sound/Battle/ItemGet.wav");
		GetSound->Play(false);
		GetSound->SetVolume(GetVolume);
		//�E�����Ƃ��ł���
		std::unique_ptr<IInventoryItem> inventoryItem = std::make_unique<CInventoryRecoveryItem>();
		inventoryItem->Init();
		CItemInventory::AddItemList(std::move(inventoryItem));
		Delete(this);
	}

	m_characterController.SetMoveSpeed(moveSpeed);
	m_characterController.SetPosition(m_position);
	m_characterController.Execute(GameTime().GetDeltaFrameTime());
	m_position = m_characterController.GetPosition();

	m_skinModel.Update(m_position, m_rotation, { 1.0f,1.0f,1.0f }, true);
}

void CRecoveryItem::Draw()
{
	m_skinModel.Draw(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
}