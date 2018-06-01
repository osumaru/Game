#pragma once
//�V�F�[�_�[(�G�t�F�N�g�t�@�C��)��ǂݍ��ރN���X

class Shader : Uncopyable
{
public:
	//�R���X�g���N�^
	Shader();

	//�f�X�g���N�^
	~Shader();

	enum EnShaderType
	{
		enVS,
		enPS,
		enCS,
	};

	/*
	�G�t�F�N�g�t�@�C����ǂݍ��ފ֐�
	filepath		�t�@�C���p�X
	entryFuncName	�֐��̖��O
	shaderType		�V�F�[�_�[�̎��
	*/
	void Load(const char* filepath, const char* entryFuncName, EnShaderType shaderType);

	//�V�F�[�_�[���擾
	ID3D11DeviceChild* GetBody()
	{
		return m_pShader;
	}

	//���_���C�A�E�g���擾
	ID3D11InputLayout* GetInputlayOut()
	{
		return m_pInputLayout;
	}
	void* GetByteCode()
	{
		return m_blob->GetBufferPointer();
	}
	size_t GetByteCodeSize()
	{
		return m_blob->GetBufferSize();
	}

private:

	//���_���C�A�E�g�����֐�
	void CreateInputLayout(ID3DBlob* blob);

private:
	std::unique_ptr<char[]>			m_pShaderData;		//�V�F�[�_�[���R���p�C�������f�[�^���i�[����o�b�t�@
	ID3D11DeviceChild*				m_pShader;			//�V�F�[�_�[
	ID3D11InputLayout*				m_pInputLayout;		//���_���C�A�E�g
	ID3DBlob*						m_blob;
};