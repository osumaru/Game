/*
*	�~�j�}�b�v�N���X
*/

#pragma once

class IEnemy;

class CMiniMap : public IGameObject
{
public:
	//������
	//enemyNum		�G�̐�
	void Init(std::list<IEnemy*> enemyList);

	//�X�V
	void Update();

	//�`��
	void Draw();

private:
	CSprite m_miniMap;							//�~�j�}�b�v
	CTexture m_miniMapTexture;

	CSprite m_playerIcon;						//�v���C���[�A�C�R��
	CTexture m_playerIconTexture;
	CVector3 m_playerIconVec = CVector3::AxisZ;	//�v���C���[�A�C�R���̌���

	CCamera m_camera;

	std::list<CSprite> m_enemyIconList;
	CTexture m_enemyIconTexture;

	std::list<IEnemy*> m_enemyList;

	CVector2 m_mapCenterPos;
};
