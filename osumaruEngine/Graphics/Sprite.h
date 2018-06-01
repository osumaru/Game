#pragma once
class Texture;
#include "Shader.h"
#include "Primitive.h"
//スプライトクラス

class Sprite
{
public:
	//コンストラクタ
	Sprite();

	//デストラクタ
	~Sprite();

	/*
	初期化関数
	texture	スプライトに張り付けるテクスチャ
	*/
	void Init(Texture* texture);

	//描画関数
	void Draw();

	//座標を設定
	void SetPosition(const Vector2& position)
	{
		m_position = position;
	}

	//座標を取得
	const Vector2& GetPosition() const
	{
		return m_position;
	}

	//サイズを設定
	void SetSize(const Vector2& size)
	{
		m_size = size;
	}

	//不透明度を設定
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	//サイズを取得
	const Vector2& GetSize() const
	{
		return m_size;
	}

	//テクスチャを設定
	void SetTexture(Texture* pTexture)
	{
		if(pTexture != nullptr)
		{
			return;
		}
		m_pTexture = pTexture;
	}

private:
	struct VSLayout
	{
		Vector4 position;
		Vector2	uv;
	};

	struct SpriteCB
	{
		Matrix worldMat;
		float alpha;
	};

	Texture*						m_pTexture;
	Shader							m_vertexShader;
	Shader							m_pixelShader;
	Primitive						m_primitive;
	float							m_alpha;
	Vector2							m_position;			//スプライトのウィンドウ上での座標
	Vector2							m_centerPosition;	//スプライトの基点を表す座標
	Vector2							m_size;				//スプライトのサイズ
	ConstantBuffer					m_cb;
};