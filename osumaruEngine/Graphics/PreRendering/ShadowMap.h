#pragma once
class CSkinModel;
//シャドウマップクラス

class CShadowMap
{
public:
	//初期化
	void Init(float height);

	//シャドウマップに描画するモデルを登録
	void AddModel(CSkinModel* model)
	{
		m_modelList.push_back(model);
	}

	void Update();

	//描画
	void Draw();


	//ビュー行列を取得
	CMatrix& GetViewMatrix(int index)
	{
		return m_viewMatrix[index];
	}

	//プロジェクション行列を取得
	CMatrix& GetProjMatrix(int index)
	{
		return m_projectionMatrix[index];
	}

	//レンダリングターゲットを取得
	CRenderTarget& GetRenderTarget(int index)
	{
		return m_renderTarget[index];
	}

	//定数バッファをセット
	void SetConstantBuffer();

	//シャドウマップのサイズを取得
	static int GetShadowMapSize()
	{
		return SHADOW_MAP_SIZE;
	}

	//ライトの注視点を設定
	void SetLightCameraTarget(const CVector3& target)
	{
		m_target = target;
	}

	//座標を設定
	void SetLightCameraUp(const CVector3& up)
	{
		m_up = up;
	}

	//ゲームで使っているカメラの設定
	void SetGameCamera(const CCamera* camera)
	{
		m_pCamera = camera;
		if (m_pCamera != nullptr)
		{
			m_isActive = true;
		}
		else
		{
			m_isActive = false;
		}
	}
	struct SShadowMapCB
	{
		CMatrix lightViewProj1;
		CMatrix lightViewProj2;
		CMatrix lightViewProj3;
	};
private:
	static const int			SHADOWMAP_NUM = 3;					//シャドウマップの数
	static const int			SHADOW_MAP_SIZE = 4096;				//シャドウマップのテクスチャサイズ
	std::vector<CSkinModel*>	m_modelList;						//シャドウマップに描画するモデルのリスト
	CRenderTarget				m_renderTarget[SHADOWMAP_NUM];		//レンダリングターゲット
	CMatrix						m_viewMatrix[SHADOWMAP_NUM];		//ビュー行列
	CMatrix						m_projectionMatrix[SHADOWMAP_NUM];	//プロジェクション行列
	CConstantBuffer				m_CB;								//定数バッファ
	CConstantBuffer				m_shadowMapCB;						//定数バッファ
	CVector3					m_target = CVector3::Down;			//ライトの方向
	CVector3					m_up = CVector3::Right;				//ライトの上向き
	const CCamera*					m_pCamera;						//メインのカメラ
	bool						m_isActive = false;					//アクティブか？
	float						m_lightHeight;						//ライトカメラの高さ
};