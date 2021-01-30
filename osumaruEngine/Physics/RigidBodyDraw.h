#pragma once
#pragma once
#include "../Graphics/Primitive.h"
#include "../Graphics/Shader.h"
#include "IRigidBodyDraw.h"

struct SRigidBodyVSLayout
{
	CVector4 pos;
	CVector3 color;
};
//剛体を表示するクラス

class CRigidBodyDraw : public IRigidBodyDraw
{
public:
	//コンストラクタ
	CRigidBodyDraw();

	//デストラクタ
	~CRigidBodyDraw() override;

	//初期化関数
	void Init();

	/*
	頂点を追加する関数
	from	1個目の頂点
	to		2個目の頂点
	color	プリミティブの色
	*/
	void drawLine(const btVector3 &from, const btVector3 &to, const btVector3& color)override;

	/*
	描画関数
	viewMatrix			カメラのビュー行列
	projectionMatrix	カメラの射影行列
	*/
	void Draw(CMatrix viewMatrix, CMatrix projectionMatrix)override;


	//カウントをリセット
	void Reset() override
	{
		ZeroMemory(m_vertexBuffer, sizeof(m_vertexBuffer));
		ZeroMemory(m_indexBuffer, sizeof(m_indexBuffer));
		//毎フレームインデックスバッファと頂点バッファをリセット
		m_count = 0;
	}

private:
	static const int VERTEX_NUM = 100000;
	SRigidBodyVSLayout m_vertexBuffer[VERTEX_NUM];
	DWORD m_indexBuffer[VERTEX_NUM];
	CPrimitive		m_primitive;			//プリミティブ
	int				m_count;				//プリミティブの数
	CShader			m_vs;				//エフェクト
	CShader			m_ps;
	CConstantBuffer	m_cb;
};