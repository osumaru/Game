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

	m_rotation = CQuaternion::Identity;
	m_cb.Create(sizeof(SParticleCB), nullptr);

	m_size.x = info.width;
	m_size.y = info.height;
	m_alphaBlendState = info.alphaBlendState;
	m_fadeOutTime = info.fadeOutTime;
}

void CParticle::Update()
{
	m_speed += m_gravity * GameTime().GetDeltaFrameTime();
	m_position += m_speed * GameTime().GetDeltaFrameTime();
	if (0.0f <= m_lifeTimer)
	{
		m_lifeTimer -= GameTime().GetDeltaFrameTime();
	}
	if (m_lifeTimer < 0.0f)
	{
		if (m_fadeOutTimer < m_fadeOutTime)
		{
			m_alpha = (m_fadeOutTime - m_fadeOutTimer) / m_fadeOutTime;
			m_fadeOutTimer += GameTime().GetDeltaFrameTime();
		}
		else
		{
			Delete(this);
		}
	}
	CQuaternion multi;
	multi.SetRotation(CVector3::AxisY, m_angle);
	m_rotation.Multiply(multi);
	UpdateWorldMatrix();
}

void CParticle::UpdateWorldMatrix()
{

	CMatrix cameraRotMat;
	cameraRotMat = m_camera->GetViewMatrix();
	cameraRotMat.Inverse();
	cameraRotMat.m[3][0] = 0.0f;
	cameraRotMat.m[3][1] = 0.0f;
	cameraRotMat.m[3][2] = 0.0f;
	cameraRotMat.m[3][3] = 1.0f;
	CMatrix scaleMat;
	scaleMat.MakeScaling({ m_size.x, m_size.y, 0.0f });
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
	EnAlphaBlendState backupBlend = Engine().GetCurrentAlphaBlendState();
	Engine().SetAlphaBlendState(m_alphaBlendState);
	EnDepthStencilState backupDepth = Engine().GetCurrentDepthStencilState();
	Engine().SetDepthStencilState(enDepthStencilParticle);

	SParticleCB particleCB;
	particleCB.worldViewProj = m_worldMatrix;

	particleCB.worldViewProj.Mul(particleCB.worldViewProj, m_camera->GetViewMatrix());
	particleCB.worldViewProj.Mul(particleCB.worldViewProj, m_camera->GetProjectionMatrix());
	particleCB.alpha = m_alpha;
	m_cb.Update(&particleCB);
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody().Get(), nullptr, 0);

	GetDeviceContext()->IASetInputLayout(m_vs.GetInputlayOut().Get());

	GetDeviceContext()->VSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	GetDeviceContext()->PSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	ID3D11ShaderResourceView* views[] = { m_pTexture->GetShaderResource().Get(), Engine().GetShaderResource(enRenderTargetDepth).Get() };
	GetDeviceContext()->PSSetShaderResources(0, 2, views);
	m_primitive.Draw(GetDeviceContext());

	Engine().SetAlphaBlendState(backupBlend);
	Engine().SetDepthStencilState(backupDepth);
}