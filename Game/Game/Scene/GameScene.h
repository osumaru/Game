/*
*	�Q�[���V�[���N���X
*/

#pragma once

class Map;

class CGameScene : public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update();

private:
	Map* map = nullptr;			//�}�b�v
};