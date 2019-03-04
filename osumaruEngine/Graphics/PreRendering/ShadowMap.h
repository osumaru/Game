#pragma once
class CSkinModel;
//�V���h�E�}�b�v�N���X

class CShadowMap
{
public:
	//������
	void Init(float height);

	//�V���h�E�}�b�v�ɕ`�悷�郂�f����o�^
	void AddModel(CSkinModel* model)
	{
		m_modelList.push_back(model);
	}

	void Update();

	//�`��
	void Draw();


	//�r���[�s����擾
	CMatrix& GetViewMatrix(int index)
	{
		return m_viewMatrix[index];
	}

	//�v���W�F�N�V�����s����擾
	CMatrix& GetProjMatrix(int index)
	{
		return m_projectionMatrix[index];
	}

	//�����_�����O�^�[�Q�b�g���擾
	CRenderTarget& GetRenderTarget(int index)
	{
		return m_renderTarget[index];
	}

	//�萔�o�b�t�@���Z�b�g
	void SetConstantBuffer();

	//�V���h�E�}�b�v�̃T�C�Y���擾
	static int GetShadowMapSize()
	{
		return SHADOW_MAP_SIZE;
	}

	//���C�g�̒����_��ݒ�
	void SetLightCameraTarget(const CVector3& target)
	{
		m_target = target;
	}

	//���W��ݒ�
	void SetLightCameraUp(const CVector3& up)
	{
		m_up = up;
	}

	//�Q�[���Ŏg���Ă���J�����̐ݒ�
	void SetGameCamera(const CCamera* camera)
	{
		m_pCamera = camera;
		if (m_pCamera != nullptr)
		{
			m_isActive = true;
		}
		else
		{
			m_isActive = false;
		}
	}
	struct SShadowMapCB
	{
		CMatrix lightViewProj1;
		CMatrix lightViewProj2;
		CMatrix lightViewProj3;
	};
private:
	static const int			SHADOWMAP_NUM = 3;					//�V���h�E�}�b�v�̐�
	static const int			SHADOW_MAP_SIZE = 4096;				//�V���h�E�}�b�v�̃e�N�X�`���T�C�Y
	std::vector<CSkinModel*>	m_modelList;						//�V���h�E�}�b�v�ɕ`�悷�郂�f���̃��X�g
	CRenderTarget				m_renderTarget[SHADOWMAP_NUM];		//�����_�����O�^�[�Q�b�g
	CMatrix						m_viewMatrix[SHADOWMAP_NUM];		//�r���[�s��
	CMatrix						m_projectionMatrix[SHADOWMAP_NUM];	//�v���W�F�N�V�����s��
	CConstantBuffer				m_CB;								//�萔�o�b�t�@
	CConstantBuffer				m_shadowMapCB;						//�萔�o�b�t�@
	CVector3					m_target = CVector3::Down;			//���C�g�̕���
	CVector3					m_up = CVector3::Right;				//���C�g�̏����
	const CCamera*					m_pCamera;						//���C���̃J����
	bool						m_isActive = false;					//�A�N�e�B�u���H
	float						m_lightHeight;						//���C�g�J�����̍���
};