#pragma once
#include "IRigidBodyDraw.h"

class NullRigidBodyDraw : public IRigidBodyDraw
{
public:
	NullRigidBodyDraw()
	{

	}

	~NullRigidBodyDraw()override
	{

	}

	//初期化関数
	void Init()override
	{

	}

	/*
	頂点を追加する関数
	from	1個目の頂点
	to		2個目の頂点
	color	プリミティブの色
	*/
	void drawLine(const btVector3 &from, const btVector3 &to, const btVector3& color)override
	{

	}

	/*
	描画関数
	viewMatrix			カメラのビュー行列
	projectionMatrix	カメラの射影行列
	*/
	void Draw(CMatrix viewMatrix, CMatrix projectionMatrix)override
	{

	}

	//カウントをリセット
	void Reset() override
	{

	}

};

