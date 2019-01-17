#include "engineStdafx.h"
#include "Particle.h"
//#include "../Graphics/VertexCommon.h"
//#include "../Engine.h"
//#include "../Graphics/EffectManager.h"
//#include "../Physics/CharacterController.h"
#include "../../Camera/Camera.h"
#include "ParticleEmitter.h"
#include "../../Random/Random.h"
#include "../../Camera/Camera.h"

CParticle::CParticle() :
	m_size(1.0f, 1.0f),
	m_pTexture(nullptr),
	m_primitive(),
	m_worldMatrix{},
	m_rotation(0.0f, 0.0f, 0.0f, 1.0f),
	m_position(0.0f, 0.0f, 0.0f),
	m_camera(nullptr),
	m_lifeTimer(0.0f),
	m_angle(0.0f),
	m_gravity(0.0f, 0.0f, 0.0f),
	m_speed(0.0f, 0.0f, 0.0f)
{
}

CParticle::~CParticle()
{
}

void CParticle::Init(const SParticleEmittInfo& info, const CCamera* camera)
{
	m_vs.Load("Assets/shader/particle.fx", "VSMain", CShader::enVS);
	m_ps.Load("Assets/shader/particle.fx", "PSMain", CShader::enPS);
	m_gravity = info.gravity;
	m_camera = camera;
	m_position = info.emitterPosition;
	CVector3 addPos = info.randomPosition;
	addPos.x *= (float)Random().GetRandDouble() * 2.0f - 1.0f;
	addPos.y *= (float)Random().GetRandDouble() * 2.0f - 1.0f;
	addPos.z *= (float)Random().GetRandDouble() * 2.0f - 1.0f;
	m_position += addPos;
	m_speed = info.moveSpeed;
	CVector3 addSpeed;
	addSpeed = info.randomMoveSpeed;
	addSpeed.x *= (float)Random().GetRandDouble() * 2.0f - 1.0f;
	addSpeed.y *= (float)Random().GetRandDouble() * 2.0f - 1.0f;
	addSpeed.z *= (float)Random().GetRandDouble() * 2.0f - 1.0f;
	m_speed += addSpeed;
	m_lifeTimer = info.lifeTime;
	m_pTexture = TextureResource().LoadTexture(info.filePath);
	//頂点バッファを作成
	PVSLayout elements[4] =
	{
		{ {-1.0f,	1.0f,		1.0f,	1.0f},	{info.uv.x ,	info.uv.y} },
		{ {1.0f,	1.0f,		1.0f,	1.0f},	{info.uv.z ,	info.uv.y} },
		{ {1.0f,	-1.0f,		1.0f,	1.0f},	{info.uv.z ,	info.uv.w} },
		{ {-1.0f,	-1.0f,		1.0f,	1.0f},	{info.uv.x ,	info.uv.w} },
	};
	//インデックスバッファーを作成
	WORD indexElements[4] = { 0, 3, 1, 2 };
	//プリミティブを作成
	m_primitive.Create(elements, sizeof(PVSLayout), 4, indexElements, 6, CPrimitive::enIndex16, CPrimitive::enTypeTriangleStrip);
	m_worldMatrix = CMatrix::Identity;
	m_rotation = CQuaternion::Identity;
	m_cb.Create(sizeof(CMatrix), &m_worldMatrix);

	m_size.x = info.width;
	m_size.y = info.height;
}

void CParticle::Update()
{
	m_speed += m_gravity * GameTime().GetDeltaFrameTime();
	m_position += m_speed * GameTime().GetDeltaFrameTime();
	m_lifeTimer -= GameTime().GetDeltaFrameTime();
	if (m_lifeTimer < 0.0f)
	{
		Delete(this);
	}
	CQuaternion multi;
	multi.SetRotation(CVector3::AxisY, m_angle);
	m_rotation.Multiply(multi);
	CMatrix cameraRotMat;
	cameraRotMat = m_camera->GetViewMatrix();
	cameraRotMat.Inverse();
	cameraRotMat.m[3][0] = 0.0f;
	cameraRotMat.m[3][1] = 0.0f;
	cameraRotMat.m[3][2] = 0.0f;
	cameraRotMat.m[3][3] = 1.0f;
	CMatrix scaleMat;
	scaleMat.MakeScaling({ m_size.x, m_size.y, 1.0f });
	CMatrix rotationMat;
	rotationMat.MakeRotationFromQuaternion(m_rotation);
	CMatrix transMat;
	transMat.MakeTranslation({ m_position.x, m_position.y, m_position.z });
	m_worldMatrix = CMatrix::Identity;
	m_worldMatrix.Mul(m_worldMatrix, scaleMat);
	m_worldMatrix.Mul(m_worldMatrix, cameraRotMat);
	m_worldMatrix.Mul(m_worldMatrix, rotationMat);
	m_worldMatrix.Mul(m_worldMatrix, transMat);
}

void CParticle::AfterDraw()
{
	CMatrix worldViewProjMat = m_worldMatrix;

	worldViewProjMat.Mul(worldViewProjMat, m_camera->GetViewMatrix());
	worldViewProjMat.Mul(worldViewProjMat, m_camera->GetProjectionMatrix());
	m_cb.Update(&worldViewProjMat);
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody().Get(), nullptr, 0);
	ID3D11Buffer* vertexBuffers[] = { m_primitive.GetVertexBuffer().Get() };
	UINT strides[] = { m_primitive.GetVertexStride() };
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, vertexBuffers, strides, &offset);
	GetDeviceContext()->IASetPrimitiveTopology(m_primitive.GetPrimitiveType());
	GetDeviceContext()->IASetIndexBuffer(m_primitive.GetIndexBuffer().Get(), m_primitive.GetIndexFormat(), 0);
	GetDeviceContext()->IASetInputLayout(m_vs.GetInputlayOut().Get());
	GetDeviceContext()->VSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	GetDeviceContext()->PSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	ID3D11ShaderResourceView* views[] = { m_pTexture->GetShaderResource().Get(), Engine().GetShaderResource(enRenderTargetDepth).Get() };
	GetDeviceContext()->PSSetShaderResources(0, 2, views);
	GetDeviceContext()->DrawIndexed(m_primitive.GetIndexNum(), 0, 0);

}