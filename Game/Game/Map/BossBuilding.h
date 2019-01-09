/*
*	�{�X�����錚���̃N���X
*/

#pragma once

class CMessage;
class CChoices;

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
	CMessage*	m_message = nullptr;	//���b�Z�[�W
	CChoices*	m_choices = nullptr;	//�I����
	CSkinModel	m_skinModel;			//���f��
	CVector3	m_position;				//���W
	CQuaternion m_rotation;				//��]
	float		m_timer = 0.0f;			//�^�C�}�[
	bool		m_isChoice = false;		//�I�����Ă��邩
};