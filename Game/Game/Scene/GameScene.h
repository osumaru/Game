/*
*	�Q�[���V�[���N���X
*/

#pragma once
class Map;
class CWeaponSelect;
class CMiniMap;
class CPlayerHp;
class CLevelUp;
class CMenu;
class CResult;
class CGameSound;

class CGameScene : public IGameObject
{
public:
	//�R���X�g���N�^
	CGameScene();
	//�f�X�g���N�^
	~CGameScene();

	//true���Ԃ����܂ŌJ��Ԃ��Ă΂��
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

	//����I���̎擾
	CWeaponSelect*	GetWeaponSelect()
	{
		return m_weaponSelect;
	}

	CGameSound* GetGameSound()
	{
		return m_gameSound;
	}

private:
	Map*			m_map = nullptr;			//�}�b�v
	CWeaponSelect*	m_weaponSelect = nullptr;	//����I��
	CMiniMap*		m_miniMap = nullptr;		//�~�j�}�b�v
	CPlayerHp*		m_playerHp = nullptr;		//�v���C���[HP
	CLevelUp*		m_levelUp = nullptr;		//���x���A�b�v�\��
	CMenu*			m_menu = nullptr;			//���j���[
	CResult*		m_result = nullptr;			//���U���g
	CGameSound*		m_gameSound = nullptr;		//�Q�[���T�E���h
};
