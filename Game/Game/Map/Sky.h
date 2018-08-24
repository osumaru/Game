#pragma once
//��̃N���X

class Sky : public GameObject
{
public:

	//�R���X�g���N�^
	Sky();

	//�f�X�g���N�^
	~Sky();

	void Init(int stageNum);

	//�������֐�
	bool Start()override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;
private:

	SkinModel		m_skinModel;			//�X�L�����f��
	SkinModelData	m_skinModelData;		//�X�L�����f���f�[�^
	D3DXVECTOR3		m_position;				//���W
	D3DXQUATERNION	m_rotation;				//��]
	D3DXVECTOR3		m_scale;				//�g��
	Light			m_light;				//���f���̃��C�g
	int				m_stageNum;				//�X�e�[�W�̔ԍ�
};