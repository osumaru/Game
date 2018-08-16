#pragma once
#include "SkinModelEffectFactory.h"
class Skelton;
class Animation;

class SkinModel : Uncopyable
{
public:
	struct SkinModelCB
	{
		Matrix worldMat;	
		Matrix viewMat;
		Matrix projMat;
	};

	SkinModel();

	~SkinModel();


	void Update(Vector3 position, Quaternion rotation, Vector3 scale);

	void Load(wchar_t* filePath);

	void Draw(Matrix view, Matrix proj);

	DirectX::Model* GetBody()
	{
		return m_skinModel.get();
	}

	Skelton* GetSkelton()
	{
		return m_skelton.get();
	}

private:

	std::unique_ptr<Skelton>		m_skelton;
	ConstantBuffer					constantBuffer;
	std::unique_ptr<DirectX::Model> m_skinModel;
	Matrix							worldMatrix;
	
};