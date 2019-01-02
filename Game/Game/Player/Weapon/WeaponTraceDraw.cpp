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
	m_primitive.Create(m_vertexBuffer, sizeof(SVSLayout), VERTEX_STRIDE_NUM * POLIGON_NUM, m_indexBuffer, INDEX_STRIDE_NUM * POLIGON_NUM, CPrimitive::enIndex32, CPrimitive::enTypeTriangleList);
	m_cb.Create(sizeof(CMatrix), &m_viewProj);
	int indexCount = 0;

	//頂点バッファとインデックスバッファを初期化
	for (int i = 0; i < POLIGON_NUM; i++)
	{
		//座標が被る箇所があるのでそれ用にアルファ値を2個用意
		float alpha[] = { (float)(POLIGON_NUM - i) / POLIGON_NUM,  (float)(POLIGON_NUM - i - 1) / POLIGON_NUM };
		DWORD vertexCount = i * VERTEX_STRIDE_NUM;
		DWORD index[INDEX_STRIDE_NUM] = { vertexCount, vertexCount + 1,  vertexCount + 2, vertexCount + 2,  vertexCount + 1,vertexCount + 3 };
		for (int j = 0; j < INDEX_STRIDE_NUM; j++)
		{
			m_indexBuffer[INDEX_STRIDE_NUM * i + j] = index[j];
		}
		CVector2 uv[VERTEX_STRIDE_NUM] = { { 1.0f, 1.0f }, { 1.0f, 0.0f },  { 0.0f, 1.0f }, { 0.0f, 0.0f } };
		int alphaIndex = 0;
		for (int j = 0; j < VERTEX_STRIDE_NUM; j++)
		{
			//後半の被ってる部分だけアルファ値を変える
			if (VERTEX_STRIDE_NUM / 2 == j)
			{
				alphaIndex++;
			}
			m_vertexBuffer[VERTEX_STRIDE_NUM * i + j].uv = uv[j];
			m_vertexBuffer[VERTEX_STRIDE_NUM * i + j].alpha = alpha[alphaIndex];
		}
	}

}

void CWeaponTraceDraw::Start(const CVector3& swordRootPosition, const CVector3& swordPointPosition)
{
	CVector4 position[VERTEX_STRIDE_NUM] = { swordRootPosition, swordPointPosition, swordRootPosition, swordPointPosition };
	for (int i = 0; i < POLIGON_NUM; i++)
	{
		for (int j = 0; j < VERTEX_STRIDE_NUM; j++)
		{
			m_vertexBuffer[i * VERTEX_STRIDE_NUM + j].position = position[j];
		}
	}
	m_rootPos = swordRootPosition;
	m_pointPos = swordPointPosition;

}

void CWeaponTraceDraw::Add(const CVector3& swordRootPosition, const CVector3& swordPointPosition)
{
	//座標を板ポリ一個分ずらす
	for (int i = POLIGON_NUM - 1; 0 < i; i--)
	{
		for(int j = 0;j < VERTEX_STRIDE_NUM;j++)
		{
			m_vertexBuffer[i * VERTEX_STRIDE_NUM + j].position = m_vertexBuffer[(i - 1) * VERTEX_STRIDE_NUM + j].position;
		}

	}
	//新しい座標を登録する
	CVector4 position[VERTEX_STRIDE_NUM] = { swordRootPosition, swordPointPosition, m_rootPos, m_pointPos, };
	for (int i = 0; i < VERTEX_STRIDE_NUM; i++)
	{
		m_vertexBuffer[i].position = position[i];
	}
	//座標2個を次でも使うために保存
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