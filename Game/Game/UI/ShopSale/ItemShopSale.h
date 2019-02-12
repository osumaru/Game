#pragma once
//�A�C�e���V���b�v�Ŕ��p���̉�� 
class IShop;
#include "../../Item/ItemList.h"

class CItemShopSale : public IGameObject
{
public:
	void Init();

	void Update()override;

	void PostAfterDraw()override;

private:
	SItemStatus			m_choiceItemStatus;
	CSprite				m_headline;					//����
	CSprite				m_backGround;				//�w�i
	CSprite				m_inventoryWindow;			//�C���x���g���E�B���h�E
	CSprite				m_pointer;					//�J�[�\��
	CSprite				m_itemFrame[CItemList::m_itemLimit];	//�C���x���g���̘g
	CSprite				m_itemWindow;				//�A�C�e���E�B���h�E
	CSprite				m_buttonBackground;			//�{�^���w�i
	CFont				m_itemName;					//�A�C�e���̖��O
	CVector2			m_basePos = CVector2::Zero;	//�������W
	CVector2			m_size = CVector2::Zero;	//�����T�C�Y
	int					m_width = 0;				//�C���x���g���̕�
	int					m_height = 0;				//�C���x���g���̍���
	int					m_pointerNum = 0;			//�J�[�\���őI��ł���A�C�e���̔ԍ�
	CFont				m_money;
};