#pragma once
class CSkinModel;
//�V���h�E�}�b�v�N���X

class CShadowMap
{
public:
	//������
	void Init();

	//�V���h�E�}�b�v�ɕ`�悷�郂�f����o�^
	void AddModel(CSkinModel* model)
	{
		m_modelList.push_back(model);
	}

	//�`��
	void Draw();

	//�r���[�s���ݒ�
	void SetViewMatrix(CMatrix& viewMatrix)
	{
		m_viewMatrix = viewMatrix;
	}

	//�v���W�F�N�V�����s��
	void SetProjectionMatrix(CMatrix& projectionMatrix)
	{
		m_projectionMatrix = projectionMatrix;
	}

	//�r���[�s����擾
	CMatrix& GetViewMatrix()
	{
		return m_viewMatrix;
	}

	//�v���W�F�N�V�����s����擾
	CMatrix& GetProjMatrix()
	{
		return m_projectionMatrix;
	}

	//�����_�����O�^�[�Q�b�g���擾
	CRenderTarget& GetRenderTarget()
	{
		return m_renderTarget;
	}

	//�萔�o�b�t�@���Z�b�g
	void SetConstantBuffer();

	//�V���h�E�}�b�v�̃T�C�Y���擾
	static int GetShadowMapSize()
	{
		return SHADOW_MAP_SIZE;
	}

private:
	static const int						SHADOW_MAP_SIZE = 1024;		//�V���h�E�}�b�v�̃e�N�X�`���T�C�Y
	std::vector<CSkinModel*>				m_modelList;				//�V���h�E�}�b�v�ɕ`�悷�郂�f���̃��X�g
	CRenderTarget							m_renderTarget;				//�����_�����O�^�[�Q�b�g
	CMatrix									m_viewMatrix;				//�r���[�s��
	CMatrix									m_projectionMatrix;			//�v���W�F�N�V�����s��
	CConstantBuffer							m_CB;						//�萔�o�b�t�@
};