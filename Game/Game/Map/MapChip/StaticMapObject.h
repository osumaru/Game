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
	anim		アニメーション付きのモデルの場合アニメーションを入れる入れ物
	*/
	void Init(const Vector3& position, const Quaternion& rotation, const wchar_t* modelName, Animation* anim = nullptr)override;

	//更新関数
	void Update()override;

	//描画関数
	void Draw()override;

private:
	std::unique_ptr<RigidBody>		m_rigidBody;		//剛体
	std::unique_ptr<BoxCollider>		m_boxCollider;		//コライダー
};
