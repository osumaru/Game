#pragma once
#include "SkinModelEffectFactory.h"
class Skelton;
class Animation;
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


	void Update(Vector3 position, Quaternion rotation, Vector3 scale);

	void Load(wchar_t* filePath);

	void Draw(Matrix view, Matrix proj);



private:

	Skelton*						m_skelton;
	ConstantBuffer					constantBuffer;
	std::unique_ptr<DirectX::Model> m_skinModel;
	bool isSkelton;
	Matrix							worldMatrix;
	Animation*						m_anim;
};