#pragma once

//�G�t�F�N�g�t�@�N�g���[
class CSkinModelEffectFactory : public EffectFactory
{
public:
	//�R���X�g���N�^
	CSkinModelEffectFactory(_In_ ID3D11Device* device) :
		EffectFactory(device)
	{
	}
	/*
	�G�t�F�N�g�����֐�
	info	���f���Ȃǂ̏��
	*/
	std::shared_ptr<IEffect> __cdecl CreateEffect(_In_ const IEffectFactory::EffectInfo& info, _In_opt_ ID3D11DeviceContext* deviceContext)override;

	/*
	�e�N�X�`�������֐�
	name		�e�N�X�`���̃t�@�C����
	*/
	void __cdecl CreateTexture(_In_z_ const wchar_t* name, _In_opt_ ID3D11DeviceContext* deviceContext, _Outptr_ ID3D11ShaderResourceView** textureView)override;
private:
};