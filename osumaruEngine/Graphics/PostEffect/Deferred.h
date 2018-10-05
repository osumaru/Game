#pragma once
#include "../RenderTarget.h"
#include "../Texture.h"
#include "../Primitive.h"
#include "../Shader.h"
#include "../ConstantBuffer.h"


class Deferred : Uncopyable
{
	enum EnRenderTarget
	{
		enRenderTargetColor,
		enRenderTargetNormalMap,
		enRenderTargetNormal,
		enRenderTargetTangent,
		enRenderTargetDepth,
		enRenderTargetNum
	};
public:
	//頂点レイアウト
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};
	//コンストラクタ
	Deferred();

	//初期化関数
	void Init();

	//ディファード用のレンダリングターゲットに切り替える
	void Start();

	//描画関数
	void Draw();
	
private:			//Gバッファーの数
	CRenderTarget							m_renderTarget[enRenderTargetNum];	//Gバッファー
	CPrimitive								m_primitive;						//プリミティブ
	CShader									m_vertexShader;						//頂点シェーダー
	CShader									m_pixelShader;						//ピクセルシェーダー
	CConstantBuffer							m_lightCB;							//ライトの定数バッファ
};