/*
*	�C���x���g���N���X
*/
#pragma once

class CMenu;
class IInventoryItem;

class CItemInventory : public IGameObject
{
public:
	//�R���X�g���N�^
	CItemInventory();

	//�f�X�g���N�^
	~CItemInventory();

	//������
	//menu	���j���[�̃|�C���^
	void Init(CMenu* menu);

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void AfterDraw() override;

	//�J�[�\���ړ�
	void PointerMove();

	//�A�C�e�����g�p����
	void UseItem();

	//�����A�C�e�����X�g�ɒǉ�
	//item		�A�C�e�����X�g�ɒǉ�����A�C�e��
	static void AddItemList(IInventoryItem* item);

private:
	static const int					m_itemLimit = 15;				//�A�C�e���������
	static std::list<IInventoryItem*>	m_itemList;						//�A�C�e�����X�g
	CMenu*								m_menu = nullptr;				//���j���[
	CSprite								m_backGround;					//�w�i
	CSprite								m_pointer;						//�J�[�\��
	CSprite								m_itemFrame[m_itemLimit];		//�C���x���g���̘g
	CFont								m_itemName;						//�A�C�e���̖��O
	CVector2							m_basePos = CVector2::Zero;		//�������W
	CVector2							m_size = CVector2::Zero;		//�����T�C�Y
	int									m_width = 0;					//�C���x���g���̕�
	int									m_height = 0;					//�C���x���g���̍���
	int									m_pointerNum = 0;				//�J�[�\���őI��ł���A�C�e���̔ԍ�
};