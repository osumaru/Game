#include "WireDraw.h"
#include "../Camera/GameCamera.h"

void CWireDraw::Init(const CVector3& startPos, const CVector3& endPos, const CVector3& color)
{
	m_startPos = startPos;
	m_endPos = endPos;
	m_startPos = startPos;
	m_endPos = endPos;
	SVSLayout vertexBuffer[2];
	vertexBuffer[0].pos = { startPos.x, startPos.y, startPos.z, 1.0f };
	vertexBuffer[0].color = color;
	vertexBuffer[1].pos = { endPos.x, endPos.y, endPos.z, 1.0f };
	vertexBuffer[1].color = color;
	DWORD indexBuffer[2] = { 0, 1 };
	m_primitive.Create(vertexBuffer, sizeof(SVSLayout), 2, indexBuffer, 2, CPrimitive::enIndex32, CPrimitive::enTypeLineList);
	m_vs.Load("Assets/shader/rigidBodyDraw.fx", "VSMain", CShader::enVS);
	m_ps.Load("Assets/shader/rigidBodyDraw.fx", "PSMain", CShader::enPS);
	CMatrix mat = CMatrix::Identity;
	m_cb.Create(sizeof(CMatrix), &mat);
}

void CWireDraw::Update()
{
	SVSLayout vertexBuffer[2];
	vertexBuffer[0].pos = { m_startPos.x, m_startPos.y, m_startPos.z, 1.0f };
	vertexBuffer[0].color = m_color;
	vertexBuffer[1].pos = { m_endPos.x, m_endPos.y, m_endPos.z, 1.0f };
	vertexBuffer[1].color = m_color;
	DWORD indexBuffer[2] = { 0, 1 };
	m_primitive.Update(vertexBuffer, indexBuffer);
}

void CWireDraw::Draw()
{
	CMatrix mat;
	const CCamera& camera = GetGameCamera().GetCamera();
	mat.Mul(camera.GetViewMatrix(), camera.GetProjectionMatrix());
	m_cb.Update(&mat);

	//•`‰æ
	GetDeviceContext()->VSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody().Get(), nullptr, 0);
	ID3D11Buffer* vertexBuffers[] = { m_primitive.GetVertexBuffer().Get() };
	UINT strides[] = { m_primitive.GetVertexStride() };
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, vertexBuffers, strides, &offset);
	GetDeviceContext()->IASetPrimitiveTopology(m_primitive.GetPrimitiveType());
	GetDeviceContext()->IASetIndexBuffer(m_primitive.GetIndexBuffer().Get(), m_primitive.GetIndexFormat(), 0);
	GetDeviceContext()->IASetInputLayout(m_vs.GetInputlayOut().Get());
	GetDeviceContext()->DrawIndexed(m_primitive.GetIndexNum(), 0, 0);
}