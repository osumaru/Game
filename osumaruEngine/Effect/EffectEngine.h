#pragma once
#include "Effect.h"
//エフェクトエンジン

class CEffectEngine : Uncopyable
{
public:
	//初期化
	void Init();

	//更新
	void Update();

	//描画
	void Draw();

	//エフェクト描画用のカメラを設定
	void SetCamera(const CCamera* camera)
	{
		m_pCamera = camera;
	}

	/*
	エフェクトを再生
	effect	再生するエフェクトのインスタンス
	
	*/
	Effekseer::Handle Play(CEffect& effect);

	//エフェクトマネージャーを取得
	Effekseer::Manager* GetEffectManager()
	{
		return m_manager;
	}
private:
	const CCamera*						m_pCamera = nullptr;	//描画に使うカメラ
	Effekseer::Manager*				m_manager = nullptr;	//マネージャー
	EffekseerRenderer::Renderer*	m_renderer = nullptr;	//レンダラー
};