/*
*	�Q�[���V�[���N���X
*/

#pragma once

class Map;
#include "../UI/DamageNumber/DamageNumber.h"

class CGameScene : public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update();

private:
	Map* map = nullptr;			//�}�b�v
	CDamegeNumber damageNumber;	//�_���[�W���l
};