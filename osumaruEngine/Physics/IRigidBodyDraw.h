#pragma once
class IRigidBodyDraw : public btIDebugDraw
{
public:
	IRigidBodyDraw();
	virtual ~IRigidBodyDraw();
	//初期化関数
	virtual void Init() = 0;

	/*
	頂点を追加する関数
	from	1個目の頂点
	to		2個目の頂点
	color	プリミティブの色
	*/
	virtual void drawLine(const btVector3 &from, const btVector3 &to, const btVector3& color) = 0;

	/*
	描画関数
	viewMatrix			カメラのビュー行列
	projectionMatrix	カメラの射影行列
	*/
	virtual void Draw(CMatrix viewMatrix, CMatrix projectionMatrix) = 0;

	//よくわかってない
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override final
	{
	}

	//よくわかってない
	void reportErrorWarning(const char* warningString) override final
	{
	}

	//よくわかってない
	void draw3dText(const btVector3& location, const char* textString) override final
	{
	}

	//よくわかってない
	void setDebugMode(int debugMode) override final
	{
	}

	//カウントをリセット
	virtual void Reset() = 0;

	//よくわかってない
	int getDebugMode() const override final
	{
		return 0;
	}
};

