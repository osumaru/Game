#pragma once
#include "MapChip.h"

//背景オブジェクト

class StaticMapObject : public MapChip
{
public:
	//コンストラクタ
	StaticMapObject();

	//デストラクタ
	~StaticMapObject();

	/*
	初期化する関数
	position	座標
	rotation	回転
	modelName	読み込むモデルの名前
	collider	コライダーの設定　falseならメッシュ	trueならボックス
	anim		アニメーション付きのモデルの場合アニメーションを入れる入れ物
	*/
	void Init(const SMapChipInfo& info, CAnimation* anim = nullptr)override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;

	//モデルを取得
	const CSkinModel& GetSkinModel() const 
	{
		return m_skinModel;
	}

private:
	std::unique_ptr<CRigidBody>			m_rigidBody;		//剛体
	std::unique_ptr<CMeshCollider>		m_meshCollider;		//コライダー
	bool								isCollider;
	bool								m_isTree = false;	//木用のコライダーの設定をするためのフラグ		

};
