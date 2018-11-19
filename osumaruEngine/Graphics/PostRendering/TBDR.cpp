#include "engineStdafx.h"
#include "TBDR.h"


void CTBDR::Init()
{
	m_cs.Load("Assets/shader/TBDR.fx", "CSMain", CShader::enCS);
	m_cb.Create(sizeof(SPointLightCB), nullptr);
}

void CTBDR::Draw()
{
	GetDeviceContext()->CSSetShader((ID3D11ComputeShader*)m_cs.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->CSSetConstantBuffers(0, 1, &m_cb.GetBody());
	//GetDeviceContext()->CSSetShaderResources();
	//GetDeviceContext()->Dispatch();

}