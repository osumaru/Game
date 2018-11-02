/*
*	�C���x���g���N���X
*/
#pragma once

class CMenu;
class IItem;

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

	//�A�C�e������������擾
	static int GetItemLimit()
	{
		return m_itemLimit;
	}

private:
	static const int	m_itemLimit = 15;				//�A�C�e���������
	CSprite				m_backGround;					//�w�i
	CTexture			m_backGroundTexture;
	CSprite				m_pointer;						//�J�[�\��
	CTexture			m_pointerTexture;
	CSprite				m_item[m_itemLimit];			//�A�C�e��
	std::list<IItem*>	m_itemList;						//�A�C�e�����X�g
	CMenu*				m_menu = nullptr;				//���j���[
	CVector2			m_basePos = CVector2::Zero;		//�������W
	CVector2			m_size = CVector2::Zero;		//�����T�C�Y
	int					m_width = 0;					//�C���x���g���̕�
	int					m_height = 0;					//�C���x���g���̍���
	int					m_pointerNum = 0;				//�J�[�\���őI��ł���A�C�e���̔ԍ�
};