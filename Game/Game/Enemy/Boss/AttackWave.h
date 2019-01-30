/*
*	ボスの攻撃で発生する波クラス
*/

#pragma once

class CCamera;

class CAttackWave : public IGameObject
{
public:
	//初期化
	//camera	カメラ
	//position	座標
	void Init(const CCamera* camera, const CVector3& position);

	//更新
	void Update() override;

	//描画
	void AfterDraw() override;
private:
	//頂点レイアウト
	struct SLayout
	{
		CVector4 position;
		CVector2 uv;
	};

	struct SConstantBuffer
	{
		CMatrix worldViewProj;		//ワールドビュープロジェクション行列
		float alpha;				//アルファ値
	};

	const CCamera*		m_camera = nullptr;	//カメラ
	CShader				m_vs;				//頂点シェーダー
	CShader				m_ps;				//ピクセルシェーダー
	CConstantBuffer		m_cb;				//コンスタントバッファ
	CPrimitive			m_primitive;		//プリミティブ
	CTexture*			m_texture;			//テクスチャ
	CVector2			m_size;				//サイズ
	CMatrix				m_worldMatrix;		//ワールド行列
	CVector3			m_position;			//座標
	CQuaternion			m_rotation;			//回転
	float				m_alpha = 1.0f;		//アルファ値
	float				m_lifeTimer = 0.0f;	//寿命
	float				m_waveHitLength = 1.0f; //波が当たる距離
};