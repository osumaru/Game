#include "WireDraw.h"
#include "../Camera/GameCamera.h"

void CWireDraw::Init(const CVector3& startPos, const CVector3& endPos, const CVector3& color)
{
	m_startPos = startPos;
	m_endPos = endPos;
	m_startPos = startPos;
	m_endPos = endPos;
	SVSLayout vertexBuffer[VERTEX_NUM];
	vertexBuffer[0].pos = { startPos.x, startPos.y, startPos.z, 1.0f };
	vertexBuffer[0].color = color;
	vertexBuffer[1].pos = { endPos.x, endPos.y, endPos.z, 1.0f };
	vertexBuffer[1].color = color;
	DWORD indexBuffer[VERTEX_NUM] = { 0, 1 };
	m_primitive.Create(vertexBuffer, sizeof(SVSLayout), VERTEX_NUM, indexBuffer, VERTEX_NUM, CPrimitive::enIndex32, CPrimitive::enTypeLineList);
	m_vs.Load("Assets/shader/line.fx", "VSMain", CShader::enVS);
	m_ps.Load("Assets/shader/line.fx", "PSMain", CShader::enPS);
	CMatrix mat = CMatrix::Identity;
	m_cb.Create(sizeof(CMatrix), &mat);
	m_color = color;
}

void CWireDraw::Update()
{
	CVector3 vertexPos[VERTEX_NUM] = { m_startPos, m_endPos };
	//プリミティブを更新
	SVSLayout vertexBuffer[VERTEX_NUM];
	for (int i = 0;i < VERTEX_NUM;i++)
	{
		vertexBuffer[i].pos = { vertexPos[i].x, vertexPos[i].y, vertexPos[i].z, 1.0f };
		vertexBuffer[i].color = m_color;
	}

	DWORD indexBuffer[VERTEX_NUM] = { 0, 1 };
	m_primitive.Update(vertexBuffer, indexBuffer);
}

void CWireDraw::Draw()
{
	CMatrix mat;
	const CCamera& camera = GetGameCamera().GetCamera();
	mat.Mul(camera.GetViewMatrix(), camera.GetProjectionMatrix());
	m_cb.Update(&mat);

	//描画
	GetDeviceContext()->VSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody().Get(), nullptr, 0);
	m_primitive.Draw(GetDeviceContext());
}