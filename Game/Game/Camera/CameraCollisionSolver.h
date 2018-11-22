#pragma once

class CCameraCollisionSolver {
public:
	//コンストラクタ
	CCameraCollisionSolver();

	//デストラクタ
	~CCameraCollisionSolver();

	//初期化
	//radius	カメラのバウンディングスフィアの半径
	void Init(float radius);

	//コリジョン解決の実行
	//result	コリジョン解決を行った結果のカメラの視点の座標が格納される
	//posiiton	カメラの視点
	//target	カメラの注視点
	//return	コリジョン解決を行った場合はtrueが返ってくる
	bool Execute(CVector3& result, const CVector3& position, const CVector3& target);
private:
	CSphereCollider	m_collider;		 //コライダー
	float			m_radius = 0.0f; //半径
};