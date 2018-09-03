#pragma once
class CTexture;
#include "Shader.h"
#include "Primitive.h"
//スプライトクラス

class CSprite
{
public:
	//コンストラクタ
	CSprite();

	//デストラクタ
	~CSprite();

	/*
	初期化関数
	texture	スプライトに張り付けるテクスチャ
	*/
	void Init(CTexture* texture);

	//描画関数
	void Draw();

	//座標を設定
	void SetPosition(const CVector2& position)
	{
		m_position = position;
	}

	//座標を取得
	const CVector2& GetPosition() const
	{
		return m_position;
	}

	//サイズを設定
	void SetSize(const CVector2& size)
	{
		m_size = size;
	}

	//不透明度を設定
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	//サイズを取得
	const CVector2& GetSize() const
	{
		return m_size;
	}

	//テクスチャを設定
	void SetTexture(CTexture* pTexture)
	{
		if(pTexture != nullptr)
		{
			return;
		}
		m_pTexture = pTexture;
	}

private:
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	struct SSpriteCB
	{
		CMatrix worldMat;
		float alpha;
	};

	CTexture*						m_pTexture;
	CShader							m_vertexShader;
	CShader							m_pixelShader;
	CPrimitive						m_primitive;
	float							m_alpha;
	CVector2						m_position;			//スプライトのウィンドウ上での座標
	CVector2						m_centerPosition;	//スプライトの基点を表す座標
	CVector2						m_size;				//スプライトのサイズ
	CConstantBuffer					m_cb;
};