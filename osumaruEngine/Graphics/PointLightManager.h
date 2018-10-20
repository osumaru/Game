#pragma once


struct SPointLight
{
	CVector4	m_position;
	CVector4	m_color;
};

class CPointLightManager
{
public:
	void Init();

	void AddPointLight(SPointLight pointLight);

	void Update();

	void Draw();

private:
	static const int MAX_POINTLIGHT_NUM = 512;
	SPointLight					m_pointLightList[MAX_POINTLIGHT_NUM];
	int							index = 0;
	ID3D11Buffer*				buffer;
	ID3D11ShaderResourceView*	srv;
};