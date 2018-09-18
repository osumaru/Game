/*
*	�Q�[���V�[���N���X
*/

#pragma once

class Map;
class CWeaponSelect;

class CGameScene : public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update();

	Map* GetMap()
	{
		return map;
	}

	CWeaponSelect*	GetWeaponSelect()
	{
		return m_weaponSelect;
	}

private:
	Map* map = nullptr;			//�}�b�v
	CWeaponSelect* m_weaponSelect = nullptr;
};
