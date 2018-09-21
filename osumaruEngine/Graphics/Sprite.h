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
		if(pTexture == nullptr)
		{
			return;
		}
		m_pTexture = pTexture;
	}

	/*
	スプライトの基底の座標を変更
	左上が(x,y) = (0.0f, 0.0f)
	右下が(x,y) = (1.0f, 1.0f)
	真ん中が(x, y) = (0.5f, 0.5f)
	*/
	void SetCenterPosition(CVector2 position)
	{
		m_centerPosition = position;
	}
	/*
	スプライトの回転の角度を設定
	angle	角度（ラジアン値）
	*/
	void SetRotationAngle(float angle)
	{
		m_angle = angle;
	}

	//描画するかのフラグを取得
	bool IsDraw() const
	{
		return m_isDraw;
	}

	//描画するかのフラグを設定
	void SetIsDraw(bool isDraw)
	{
		m_isDraw = isDraw;
	}

	/*
	スプライトのZ値を設定
	0.0fが一番手前で1.0fが最奥
	*/
	void SetDepthValue(float depthValue)
	{
		m_depthValue = depthValue;
	}
private:
	//頂点レイアウト
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	//定数バッファ
	struct SSpriteCB
	{
		CMatrix worldMat;	//ワールド行列
		float alpha;		//アルファ値
		float depthValue;	//Zの値
	};

	CTexture*						m_pTexture;			//テクスチャ
	CShader							m_vertexShader;		//頂点シェーダー
	CShader							m_pixelShader;		//ピクセルシェーダー
	CPrimitive						m_primitive;		//プリミティブ
	float							m_alpha;			//アルファ値
	float							m_angle;			//回転角度
	CVector2						m_position;			//スプライトのウィンドウ上での座標
	CVector2						m_centerPosition;	//スプライトの基点を表す座標
	CVector2						m_size;				//スプライトのサイズ
	CConstantBuffer					m_cb;				//定数バッファ
	bool							m_isDraw;			//描画するかどうか？
	float							m_depthValue;		//Zの値
};