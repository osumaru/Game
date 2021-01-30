#include "engineStdafx.h"
#include "ShadowMap.h"
#include "../../Graphics/SkinModel.h"
#include "../PostRendering/Deferred.h"
#include "../../Engine.h"
#include "../../Camera/Camera.h"

void CShadowMap::Init(float height)
{
	for (int i = 0; i < SHADOWMAP_NUM; i++)
	{

		m_renderTarget[i].CreateRenderTarget(SHADOW_MAP_SIZE >> i , SHADOW_MAP_SIZE >> i, DXGI_FORMAT_R32G32B32A32_FLOAT);
		m_renderTarget[i].CreateDepthStencilBuffer(SHADOW_MAP_SIZE >> i, SHADOW_MAP_SIZE >> i);
	}

	m_CB.Create(sizeof(SShadowMapCB), nullptr);
	m_shadowMapCB.Create(sizeof(CMatrix), nullptr);
	m_lightHeight = height;
}

void CShadowMap::SetConstantBuffer()
{
	SShadowMapCB shadowMapCB;
	CMatrix* viewProjMatrix[] = {
		&shadowMapCB.lightViewProj1,
		&shadowMapCB.lightViewProj2,
		&shadowMapCB.lightViewProj3,
	};
	for (int i = 0; i < SHADOWMAP_NUM; i++)
	{
		viewProjMatrix[i]->Mul(m_viewMatrix[i], m_projectionMatrix[i]);
	}

	m_CB.Update(&shadowMapCB);
	GetDeviceContext()->PSSetConstantBuffers(2, 1, m_CB.GetBody().GetAddressOf());
	GetDeviceContext()->VSSetConstantBuffers(2, 1, m_CB.GetBody().GetAddressOf());
}

void CShadowMap::Update()
{
	if (!m_isActive)
	{
		return;
	}
	//ライトカメラの回転行列を計算
	CVector3 lightCameraForward = m_target;
	CVector3 lightCameraUp = m_up;
	lightCameraForward.Normalize();
	lightCameraUp.Normalize();

	CVector3 lightCameraRight;
	lightCameraRight.Cross(lightCameraUp, lightCameraForward);
	lightCameraRight.Normalize();
	lightCameraUp.Cross(lightCameraForward, lightCameraRight);
	lightCameraUp.Normalize();
	CMatrix lightCameraRot;
	lightCameraRot.m[0][0] = lightCameraRight.x;
	lightCameraRot.m[0][1] = lightCameraRight.y;
	lightCameraRot.m[0][2] = lightCameraRight.z;
	lightCameraRot.m[0][3] = 0.0f;
	lightCameraRot.m[1][0] = lightCameraUp.x;
	lightCameraRot.m[1][1] = lightCameraUp.y;
	lightCameraRot.m[1][2] = lightCameraUp.z;
	lightCameraRot.m[1][3] = 0.0f;
	lightCameraRot.m[2][0] = lightCameraForward.x;
	lightCameraRot.m[2][1] = lightCameraForward.y;
	lightCameraRot.m[2][2] = lightCameraForward.z;
	lightCameraRot.m[2][3] = 0.0f;
	float _near = 0.0f;
	float _far;
	float ZLength = 150.0f;
	float shadowAreaTable[SHADOWMAP_NUM] =
	{
		10.0f,
		40.0f,
		300.0f
	};
	//メインカメラの前方向と上方向と右方向を求める
	CVector3 cameraForward = m_pCamera->GetTarget() - m_pCamera->GetPosition();
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	CVector3 cameraUp = m_pCamera->GetUp();
	CVector3 cameraRight;
	cameraRight.Cross(cameraUp, cameraForward);
	cameraUp.Cross(cameraForward, cameraRight);
	cameraUp.Normalize();
	cameraRight.Normalize();
	float halfAngle = m_pCamera->GetAngle() * 0.5f;
	float _aspect = m_pCamera->GetAspect();
	//メインカメラの近平面と遠平面の8個の頂点の座標を求める
	for (int i = 0; i < SHADOWMAP_NUM; i++)
	{
		float t = tan(halfAngle);
		_far = shadowAreaTable[i] + _near;
		CVector3 cameraCenter = m_pCamera->GetPosition() + cameraForward * _near;
		CVector3 lightPos = cameraCenter;
		CVector3 cameraUpNear = cameraUp * t * _near;
		CVector3 cameraUpFar = cameraUp * t * _far;
		t *= _aspect;
		CVector3 cameraRightNear = cameraRight * t * _near;
		CVector3 cameraRightFar = cameraRight * t * _far;
		const int VERTEX_NUM = 8;
		CVector3 aabbVertex[VERTEX_NUM];
		aabbVertex[0] = cameraCenter + cameraUpNear + cameraRightNear;
		aabbVertex[1] = cameraCenter + cameraUpNear - cameraRightNear;
		aabbVertex[2] = cameraCenter - cameraUpNear + cameraRightNear;
		aabbVertex[3] = cameraCenter - cameraUpNear - cameraRightNear;
		cameraCenter = m_pCamera->GetPosition() + cameraForward * _far;
		lightPos += cameraCenter;
		lightPos *= 0.5f;
		aabbVertex[4] = cameraCenter + cameraUpFar + cameraRightFar;
		aabbVertex[5] = cameraCenter + cameraUpFar - cameraRightFar;
		aabbVertex[6] = cameraCenter - cameraUpFar + cameraRightFar;
		aabbVertex[7] = cameraCenter - cameraUpFar - cameraRightFar;
		CMatrix lightView = lightCameraRot;
		CVector3 lightPosDir = m_target;
		lightPosDir.Normalize();
		lightPos -= lightPosDir * m_lightHeight;
		//lightPos.y += m_lightHeight;
		lightView.m[3][0] = lightPos.x;
		lightView.m[3][1] = lightPos.y;
		lightView.m[3][2] = lightPos.z;
		lightView.m[3][3] = 1.0f;
		lightView.Inverse();
		CVector3 aabbMin = { FLT_MAX, FLT_MAX, FLT_MAX };
		CVector3 aabbMax = { -FLT_MAX, -FLT_MAX, -FLT_MAX };
		//8個の頂点をライト用のカメラのビュー行列をかけてAABBをもとめライトカメラの写す範囲を決定
		for (int i = 0; i < VERTEX_NUM; i++)
		{
			aabbVertex[i].Mul(lightView);
			aabbMax.Max(aabbVertex[i]);
			aabbMin.Min(aabbVertex[i]);
		}
		CVector3 lightTarget = lightPos + lightCameraForward;
		float w = aabbMax.x - aabbMin.x;//ちょっと太らせる
		float h = aabbMax.y - aabbMin.y;
		m_viewMatrix[i].MakeLookAt(lightPos, lightTarget, lightCameraUp);
		m_projectionMatrix[i].MakeOrthoProjectionMatrix(w, h, 10.0f, 1000.0f);
		_near = _far;
	}
}

void CShadowMap::Draw()
{
	Engine().SetAlphaBlendState(enAlphaBlendStateNone);
	Engine().SetDepthStencilState(enDepthStencilState3D);
	EnViewPortState viewPortState[3] = {
		enViewPortShadow1,
		enViewPortShadow2,
		enViewPortShadow3,
	};
	for (int i = 0; i < SHADOWMAP_NUM; i++)
	{
		ID3D11RenderTargetView* rtv[] = { m_renderTarget[i].GetRenderTarget().Get() };
		Engine().GetDeviceContext()->OMSetRenderTargets(1, rtv, m_renderTarget[i].GetDepthStencil().Get());
		float color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		Engine().GetDeviceContext()->ClearRenderTargetView(m_renderTarget[i].GetRenderTarget().Get(), color);
		Engine().GetDeviceContext()->ClearDepthStencilView(m_renderTarget[i].GetDepthStencil().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		CMatrix viewMat = m_viewMatrix[i];
		CMatrix projMat = m_projectionMatrix[i];
		Engine().SetViewPortState(viewPortState[i]);
		CMatrix lightViewProj;
		lightViewProj.Mul(m_viewMatrix[i], m_projectionMatrix[i]);
		m_shadowMapCB.Update(&lightViewProj);
		GetDeviceContext()->PSSetConstantBuffers(2, 1, m_shadowMapCB.GetBody().GetAddressOf());
		GetDeviceContext()->VSSetConstantBuffers(2, 1, m_shadowMapCB.GetBody().GetAddressOf());
		for (auto& model : m_modelList)
		{
			model->Draw(viewMat, projMat, true);
		}
	}
	m_modelList.clear();
	Engine().SetViewPortState(enViewPortGame);
}

