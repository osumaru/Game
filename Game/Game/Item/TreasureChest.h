/*
*	�����A�C�e���N���X
*/

#pragma once

#include "IItem.h"
#include "InventoryItem/IInventoryEquip.h"

class CTreasureChest : public IItem
{
public:
	enum EnDropType
	{
		enRandom,			//���߂�ꂽ�h���b�v�����烉���_���Ɏ��o���B
		enNormal,			//���A�x1�̓��������X�g����A�C�e�������o��
		enRare,				//���A�x2�̓��������X�g����A�C�e�������o��
		enLegend,			//���A�x3�̓��������X�g����A�C�e�������o��
		enSpecial,			//���A�x4�̓��������X�g����A�C�e�������o��
	};
	//������
	//position		���W
	//isMapItem		�}�b�v�ɔz�u���邩
	void Init(CVector3 position, CQuaternion rotation = {0.00f, 0.00f, 0.00f, 1.00f}, bool isMapItem = false, EnDropType dropType = enRandom);

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//����̃X�e�[�^�X�����߂�
	void DesideWeaponStatus();

private:
	std::unique_ptr<IInventoryEquip> m_inventoryEquip;	//�C���x���g���ɓ���鑕��
	EnDropType	m_dropType = EnDropType::enRandom;
	CLight	m_light;				//���C�g
	bool m_itemDrawCount = false;	//�A�C�e�����E��UI���o���J�E���g�����łɂ��Ă��邩
	bool m_isMapItem = false;		//�}�b�v�ɔz�u���邩
	std::unique_ptr<CRigidBody>			m_rigidBody;		//����
	std::unique_ptr<CMeshCollider>		m_meshCollider;		//�R���C�_�[
	std::unique_ptr<CBoxCollider>		m_boxCollider;		//�R���C�_�[
	bool								m_isItemeName = false;
	bool								m_isDrawItemName = false;
	float								m_drawTime = 0.0f;
};