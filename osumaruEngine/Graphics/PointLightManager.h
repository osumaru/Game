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
	//������
	void Init();

	/*
	�|�C���g���C�g��ǉ�
	pos		���W
	color	�F
	*/
	void AddPointLight(CVector3 pos, CVector3 color);

	//�X�V����
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