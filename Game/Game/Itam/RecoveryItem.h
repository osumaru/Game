/*
*	�񕜃A�C�e���N���X
*/

#pragma once

class CRecoveryItem : public IGameObject
{
public:
	//������
	//position	���W
	void Init(CVector3 position);

	//�X�V
	void Update();

	//�`��
	void Draw();

private:
	CSkinModel m_skinModel;	//�X�L�����f��
	CVector3 m_position;	//���W
};
