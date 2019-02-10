#pragma once

class Map;
class CWeaponSelect;
class CPlayerHp;
class CLevelUp;
class CMenu;
class CResult;
class CGameSound;
class CMessage;
class CChoices;
class CArrowRemain;

class CBossScene : public IGameObject
{
public:
	//�R���X�g���N�^
	CBossScene() {};

	//�f�X�g���N�^
	~CBossScene() {};

	//�X�V�����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//���ʑO�ɌĂяo�����
	void BeforeDead() override;

	//�}�b�v�̎擾
	Map* GetMap()
	{
		return m_map;
	}

	//���j���[�̎擾
	CMenu* GetMenu()
	{
		return m_menu;
	}

private:
	Map*			m_map = nullptr;			//�}�b�v
	CWeaponSelect*	m_weaponSelect = nullptr;	//����I��
	CPlayerHp*		m_playerHp = nullptr;		//�v���C���[HP
	CLevelUp*		m_levelUp = nullptr;		//���x���A�b�v�\��
	CMenu*			m_menu = nullptr;			//���j���[
	CResult*		m_result = nullptr;			//���U���g
	CGameSound*		m_gameSound = nullptr;		//�Q�[���T�E���h
	CMessage*		m_message = nullptr;		//���b�Z�[�W�\��
	CChoices*		m_choices = nullptr;		//�I�����\��
	CArrowRemain*	m_arrowRemain = nullptr;	//��̎c�e��
};