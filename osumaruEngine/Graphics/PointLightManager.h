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
	//初期化
	void Init();

	/*
	ポイントライトを追加
	pos		座標
	color	色
	*/
	void AddPointLight(CVector3 pos, CVector3 color);

	//更新処理
	void Update();

	//
	void Draw(CMatrix& view);

private:
	static const int MAX_POINTLIGHT_NUM = 512;
	SPointLight							m_pointLightList[MAX_POINTLIGHT_NUM];
	int									m_index = 0;
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_buffer;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_srv;
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>	m_uav;
};