#pragma once
class CTexture;
class CCamera;
#include "ParticleEmitter.h"

class CParticle : public IGameObject
{
public:
	//パーティクル用の頂点レイアウト
	struct PVSLayout
	{
		CVector4 pos;
		CVector2 uv;
	};
	//コンストラクタ
	CParticle();

	//デストラクタ
	~CParticle();

	/*
	パーティクルを初期化
	info	パーティクルの初期化情報
	camera	ビルボード処理に使うカメラ
	*/
	void Init(const SParticleEmittInfo& info, const CCamera* camera);

	//更新関数
	void Update()override;

	//ワールド行列の更新
	void UpdateWorldMatrix();

	//描画処理
	void AfterDraw()override;

	//座標を設定
	//position	座標
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}

	//アルファ値を設定
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

private:
	struct SParticleCB
	{
		CMatrix worldViewProj;		//ワールドビュープロジェクション行列
		float alpha;				//アルファ値
	};
	CVector2			m_size;			//サイズ
	CTexture*			m_pTexture;		//テクスチャ
	CPrimitive			m_primitive;	//プリミティブ
	CMatrix				m_worldMatrix;	//ワールド行列
	CQuaternion			m_rotation;		//回転
	CShader				m_vs;			//頂点シェーダー
	CShader				m_ps;			//ピクセルシェーダー
	CConstantBuffer		m_cb;
	CVector3			m_position;		//座標
	const CCamera*		m_camera;		//カメラ
	float				m_lifeTimer;	//寿命
	float				m_angle;		//回転量
	CVector3			m_gravity;		//重力
	CVector3			m_speed;		//速度
	float				m_alpha = 1.0f;	//アルファ値
	EnAlphaBlendState	m_alphaBlendState;	//アルファブレンドのステート
	float				m_fadeOutTime = 0.0f;	//フェードアウトする時間
	float				m_fadeOutTimer = 0.0f;	//フェードアウトする時間
};