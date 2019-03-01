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
		CMatrix beforeWorldMat;				//ワールド行列
		CMatrix viewProjMat;			//ビュープロジェクション行列
		CMatrix beforeViewProjMat;
		float specularPower;			//スペキュラライトの強さ
		float diffuseLightPower;
		int alphaTestFlg;
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

	/*
	骨のローカル行列を更新
	boneID	骨の番号
	mat		ローカル行列
	*/
	void SetBoneMatrix(int boneID, const CMatrix& mat);

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

	const CLight& GetLight() const
	{
		return m_light;
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

	//ディフューズライトの強さを設定
	void SetDiffuseLightPower(float diffuseLightPower)
	{
		m_diffuseLightPower = diffuseLightPower;
	}

	//ディフューズライトの強さを取得
	float GetDiffuseLightPower() const
	{
		return m_diffuseLightPower;
	}
	
	//アルファテストするかどうかのフラグを設定
	void SetIsAlphaTest(bool isAlphaTest)
	{
		m_isAlphaTest = isAlphaTest;
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
	CMatrix							m_beforeWorldMatrix;
	CMatrix							m_beforeViewProj = CMatrix::Identity;	//1フレーム前のビュープロジェクション行列
	CTexture*						m_pNormalTexture = nullptr;
	CTexture*						m_pSpecularTexture = nullptr;
	SMaterialFlg					m_materialFlg;
	bool							m_isShadowCaster = false;
	float							m_specularPower = 0.0f;					//スペキュラライトの強さ
	float							m_diffuseLightPower = 1.0f;				//ディフューズライトの強さ
	bool							m_isAlphaTest = false;					//アルファテストするかどうかのフラグ
};