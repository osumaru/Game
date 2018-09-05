/*
*	�~�j�}�b�v�N���X
*/

#pragma once

class CMiniMap : public IGameObject
{
public:
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

private:
	CSprite m_miniMap;				//�~�j�}�b�v
	CTexture m_miniMapTexture;

	CSprite m_playerIcon;			//�v���C���[�A�C�R��
	CTexture m_playerIconTexture;
	CVector3 m_playerFowardOld;
};
