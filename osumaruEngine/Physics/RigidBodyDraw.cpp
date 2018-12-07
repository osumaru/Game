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
	//���_��1���ŋ�m�o�b�t�@���쐬
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
	//���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�Ƀf�[�^��ǉ�
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
	//����������ĂȂ��ꍇ�͑������^�[������
	if (m_count == 0)
	{
		return;
	}
	//���_�o�b�t�@���X�V
	D3D11_MAPPED_SUBRESOURCE subresource;
	Engine().GetDeviceContext()->UpdateSubresource(m_primitive.GetVertexBuffer().Get(), 0, NULL, &m_vertexBuffer[0], 0, 0);
	//�C���f�b�N�X�o�b�t�@���X�V
	Engine().GetDeviceContext()->UpdateSubresource(m_primitive.GetIndexBuffer().Get(), 0, NULL, &m_indexBuffer[0], 0, 0);

	CMatrix mat;
	mat.Mul(viewMatrix, projectionMatrix);
	m_cb.Update(&mat);

	//�`��
	GetDeviceContext()->VSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->IASetInputLayout(m_vs.GetInputlayOut().Get());

	m_primitive.Draw(GetDeviceContext());
	Reset();
}