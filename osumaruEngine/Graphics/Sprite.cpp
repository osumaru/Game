#include "engineStdafx.h"
#include "Sprite.h"
#include "../Engine.h"
#include "Texture.h"
#include "../Math/Math.h"

CSprite::CSprite() :
	m_pTexture(nullptr),
	m_vertexShader(),
	m_pixelShader(),
	m_primitive(),
	m_alpha(1.0f),
	m_angle(0.0f),
	m_position(0.0f, 0.0f),
	m_centerPosition(0.5f, 0.5f),
	m_size(FrameBufferWidth(), FrameBufferHeight()),
	m_isDraw(true),
	m_depthValue(0.0f)
{
}
CSprite::~CSprite()
{
}


void CSprite::Init(CTexture* texture)
{
	m_pTexture = texture;
	//m_size.x = m_pTexture->GetWidth();
	//m_size.y = m_pTexture->GetHeight();
	m_vertexShader.Load("Assets/shader/sprite.fx", "VSMain", CShader::enVS);
	m_pixelShader.Load("Assets/shader/sprite.fx", "PSMain", CShader::enPS);
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
	cb.depthValue = m_depthValue;
	m_cb.Create(sizeof(SSpriteCB), &cb);
	m_primitive.Create(vertexBufferLayout, sizeof(SVSLayout), 4, indexBufferLayout, 4, CPrimitive::enIndex32, CPrimitive::enTypeTriangleStrip);

}

void CSprite::Draw()
{
	if (!m_isDraw)
	{
		return;
	}
	//���W�̃X�P�[����ϊ�
	CVector3 position;
	position.x = m_position.x / (FrameBufferWidth() / 2.0f);
	position.y = m_position.y / (FrameBufferHeight() / 2.0f);
	position.z = 0.0f;

	//�g��̃X�P�[����ϊ�
	CVector3 size;
	size.x = m_size.x / FrameBufferWidth() * (1.0f - m_depthValue);
	size.y = m_size.y / FrameBufferHeight() * (1.0f - m_depthValue);
	size.z = 1.0f;

	//�X�v���C�g�̊����W��ς��邽�߂̍s��
	CVector3 centerPos = CVector3::Zero;
	centerPos.x = m_centerPosition.x;
	centerPos.y = 1.0f - m_centerPosition.y;
	centerPos.x -= 0.5f;
	centerPos.y -= 0.5f;
	centerPos.x *= -2.0f;
	centerPos.y *= -2.0f;
	centerPos.x *= size.x;
	centerPos.y *= size.y;

	//�ړ��s����쐬
	CMatrix centerTrans;
	centerTrans.MakeTranslation(centerPos);
	CMatrix trans;
	trans.MakeTranslation(position);
	//�g��s����쐬
	CMatrix scale;
	scale.MakeScaling(size);

	//�X�N���[���̔䗦�ɃX�v���C�g���������΂����߂̍s��(��]�Ŏg��)
	CMatrix screenExtend;
	size.x = (float)FrameBufferWidth() / (float)FrameBufferHeight();
	size.y = 1.0f;
	screenExtend.MakeScaling(size);

	//1.0�`0.0�̊Ԃɏk�߂�
	CMatrix screenShrink;
	size.x = (float)FrameBufferHeight() / (float)FrameBufferWidth();
	size.y = 1.0f;
	screenShrink.MakeScaling(size);

	//��]�s����쐬
	CQuaternion quat;
	quat.SetRotation({0.0f, 0.0f, -1.0f}, m_angle);
	CMatrix rot;
	rot.MakeRotationFromQuaternion(quat);

	//���[���h�s����쐬
	CMatrix worldMatrix = CMatrix::Identity;
	worldMatrix.Mul(worldMatrix, scale);
	worldMatrix.Mul(worldMatrix, centerTrans);
	worldMatrix.Mul(worldMatrix, screenExtend);
	worldMatrix.Mul(worldMatrix, rot);
	worldMatrix.Mul(worldMatrix, screenShrink);
	worldMatrix.Mul(worldMatrix, trans);
	//�萔�o�b�t�@���X�V
	SSpriteCB cb;
	cb.worldMat = worldMatrix;
	cb.alpha = m_alpha;
	cb.depthValue = m_depthValue;
	m_cb.Update(&cb);
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vertexShader.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_pixelShader.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->IASetInputLayout(m_vertexShader.GetInputlayOut().Get());
	GetDeviceContext()->VSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	GetDeviceContext()->PSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	ID3D11ShaderResourceView* views[] = {m_pTexture->GetShaderResource().Get()};
	GetDeviceContext()->PSSetShaderResources(0, 1, views);
	ID3D11Buffer* vertexBuffers[] = { m_primitive.GetVertexBuffer().Get() };
	UINT strides[] = { m_primitive.GetVertexStride() };
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, vertexBuffers, strides, &offset);
	GetDeviceContext()->IASetPrimitiveTopology(m_primitive.GetPrimitiveType());
	GetDeviceContext()->IASetIndexBuffer(m_primitive.GetIndexBuffer().Get(), m_primitive.GetIndexFormat(), 0);

	GetDeviceContext()->DrawIndexed(m_primitive.GetIndexNum(), 0, 0);
	//m_primitive.Draw(GetDeviceContext());
}