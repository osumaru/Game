#pragma once
//トレイルを描画するクラス

class CWeaponTraceDraw
{
public:

	//初期化
	void Init();

	/*
	トレイルを描画するを登録
	swordRootPosition	根本の座標
	swordPointPosition	先っちょの座標
	*/
	void Add(const CVector3& swordRootPosition, const CVector3& swordPointPosition);
	
	/*
	トレイルを始める地点を登録
	swordRootPosition	根本の座標
	swordPointPosition	先っちょの座標
	*/
	void Start(const CVector3& swordRootPosition, const CVector3& swordPointPosition);

	//描画
	void Draw();

private:
	//頂点レイアウト
	struct SVSLayout
	{
		CVector4 position;	//座標
		CVector2	uv;		//UV
		float alpha;		//透明度
	}; 

	CVector4						m_rootPos;				//剣の根本の座標
	CVector4						m_pointPos;				//剣の先っちょの座標
	static const int				VERTEX_STRIDE_NUM = 4;	//板ポリ一枚の頂点の数
	static const int				INDEX_STRIDE_NUM = 6;	//板ポリ一枚のインデックスバッファの数
	static const int				POLIGON_NUM = 5;		//板ポリの数
	DWORD							m_indexBuffer[INDEX_STRIDE_NUM * POLIGON_NUM];
	SVSLayout						m_vertexBuffer[VERTEX_STRIDE_NUM * POLIGON_NUM];
	CTexture*						m_pTexture;			//テクスチャ
	CShader							m_vertexShader;		//頂点シェーダー
	CShader							m_pixelShader;		//ピクセルシェーダー
	CPrimitive						m_primitive;		//プリミティブ
	CConstantBuffer					m_cb;				//定数バッファ
	CMatrix							m_viewProj;			//ビュープロジェクション行列

};