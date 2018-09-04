#pragma once
//�e�N�X�`���N���X

class CTexture : Uncopyable
{
public:
	enum EnTextureType
	{
		enRendertarget,
		enDepthStencil,
	};
	//�R���X�g���N�^
	CTexture();

	//�f�X�g���N�^
	~CTexture();

	/*
	�e�N�X�`���̓ǂݍ��݊֐�
	filepath �e�N�X�`��������t�@�C���̃p�X
	*/
	void Load(const wchar_t* filepath);

	/*
	�e�N�X�`�������֐�
	*/
	void Create(int width, int height, EnTextureType textureType, DXGI_FORMAT format);

	//�e�N�X�`�����擾
	ID3D11Resource* GetTexture()
	{
		return m_pTexture;
	}

	//�V�F�[�_�[���\�[�X�r���[���擾
	ID3D11ShaderResourceView* GetShaderResource()
	{
		return m_pShaderResource;
	}

	//�e�N�X�`���̉������擾
	int GetWidth()
	{
		return m_width;
	}

	//�e�N�X�`���̏c�����擾
	int GetHeight()
	{
		return m_height;
	}

private:
	int m_width;
	int m_height;

	ID3D11Resource*					m_pTexture;
	ID3D11ShaderResourceView*		m_pShaderResource;
};