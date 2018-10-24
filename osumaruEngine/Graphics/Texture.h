#pragma once
//�e�N�X�`���N���X

class CTexture : Uncopyable
{
public:
	//�����_�����O�^�[�Q�b�g�̎��
	enum EnTextureType
	{
		enRendertarget,		//�����_�����O�^�[�Q�b�g
		enDepthStencil,		//�f�v�X�X�e���V���o�b�t�@
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
	ID3D11Texture2D* GetTexture() const
	{
		return (ID3D11Texture2D*)m_pTexture;
	}

	//�V�F�[�_�[���\�[�X�r���[���擾
	ID3D11ShaderResourceView* GetShaderResource() const
	{
		return m_pShaderResource;
	}

	ID3D11UnorderedAccessView* GetUnorderedAccessView()
	{
		return m_pUnorderedAccess;
	}

	//�e�N�X�`���̉������擾
	int GetWidth() const
	{
		return m_width;
	}

	//�e�N�X�`���̏c�����擾
	int GetHeight() const
	{
		return m_height;
	}

private:
	int								m_width;			//�e�N�X�`���̉���									
	int								m_height;			//�e�N�X�`���̏c��
	ID3D11Resource*					m_pTexture;			//�e�N�X�`��
	ID3D11ShaderResourceView*		m_pShaderResource;	//SRV
	ID3D11UnorderedAccessView*		m_pUnorderedAccess;	//UAV
};