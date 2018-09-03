#pragma once
#include "ICollider.h"
//箱のコライダー

class CBoxCollider : public ICollider
{
public:
	//コンストラクタ
	CBoxCollider();

	//デストラクタ
	~CBoxCollider();
	
	/*
	コライダーの初期化
	box		ボックスのサイズ
	*/
	void Create(btVector3 box)
	{
		m_boxShape.reset(new btBoxShape(box));
	}

	//コライダーを取得
	const btCollisionShape* GetBody() const override
	{
		return m_boxShape.get();
	}
private:
	std::unique_ptr<btBoxShape>		m_boxShape;//コライダー
};
