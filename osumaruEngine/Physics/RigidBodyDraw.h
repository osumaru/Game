#pragma once
#pragma once
#include "../Graphics/Primitive.h"
#include "../Graphics/Shader.h"

struct SRigidBodyVSLayout
{
	CVector4 pos;
	CVector3 color;
};
//剛体を表示するクラス

class CRigidBodyDraw : public btIDebugDraw
{
public:
	//コンストラクタ
	CRigidBodyDraw();

	//デストラクタ
	~CRigidBodyDraw();

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
	void Draw(CMatrix viewMatrix, CMatrix projectionMatrix);

	//よくわかってない
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}

	//よくわかってない
	void reportErrorWarning(const char* warningString) {}

	//よくわかってない
	void draw3dText(const btVector3& location, const char* textString) {}

	//よくわかってない
	void setDebugMode(int debugMode) {}

	//カウントをリセット
	void Reset()
	{
		//毎フレームインデックスバッファと頂点バッファをリセット
		m_count = 0;
	}

	//よくわかってない
	int getDebugMode() const
	{
		return 0;
	}

private:
	static const int VERTEX_NUM = 10000;
	SRigidBodyVSLayout m_vertexBuffer[VERTEX_NUM];
	DWORD m_indexBuffer[VERTEX_NUM];
	CPrimitive		m_primitive;			//プリミティブ
	int				m_count;				//プリミティブの数
	CShader			m_vs;				//エフェクト
	CShader			m_ps;
	CConstantBuffer	m_cb;
};