#pragma once
#include "../RenderTarget.h"
#include "../Texture.h"
#include "../Primitive.h"
#include "../Shader.h"
#include "../ConstantBuffer.h"

class CCamera;

enum EnRenderTarget
{
	enRenderTargetColor,
	enRenderTargetNormalMap,
	enRenderTargetNormal,
	enRenderTargetTangent,
	enRenderTargetDepth,
	enRenderTargetNum
};

class CDeferred : Uncopyable
{
public:
	//頂点レイアウト
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	//コンストラクタ
	CDeferred();

	//初期化関数
	void Init();

	//ディファード用のレンダリングターゲットに切り替える
	void Start();

	//描画関数
	void Draw();

	/*
	シェーダーリソースビューを取得
	numRenderTarget	レンダリングターゲットの番号
	*/
	ID3D11ShaderResourceView* GetShaderResource(EnRenderTarget numRenderTarget)
	{
		return m_renderTarget[numRenderTarget].GetRenderTargetTexture().GetShaderResource();
	}

	void SetViewMatrix(CMatrix& viewMatrix)
	{
		m_viewMatrix = viewMatrix;
	}

	void SetProjectionMatrix(CMatrix& projectionMatrix)
	{
		m_projectionMatrix = projectionMatrix;
	}

	CMatrix& GetViewMatrix()
	{
		return m_viewMatrix;
	}

	CMatrix& GetProjMatrix()
	{
		return m_projectionMatrix;
	}

	void SetConstantBuffer();

	void SetCamera(CCamera* camera);

private:
	CRenderTarget							m_renderTarget[enRenderTargetNum];	//Gバッファー
	CPrimitive								m_primitive;						//プリミティブ
	CShader									m_vertexShader;						//頂点シェーダー
	CShader									m_pixelShader;						//ピクセルシェーダー
	CConstantBuffer							m_lightCB;							//ライトの定数バッファ
	CMatrix									m_viewMatrix;						
	CMatrix									m_projectionMatrix;
	CConstantBuffer							m_shadowCB;
	CConstantBuffer							m_gameCameraCB;
	CCamera*								m_camera = nullptr;
};