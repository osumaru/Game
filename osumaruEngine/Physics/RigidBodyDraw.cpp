#include "engineStdafx.h"
#include "RigidBodyDraw.h"
#include "../Engine.h"




CRigidBodyDraw::CRigidBodyDraw() :
	m_indexBuffer(NULL),
	m_vertexBuffer(NULL),
	m_primitive(),
	m_count(0)
{
}

CRigidBodyDraw::~CRigidBodyDraw()
{
	
	//m_primitive.Release();
}

void CRigidBodyDraw::Init()
{
	//頂点数1万で空ノバッファを作成
	const int vertexNum = 30000;
	SRigidBodyVSLayout vertexBuffer[vertexNum];
	DWORD indexBuffer[vertexNum];
	memset(vertexBuffer, 0, sizeof(vertexBuffer));
	memset(indexBuffer, 0, sizeof(indexBuffer));
	m_primitive.Create(vertexBuffer, sizeof(RigidBodyVSLayout), vertexNum, indexBuffer, vertexNum,  Primitive::enIndex32, Primitive::enTypeLineList);
	m_vs.Load("Assets/shader/rigidBodyDraw.fx", "VSMain", Shader::enVS);
	m_ps.Load("Assets/shader/rigidBodyDraw.fx", "PSMain", Shader::enPS);
	CMatrix mat = CMatrix::Identity;
	m_cb.Create(sizeof(CMatrix), &mat);
}

void CRigidBodyDraw::drawLine(const btVector3 &from, const btVector3 &to, const btVector3& color)
{
	//頂点バッファとインデックスバッファにデータを追加
	SRigidBodyVSLayout vertex;
	vertex.pos = { from.x(), from.y(), from.z(), 1.0f };
	vertex.color = {  color.x(), color.y(), color.z() };
	m_vertexBuffer.push_back(vertex);
	vertex.pos = { to.x(), to.y(), to.z(), 1.0f };
	vertex.color = { color.x(), color.y(), color.z() };
	m_vertexBuffer.push_back(vertex);
	m_indexBuffer.push_back(m_count * 2);
	m_indexBuffer.push_back(m_count * 2 + 1);
	m_count++;
}

void CRigidBodyDraw::Draw(CMatrix viewMatrix, CMatrix projectionMatrix)
{
	if (m_count == 0)
	{
		return;
	}
	//頂点バッファに書き込んでいく
	const int vertexNum = m_count * 2;
	ID3D11Buffer* vertexBuffer = m_primitive.GetVertexBuffer();
	D3D11_MAPPED_SUBRESOURCE subresource;
	Engine().GetDeviceContext()->UpdateSubresource(vertexBuffer, 0, NULL, &m_vertexBuffer[0], 0, 0);
	Engine().GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE, 0, &subresource);
	void* pData = subresource.pData;
	int count = 0;
	for (auto& list : m_vertexBuffer)
	{
		*((SRigidBodyVSLayout*)pData + count) = list;
		count++;
	}
	Engine().GetDeviceContext()->Unmap(vertexBuffer, 0);
	//インデックスバッファに書き込んでいく
	ID3D11Buffer* indexBuffer = m_primitive.GetIndexBuffer();

	Engine().GetDeviceContext()->UpdateSubresource(indexBuffer, 0, NULL, &m_indexBuffer[0], 0, 0);
	Engine().GetDeviceContext()->Map(indexBuffer, 0, D3D11_MAP_WRITE, 0, &subresource);
	pData = subresource.pData;
	count = 0;
	for (auto& list : m_indexBuffer)
	{
		*((DWORD*)pData + count) = list;
		count++;
	}
	Engine().GetDeviceContext()->Unmap(indexBuffer, 0);

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