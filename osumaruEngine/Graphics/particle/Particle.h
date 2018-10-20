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

	//描画処理
	void AfterDraw()override;

private:
	CVector2		m_size;			//サイズ
	CTexture*		m_pTexture;		//テクスチャ
	CPrimitive		m_primitive;	//プリミティブ
	CMatrix			m_worldMatrix;	//ワールド行列
	CQuaternion		m_rotation;		//回転
	CShader			m_vs;			//頂点シェーダー
	CShader			m_ps;			//ピクセルシェーダー
	CConstantBuffer m_cb;
	CVector3		m_position;		//座標
	const CCamera*	m_camera;		//カメラ
	float			m_lifeTimer;	//寿命
	float			m_angle;		//回転量
	CVector3		m_gravity;		//重力
	CVector3		m_speed;		//速度
};