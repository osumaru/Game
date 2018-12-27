/*
*	�~�j�}�b�v�N���X
*/

#pragma once

class IEnemy;

class CMiniMap : public IGameObject
{
public:
	//�R���X�g���N�^
	CMiniMap();

	//�f�X�g���N�^
	virtual ~CMiniMap();

	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void AfterDraw();

private:
	CSprite									m_miniMap;				//�~�j�}�b�v
	CTexture*								m_miniMapTexture;
	CSprite									m_playerIcon;			//�v���C���[�A�C�R��
	CTexture*								m_playerIconTexture;
	std::vector<std::unique_ptr<CSprite>>	m_enemyIcon;			//�G�l�~�[�A�C�R��
	CTexture*								m_enemyIconTexture;
	std::list<IEnemy*>*						m_enemyList;			//�G�l�~�[���X�g
	CVector2								m_mapCenterPos;			//�~�j�}�b�v�̒��S���W
};
