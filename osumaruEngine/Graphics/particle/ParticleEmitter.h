#pragma once
class CParticle;
class CCamera;

struct SParticleEmittInfo
{
	wchar_t*	filePath;			//テクスチャのファイルパス
	float width;				//パーティクルの横幅
	float height;				//パーティクルの縦幅
	CVector4 uv;				//テクスチャのuv座標。左上のuv、右下のuv
	CVector3 randomPosition;		//パーティクル座標のランダム幅
	CVector3 gravity;		//パーティクルの重力
	float	lifeTime;			//パーティクルの寿命
	float	emittIntervalTime;	//パーティクルが出るインターバルの時間
	float	emitterLifeTime;	//エミッターの寿命
	CVector3 emitterPosition;//エミッターの座標
	CVector3 moveSpeed;			//パーティクルの移動速度
	CVector3 randomMoveSpeed;	//パーティクルの移動速度のランダム幅
	int particleNum;			//同時に出るパーティクルの数
	bool isFirstTimeRandom;		//一番最初にパーティクル出すときだけ時間をずらすか
	EnAlphaBlendState alphaBlendState;//アルファブレンドのステート
};

//パーティクルエミッター
class CParticleEmitter : public IGameObject
{
public:
	//コンストラクタ
	CParticleEmitter();

	//デストラクタ
	~CParticleEmitter();

	/*
	エミッターの初期化
	info　パーティクルとエミッターの初期化情報
	camera	ビルボード処理に使うカメラ
	*/
	void Init(const SParticleEmittInfo& info, const CCamera* camera);

	//更新関数
	void Update()override;

	//座標を設定。
	void SetPosition(const CVector3& position)
	{
		m_info.emitterPosition = position;
	}

private:
	const CCamera*			m_pCamera;		//カメラ
	SParticleEmittInfo		m_info;			//パーティクルとエミッターの初期化情報
	float					m_lifeTimer;	//寿命
	float					m_intervalTime;	//パーティクルを出すインターバルタイム
	int						m_particleNum;	//1フレームに出るパーティクルの数
};