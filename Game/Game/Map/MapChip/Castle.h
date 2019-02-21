#pragma once
#include "MapChip.h"
//ワイヤーで飛ぶためのボーンを入れているモデル(ZUp)でナビメッシュのルートを弾くためのオブジェクト
//CastleとかCastleWallとかChurchとかがこれになる

class CCastle : public MapChip
{
public:

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

private:
	std::unique_ptr<CRigidBody>			m_rigidBody;		//剛体
	std::unique_ptr<CMeshCollider>		m_meshCollider;		//コライダー

};