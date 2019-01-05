/*
*	�{�X�����錚���̃N���X
*/

#pragma once

class CBossBuilding : public IGameObject
{
public:
	//������
	//position	���W
	void Init(CVector3 position);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
private:
	CSkinModel	m_skinModel;	//���f��
	CVector3	m_position;		//���W
	CQuaternion m_rotation;		//��]
};