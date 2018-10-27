#include "engineStdafx.h"
#include "TBDR.h"


void CTBDR::Init()
{
	m_cs.Load("Assets/shader/TBDR.fx", "CSMain", CShader::enCS);
	m_cb.Create(sizeof(SPointLightCB), nullptr);
}

void CTBDR::Draw()
{
	GetDeviceContext()->CSSetShader((ID3D11ComputeShader*)m_cs.GetBody(), nullptr, 0);
	ID3D11Buffer* cb[] = {m_cb.GetBody()};
	GetDeviceContext()->CSSetConstantBuffers(0, 1, cb);
	//GetDeviceContext()->CSSetShaderResources();
	//GetDeviceContext()->Dispatch();

}