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

class CGameScene : public IGameObject
{
public:

	//�J��
	void Release();

	//������
	void Init();

	//�X�V
	void Update() override;

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

private:
	Map*			m_map = nullptr;			//�}�b�v
	CWeaponSelect*	m_weaponSelect = nullptr;	//����I��
	CMiniMap*		m_miniMap = nullptr;		//�~�j�}�b�v
	CPlayerHp*		m_playerHp = nullptr;		//�v���C���[HP
	CLevelUp*		m_levelUp = nullptr;		//���x���A�b�v�\��
	CMenu*			m_menu = nullptr;			//���j���[
	CResult*		m_result = nullptr;			//���U���g
};
