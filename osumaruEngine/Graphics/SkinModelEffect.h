#pragma once
/*
�G�t�F�N�g�̋K��N���X
*/
class ISkinModelEffect : public DirectX::IEffect
{
public:
	//�R���X�g���N�^
	ISkinModelEffect()
	{

	}

	/*
	�V�F�[�_�[��K�p
	deviceContext	�f�o�C�X�R���e�L�X�g
	*/
	void __cdecl Apply(_In_ ID3D11DeviceContext* deviceContext)override;

	/*
	���_�V�F�[�_�[�̃f�[�^���擾
	pShaderByteCode		�f�[�^���i�[����|�C���^
	pByteCodeLength		�V�F�[�_�̃f�[�^�̃T�C�Y�����i�[����|�C���^
	*/
	void __cdecl GetVertexShaderBytecode(_Out_ void const** pShaderByteCode, _Out_ size_t* pByteCodeLength)override;

	/*
	�e�N�X�`����ݒ�
	texture	�e�N�X�`����SRV
	*/
	void SetTexture(ID3D11ShaderResourceView* texture)
	{
		textureResource = texture;
	}

protected:
	ID3D11ShaderResourceView*		textureResource;	//�e�N�X�`����SRV
	CConstantBuffer					constantBuffer;		//�萔�o�b�t�@
	CShader							vsShader;			//���_�V�F�[�_�[
	CShader							psShader;			//�s�N�Z���V�F�[�_�[
};

//�X�L���L�胂�f���̃G�t�F�N�g
class CSkinModelEffect : public ISkinModelEffect
{
public:
	//�R���X�g���N�^
	CSkinModelEffect();


private:
};

//�X�L���������f���̃G�t�F�N�g
class CNoSkinModelEffect : public ISkinModelEffect
{
public:
	//�R���X�g���N�^
	CNoSkinModelEffect();

private:
};
