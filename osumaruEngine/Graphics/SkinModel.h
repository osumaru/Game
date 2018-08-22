#pragma once
#include "SkinModelEffectFactory.h"
class Skelton;
class Animation;
//スキンモデルクラス

class SkinModel : Uncopyable
{
public:
	struct SkinModelCB
	{
		Matrix worldMat;		//ワールド行列
		Matrix viewMat;			//ビュー行列
		Matrix projMat;			//プロジェクション行列
	};

	//コンストラクタ
	SkinModel();

	//デストラクタ
	~SkinModel();

	/*
	ワールド行列を更新
	position	座標
	rotation	回転
	scale		拡大
	*/
	void Update(Vector3 position, Quaternion rotation, Vector3 scale);

	/*
	モデルの読み込み
	filePath	モデルのファイルパス
	animation	アニメーションが有るモデルならアニメーションのインスタンス
	*/
	void Load(wchar_t* filePath, Animation* animation = nullptr);

	/*
	描画関数
	view	ビュー行列
	proj	プロジェクション行列
	*/
	void Draw(Matrix view, Matrix proj);

	//モデルを取得
	DirectX::Model* GetBody()
	{
		return m_skinModel.get();
	}

	//スケルトンを取得
	Skelton* GetSkelton()
	{
		return m_skelton.get();
	}

private:
	std::unique_ptr<Skelton>		m_skelton = nullptr;			//スケルトン
	ConstantBuffer					constantBuffer;					//定数バッファ
	std::unique_ptr<DirectX::Model> m_skinModel = nullptr;			//スキンモデル
	Matrix							worldMatrix = Matrix::Identity;	//ワールド行列
	
};