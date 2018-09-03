#pragma once
#include "SkinModelEffectFactory.h"
class CSkelton;
class CAnimation;
//スキンモデルクラス

class CSkinModel : Uncopyable
{
public:
	struct SSkinModelCB
	{
		CMatrix worldMat;		//ワールド行列
		CMatrix viewProjMat;			//ビュープロジェクション行列
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
	void Load(wchar_t* filePath, CAnimation* animation = nullptr);

	/*
	描画関数
	view	ビュー行列
	proj	プロジェクション行列
	*/
	void Draw(const CMatrix& view, const CMatrix& proj);

	//モデルを取得
	DirectX::Model* GetBody()
	{
		return m_skinModel.get();
	}

	//スケルトンを取得
	CSkelton* GetSkelton()
	{
		return m_skelton.get();
	}

	//ワールド行列の取得
	const CMatrix& GetWorldMatrix()
	{
		return worldMatrix;
	}

private:
	std::unique_ptr<CSkelton>		m_skelton = nullptr;			//スケルトン
	CConstantBuffer					constantBuffer;					//定数バッファ
	std::unique_ptr<DirectX::Model> m_skinModel = nullptr;			//スキンモデル
	CMatrix							worldMatrix = CMatrix::Identity;	//ワールド行列
	
};