#pragma once
#pragma once
#include "../Graphics/Primitive.h"
#include "../Graphics/Shader.h"

struct RigidBodyVSLayout
{
	Vector4 pos;
	Vector3 color;
};
//剛体を表示するクラス

class RigidBodyDraw : public btIDebugDraw
{
public:
	//コンストラクタ
	RigidBodyDraw();

	//デストラクタ
	~RigidBodyDraw();

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
	void Draw(Matrix viewMatrix, Matrix projectionMatrix);

	//よくわかってない
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) {}

	//よくわかってない
	void reportErrorWarning(const char* warningString) {}

	//よくわかってない
	void draw3dText(const btVector3& location, const char* textString) {}

	//よくわかってない
	void setDebugMode(int debugMode) {}

	void Reset()
	{
		//毎フレームインデックスバッファと頂点バッファをリセット
		m_count = 0;
		m_vertexBuffer.clear();
		m_indexBuffer.clear();
	}

	//よくわかってない
	int getDebugMode() const
	{
		return 0;
	}

private:
	std::vector<DWORD> m_indexBuffer;			//インデックスバッファ
	std::vector<RigidBodyVSLayout> m_vertexBuffer;	//頂点バッファ
	Primitive		m_primitive;			//プリミティブ
	int				m_count;				//プリミティブの数
	Shader			m_vs;				//エフェクト
	Shader			m_ps;
	ConstantBuffer	m_cb;
};