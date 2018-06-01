#pragma once
#include "SkinModelEffectFactory.h"
class Skelton;

class SkinModel
{
public:
	struct SkinModelCB
	{
		Matrix worldMat;
		Matrix viewMat;
		Matrix projMat;
	};

	SkinModel();


	void Create();

	void Draw(Matrix view, Matrix proj);

private:
	Skelton*						m_skelton;
	ID3D11Buffer*					m_structuredBuffer;
	ID3D11ShaderResourceView*		m_shaderResourceView;
	ConstantBuffer					constantBuffer;
	std::unique_ptr<DirectX::Model> m_skinModel;
};