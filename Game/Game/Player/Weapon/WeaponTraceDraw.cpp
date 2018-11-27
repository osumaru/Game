#include "WeaponTraceDraw.h"
#include "../../Camera/GameCamera.h"

void CWeaponTraceDraw::Init()
{
	m_viewProj = CMatrix::Identity;
	m_pTexture = TextureResource().LoadTexture(L"Assets/sprite/SwordTrace.png");
	m_vertexShader.Load("Assets/shader/weapon.fx", "VSMain", CShader::enVS);
	m_pixelShader.Load("Assets/shader/weapon.fx", "PSMain", CShader::enPS);
	ZeroMemory(m_vertexBuffer, sizeof(m_vertexBuffer));
	ZeroMemory(m_indexBuffer, sizeof(m_indexBuffer));
	m_primitive.Create(m_vertexBuffer, sizeof(SVSLayout), VERTEX_BUFFER_NUM, m_indexBuffer, INDEX_BUFFER_NUM, CPrimitive::enIndex32, CPrimitive::enTypeTriangleList);
	m_cb.Create(sizeof(CMatrix), &m_viewProj);

}

void CWeaponTraceDraw::Start()
{
	m_indexCount = 0;
	m_vertexCount = 0;
	ZeroMemory(m_vertexBuffer, sizeof(m_vertexBuffer));
	ZeroMemory(m_indexBuffer, sizeof(m_indexBuffer));
}

void CWeaponTraceDraw::Add(const CVector3& swordRootPosition, const CVector3& swordPointPosition)
{
	if (m_vertexCount == 0)
	{
		const int VERTEX_NUM = 2;
		CVector4 position[VERTEX_NUM] = { swordRootPosition, swordPointPosition };
		CVector2 uv[VERTEX_NUM] = { { 0.0f, 0.0f }, { 0.0f, 1.0f } };
		for (int i = 0; i < VERTEX_NUM; i++)
		{
			m_vertexBuffer[m_vertexCount].position = position[i];
			m_vertexBuffer[m_vertexCount].uv = uv[i];
			m_vertexCount++;
		}
	}
	else
	{
		const int VERTEX_NUM = 4;
		DWORD index[VERTEX_NUM] = { m_vertexCount, m_vertexCount + 1,  m_vertexCount + 2, m_vertexCount + 3 };
		CVector4 position[VERTEX_NUM] = { swordRootPosition, swordPointPosition, m_rootPos, m_pointPos, };
		CVector2 uv[VERTEX_NUM] = { { 1.0f, 1.0f }, { 1.0f, 0.0f },  { 0.0f, 1.0f }, { 0.0f, 0.0f } };
		m_indexBuffer[m_indexCount + 0] = index[0];
		m_indexBuffer[m_indexCount + 1] = index[1];
		m_indexBuffer[m_indexCount + 2] = index[2];
		m_indexBuffer[m_indexCount + 3] = index[2];
		m_indexBuffer[m_indexCount + 4] = index[1];
		m_indexBuffer[m_indexCount + 5] = index[3];
		m_indexCount += 6;
		for (int i = 0; i < VERTEX_NUM; i++)
		{
			m_vertexBuffer[m_vertexCount].position = position[i];
			m_vertexBuffer[m_vertexCount].uv = uv[i];
			m_vertexCount++;
		}
	}
	m_rootPos = swordRootPosition;
	m_pointPos = swordPointPosition;
	m_primitive.Update(m_vertexBuffer, m_indexBuffer);
}

void CWeaponTraceDraw::Draw()
{
	EnRasterizerState backupRasterizer = Engine().GetCurrentRasterizerState();
	Engine().SetRasterizerState(enRasterizerStateBoth);
	m_primitive.Update(m_vertexBuffer, m_indexBuffer);
	m_viewProj.Mul(GetGameCamera().GetViewMatrix(), GetGameCamera().GetProjectionMatrix());
	m_cb.Update(&m_viewProj);
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vertexShader.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_pixelShader.GetBody().Get(), nullptr, 0);
	ID3D11Buffer* vertexBuffers[] = { m_primitive.GetVertexBuffer().Get() };
	UINT strides[] = { m_primitive.GetVertexStride() };
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, vertexBuffers, strides, &offset);
	GetDeviceContext()->IASetPrimitiveTopology(m_primitive.GetPrimitiveType());
	GetDeviceContext()->IASetIndexBuffer(m_primitive.GetIndexBuffer().Get(), m_primitive.GetIndexFormat(), 0);
	GetDeviceContext()->IASetInputLayout(m_vertexShader.GetInputlayOut().Get());
	GetDeviceContext()->VSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	GetDeviceContext()->PSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	ID3D11ShaderResourceView* views[] = { m_pTexture->GetShaderResource().Get(), Engine().GetDeferred().GetShaderResource(enRenderTargetDepth).Get()
};
	GetDeviceContext()->PSSetShaderResources(0, 2, views);
	GetDeviceContext()->DrawIndexed(m_primitive.GetIndexNum(), 0, 0);
	Engine().SetRasterizerState(backupRasterizer);
}