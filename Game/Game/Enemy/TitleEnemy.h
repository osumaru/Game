/*
*	�^�C�g���V�[���ɂ����G�l�~�[�N���X
*/

#pragma once

class CTitleEnemy : public IGameObject
{
public:
	//������
	//modelData		���f���̖��O
	//position		���W
	void Init(const wchar_t* modelName, CVector3 position);

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;
private:
	CSkinModel	m_skinModel;	//���f��
	CAnimation	m_animation;	//�A�j���[�V����
	CVector3	m_position;		//���W
	CQuaternion m_rotation;		//��]
};