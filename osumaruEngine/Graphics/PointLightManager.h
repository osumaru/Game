#pragma once


struct SPointLight
{
	CVector4	m_position;
	CVector4	m_color;
	CVector4    m_attn;
};

class CPointLightManager
{
public:
	void Init();

	void AddPointLight(CVector3 pos, CVector3 color);

	void Update();

	void Draw(CMatrix& view);

private:
	static const int MAX_POINTLIGHT_NUM = 512;
	SPointLight					m_pointLightList[MAX_POINTLIGHT_NUM];
	int							index = 0;
	ID3D11Buffer*				buffer;
	ID3D11ShaderResourceView*	srv;
	ID3D11UnorderedAccessView*	uav;
};