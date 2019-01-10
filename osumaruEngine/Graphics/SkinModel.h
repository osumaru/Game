#pragma once
#include "SkinModelEffectFactory.h"
#include "SkinModelShaderFlgCommon.h"
#include "Light.h"
class CSkelton;
class CAnimation;
//スキンモデルクラス

class CSkinModel : Uncopyable
{
public:
	//定数バッファ用の構造体
	struct SSkinModelCB
	{
		CMatrix worldMat;				//ワールド行列
		CMatrix viewProjMat;			//ビュープロジェクション行列
		float specularPower;			//スペキュラライトの強さ
	};

	//コンストラクタ
	CSkinModel();

	//デストラクタ
	~CSkinModel();

	/*
	ワールド行列を更新
	position	座標
	rotation	回転
	scale		拡大
	isZup		Zアップで吐き出したモデルはtrue,Yアップで吐き出した場合はfalse
	*/
	void Update(const CVector3& position, const CQuaternion& rotation, const CVector3& scale, bool isZup = false);

	/*
	モデルの読み込み
	filePath	モデルのファイルパス
	animation	アニメーションが有るモデルならアニメーションのインスタンス
	*/
	void Load(const wchar_t* filePath, CAnimation* animation = nullptr);

	/*
	描画関数
	view	ビュー行列
	proj	プロジェクション行列
	*/
	void Draw(const CMatrix& view, const CMatrix& proj, bool isShadow = false);


	//モデルを取得
	DirectX::Model* GetBody() const
	{
		return m_skinModel;
	}

	//スケルトンを取得
	const CSkelton* GetSkelton() const
	{
		return m_skelton.get();
	}

	//ワールド行列の取得
	const CMatrix& GetWorldMatrix() const
	{
		return m_worldMatrix;
	}

	/*
	骨のワールド行列を取得
	boneName	探す骨の名前
	ret			見つかった骨のワールド行列を返す、見つからなかったら単位行列を返す
	*/
	const CMatrix& FindBoneWorldMatrix(const wchar_t* boneName) const;

	//ライトの設定
	void SetLight(const CLight& light)
	{
		m_light = light;
	}
	/*
	法線マップの読み込み

	*/
	void LoadNormalmap(const wchar_t* filePath);

	/*
	スペキュラマップの読み込み

	*/
	void LoadSpecularMap(const wchar_t* filePath);

	//スペキュラライトの強さを設定
	void SetSpecularPower(float specPower)
	{
		m_specularPower = specPower;
	}
	
	/*
	シャドウマップへ書き込むモデルとして登録
	*/
	void ShadowMapEntry();

	//シャドウを落とすかのフラグを設定
	void SetIsShadowReceiver(bool isShadowReceiver)
	{
		m_materialFlg.isShadowReceiver = g_materialFlg.isShadowReceiver * isShadowReceiver;
	}

	//シャドウマップに書き込むモデル化のフラグを設定
	void SetIsShadowCaster(bool isShadowCaster)
	{
		m_isShadowCaster = isShadowCaster;
	}

	//ディフューズライトを当てるかの設定
	void SetIsDiffuse(bool isDiffuse)
	{
		m_materialFlg.isDiffuse = g_materialFlg.isDiffuse * isDiffuse;
	}
	

private:
	std::unique_ptr<CSkelton>		m_skelton = nullptr;				//スケルトン
	CConstantBuffer					m_cb;						//定数バッファ
	CConstantBuffer					m_lightCB;							//ライトのバッファ
	CConstantBuffer					m_materialCB;
	CLight							m_light;							//ライト
	DirectX::Model*					m_skinModel = nullptr;				//スキンモデル
	CMatrix							m_worldMatrixZUp = CMatrix::Identity;	//ZUpのワールド行列
	CMatrix							m_worldMatrix = CMatrix::Identity;	//ワールド行列
	CTexture*						m_pNormalTexture = nullptr;
	CTexture*						m_pSpecularTexture = nullptr;
	SMaterialFlg					m_materialFlg;
	bool							m_isShadowCaster = false;
	float							m_specularPower = 0.0f;					//スペキュラライトの強さ

};