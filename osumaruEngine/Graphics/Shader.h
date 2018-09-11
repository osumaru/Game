#pragma once
//�V�F�[�_�[(�G�t�F�N�g�t�@�C��)��ǂݍ��ރN���X


class CShader : Uncopyable
{
public:
	//�R���X�g���N�^
	CShader();

	//�f�X�g���N�^
	~CShader();

	//�V�F�[�_�[�̎��
	enum EnShaderType
	{
		enVS,		//���_�V�F�[�_�[
		enPS,		//�s�N�Z���V�F�[�_�[
		enCS,		//�R���s���[�g�V�F�[�_�[
	};

	/*
	�G�t�F�N�g�t�@�C����ǂݍ��ފ֐�
	filepath		�t�@�C���p�X
	entryFuncName	�֐��̖��O
	shaderType		�V�F�[�_�[�̎��
	*/
	void Load(const char* filepath, const char* entryFuncName, EnShaderType shaderType);

	//�V�F�[�_�[���擾
	ID3D11DeviceChild* GetBody()const
	{
		return m_pShader;
	}

	//���_���C�A�E�g���擾
	ID3D11InputLayout* GetInputlayOut() const
	{
		return m_pInputLayout;
	}

	//�V�F�[�_�[�f�[�^���擾
	void* GetByteCode()
	{
		return m_blob->GetBufferPointer();
	}
	//�V�F�[�_�[�f�[�^�̃T�C�Y���擾�B
	size_t GetByteCodeSize()
	{
		return m_blob->GetBufferSize();
	}

	//�z�b�g�����[�h�p�̊֐�
	void ReLoad();

	void EraseFlgFold()
	{
		m_isErase = false;
	}
private:
	ID3D11DeviceChild*				m_pShader;			//�V�F�[�_�[
	ID3D11InputLayout*				m_pInputLayout;		//���_���C�A�E�g
	ID3DBlob*						m_blob;				//�V�F�[�_�[�f�[�^
	const char*						m_filePath;
	const char*						m_entryFuncName;
	EnShaderType					m_shaderType;
	std::list<CShader*>::iterator	m_it;
	bool							m_isErase;
};