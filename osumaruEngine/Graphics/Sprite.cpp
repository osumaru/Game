#include "engineStdafx.h"
#include "Sprite.h"
#include "../Engine.h"
#include "Texture.h"

CSprite::CSprite() :
	m_pTexture(nullptr),
	m_vertexShader(),
	m_pixelShader(),
	m_primitive(),
	m_alpha(1.0f),
	m_position(0.0f, 0.0f),
	m_size(FrameBufferWidth(), FrameBufferHeight())
{

}
CSprite::~CSprite()
{
}


void CSprite::Init(Texture* texture)
{
	m_pTexture = texture;
	m_vertexShader.Load("Assets/shader/sprite.fx", "VSMain", Shader::enVS);
	m_pixelShader.Load("Assets/shader/sprite.fx", "PSMain", Shader::enPS);
	SVSLayout vertexBufferLayout[4] = 
	{
		{ { -1.0f,  1.0f, 0.0f, 1.0f } , { 0.0f, 0.0f } },
		{ {  1.0f,  1.0f, 0.0f, 1.0f } , { 1.0f, 0.0f } },
		{ { -1.0f, -1.0f, 0.0f, 1.0f } , { 0.0f, 1.0f } },
		{ {  1.0f, -1.0f, 0.0f, 1.0f } , { 1.0f, 1.0f } },
	};
	DWORD indexBufferLayout[4] = {0, 2, 1, 3};
	SSpriteCB cb;
	cb.worldMat = CMatrix::Identity;
	cb.alpha = 1.0f;
	m_cb.Create(sizeof(SSpriteCB), &cb);
	m_primitive.Create(vertexBufferLayout, sizeof(SVSLayout), 4, indexBufferLayout, 4, CPrimitive::enIndex32, CPrimitive::enTypeTriangleStrip);

}

void CSprite::Draw()
{
	//���W�̃X�P�[����ϊ�
	CVector3 position;
	position.x = m_position.x / (FrameBufferWidth() / 2.0f);
	position.y = m_position.y / (FrameBufferHeight() / 2.0f);
	position.z = 0.0f;
	//�g��̃X�P�[����ϊ�
	CVector3 size;
	size.x = m_size.x / FrameBufferWidth();
	size.y = m_size.y / FrameBufferHeight();
	size.z = 1.0f;

	//�ړ��s����쐬
	CMatrix transform;
	transform.MakeTranslation(position);
	//�g��s����쐬
	CMatrix scale;
	scale.MakeScaling(size);
	//���[���h�s����쐬
	SSpriteCB cb;
	CMatrix worldMatrix = CMatrix::Identity;
	CQuaternion quat = CQuaternion::Identity;
	CMatrix rot;
	rot.MakeRotationFromQuaternion(quat);
	worldMatrix.Mul(worldMatrix, scale);
	worldMatrix.Mul(worldMatrix, rot);
	worldMatrix.Mul(worldMatrix, transform);
	worldMatrix.Transpose();
	cb.worldMat = worldMatrix;
	cb.alpha = m_alpha;
	m_cb.Update(&cb);
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vertexShader.GetBody(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_pixelShader.GetBody(), nullptr, 0);
	ID3D11Buffer* vertexBuffers[] = { m_primitive.GetVertexBuffer() };
	UINT strides[] = { m_primitive.GetVertexStride() };
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, vertexBuffers, strides, &offset);
	GetDeviceContext()->IASetPrimitiveTopology(m_primitive.GetPrimitiveType());
	GetDeviceContext()->IASetIndexBuffer(m_primitive.GetIndexBuffer(), m_primitive.GetIndexFormat(), 0);
	GetDeviceContext()->IASetInputLayout(m_vertexShader.GetInputlayOut());
	ID3D11Buffer* buffer = m_cb.GetBody();
	GetDeviceContext()->VSSetConstantBuffers(0, 1, &buffer);
	ID3D11ShaderResourceView* views[] = {m_pTexture->GetShaderResource()};
	GetDeviceContext()->PSSetShaderResources(0, 1, views);
	GetDeviceContext()->DrawIndexed(m_primitive.GetIndexNum(), 0, 0);
}