#pragma once
class CSkinModel;
//シャドウマップクラス

class CShadowMap
{
public:
	//初期化
	void Init();

	//シャドウマップに描画するモデルを登録
	void AddModel(CSkinModel* model)
	{
		m_modelList.push_back(model);
	}

	//描画
	void Draw();

	//ビュー行列を設定
	void SetViewMatrix(CMatrix& viewMatrix)
	{
		m_viewMatrix = viewMatrix;
	}

	//プロジェクション行列
	void SetProjectionMatrix(CMatrix& projectionMatrix)
	{
		m_projectionMatrix = projectionMatrix;
	}

	//ビュー行列を取得
	CMatrix& GetViewMatrix()
	{
		return m_viewMatrix;
	}

	//プロジェクション行列を取得
	CMatrix& GetProjMatrix()
	{
		return m_projectionMatrix;
	}

	//レンダリングターゲットを取得
	CRenderTarget& GetRenderTarget()
	{
		return m_renderTarget;
	}

	//定数バッファをセット
	void SetConstantBuffer();

	//シャドウマップのサイズを取得
	static int GetShadowMapSize()
	{
		return SHADOW_MAP_SIZE;
	}

private:
	static const int						SHADOW_MAP_SIZE = 1024;		//シャドウマップのテクスチャサイズ
	std::vector<CSkinModel*>				m_modelList;				//シャドウマップに描画するモデルのリスト
	CRenderTarget							m_renderTarget;				//レンダリングターゲット
	CMatrix									m_viewMatrix;				//ビュー行列
	CMatrix									m_projectionMatrix;			//プロジェクション行列
	CConstantBuffer							m_CB;						//定数バッファ
};