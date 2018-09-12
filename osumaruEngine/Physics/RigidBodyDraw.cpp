#include "engineStdafx.h"
#include "RigidBodyDraw.h"
#include "../Engine.h"




CRigidBodyDraw::CRigidBodyDraw() :
	m_indexBuffer(),
	m_vertexBuffer(),
	m_primitive(),
	m_count(0)
{
}

CRigidBodyDraw::~CRigidBodyDraw()
{
	
}

void CRigidBodyDraw::Init()
{
	//頂点数1万で空ノバッファを作成
	memset(m_vertexBuffer, 0, sizeof(m_vertexBuffer));
	memset(m_indexBuffer, 0, sizeof(m_indexBuffer));
	m_primitive.Create(m_vertexBuffer, sizeof(SRigidBodyVSLayout), VERTEX_NUM, m_indexBuffer, VERTEX_NUM,  CPrimitive::enIndex32, CPrimitive::enTypeLineList);
	m_vs.Load("Assets/shader/rigidBodyDraw.fx", "VSMain", CShader::enVS);
	m_ps.Load("Assets/shader/rigidBodyDraw.fx", "PSMain", CShader::enPS);
	CMatrix mat = CMatrix::Identity;
	m_cb.Create(sizeof(CMatrix), &mat);
}

void CRigidBodyDraw::drawLine(const btVector3 &from, const btVector3 &to, const btVector3& color)
{
	if (VERTEX_NUM <= m_count * 2)
	{
		return;
	}
	//頂点バッファとインデックスバッファにデータを追加
	SRigidBodyVSLayout vertex;
	vertex.pos = { from.x(), from.y(), from.z(), 1.0f };
	vertex.color = {  color.x(), color.y(), color.z() };
	m_vertexBuffer[m_count * 2] = vertex;
	vertex.pos = { to.x(), to.y(), to.z(), 1.0f };
	vertex.color = { color.x(), color.y(), color.z() };
	m_vertexBuffer[m_count * 2 + 1] = vertex;
	m_indexBuffer[m_count * 2] = m_count * 2;
	m_indexBuffer[m_count * 2 + 1] = m_count * 2 + 1;
	m_count++;
}

void CRigidBodyDraw::Draw(CMatrix viewMatrix, CMatrix projectionMatrix)
{
	//何も書かれてない場合は早期リターンする
	if (m_count == 0)
	{
		return;
	}
	//頂点バッファを更新
	ID3D11Buffer* vertexBuffer = m_primitive.GetVertexBuffer();
	D3D11_MAPPED_SUBRESOURCE subresource;
	Engine().GetDeviceContext()->UpdateSubresource(vertexBuffer, 0, NULL, &m_vertexBuffer[0], 0, 0);
	//インデックスバッファを更新
	ID3D11Buffer* indexBuffer = m_primitive.GetIndexBuffer();
	Engine().GetDeviceContext()->UpdateSubresource(indexBuffer, 0, NULL, &m_indexBuffer[0], 0, 0);

	CMatrix mat;
	mat.Mul(viewMatrix, projectionMatrix);
	m_cb.Update(&mat);

	//描画
	ID3D11Buffer* buffer = m_cb.GetBody();
	GetDeviceContext()->VSSetConstantBuffers(0, 1, &buffer);
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody(), nullptr, 0);
	ID3D11Buffer* vertexBuffers[] = { m_primitive.GetVertexBuffer() };
	UINT strides[] = { m_primitive.GetVertexStride() };
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, vertexBuffers, strides, &offset);
	GetDeviceContext()->IASetPrimitiveTopology(m_primitive.GetPrimitiveType());
	GetDeviceContext()->IASetIndexBuffer(m_primitive.GetIndexBuffer(), m_primitive.GetIndexFormat(), 0);
	GetDeviceContext()->IASetInputLayout(m_vs.GetInputlayOut());
	GetDeviceContext()->DrawIndexed(m_primitive.GetIndexNum(), 0, 0);
	Reset();
}