#include "engineStdafx.h"
#include "PointLightManager.h"


void CPointLightManager::Init()
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.StructureByteStride = sizeof(SPointLight);
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(D3D11_BUFFER_DESC) * MAX_POINTLIGHT_NUM;
	HRESULT hr = GetDevice()->CreateBuffer(&desc, nullptr, &buffer);
	hr = GetDevice()->CreateShaderResourceView(buffer, nullptr, &srv);
	ZeroMemory(m_pointLightList, sizeof(m_pointLightList));

}

void CPointLightManager::AddPointLight(CVector3 pos, CVector3 color)
{
	m_pointLightList[index].m_position = { pos.x, pos.y, pos.z, 1.0f };
	m_pointLightList[index].m_color = { color.x, color.y, color.z, 1.0f };
	m_pointLightList[index].m_attn = { 3.0f, 0.0f, 0.0f, 0.0f };
	index++;
}

void CPointLightManager::Update()
{
}

void CPointLightManager::Draw(CMatrix& view)
{
	SPointLight pointLightList[MAX_POINTLIGHT_NUM];
	memcpy(pointLightList, m_pointLightList, sizeof(m_pointLightList));
	for (int i = 0; i < index; i++)
	{
		pointLightList[i].m_position.Mul(view);
	}
	GetDeviceContext()->UpdateSubresource(buffer, 0, 0, pointLightList, 0, 0);
	
	ID3D11ShaderResourceView* srviews[] = { srv };
	GetDeviceContext()->VSSetShaderResources(10, 1, srviews);
	GetDeviceContext()->PSSetShaderResources(10, 1, srviews);
	GetDeviceContext()->CSSetShaderResources(5,  1, srviews);
}