#pragma once

class CWeaponTraceDraw
{
public:

	void Init();

	void Add(const CVector3& swordRootPosition, const CVector3& swordPointPosition);

	void Start(const CVector3& swordRootPosition, const CVector3& swordPointPosition);

	void Draw();

private:
	//頂点レイアウト
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	}; 
	CVector4						m_rootPos;
	CVector4						m_pointPos;
	static const int				VERTEX_STRIDE_NUM = 4;
	static const int				INDEX_STRIDE_NUM = 6;
	static const int				POLIGON_NUM = 12;
	DWORD							m_indexBuffer[INDEX_STRIDE_NUM * POLIGON_NUM];
	SVSLayout						m_vertexBuffer[VERTEX_STRIDE_NUM * POLIGON_NUM];
	CTexture*						m_pTexture;			//テクスチャ
	CShader							m_vertexShader;		//頂点シェーダー
	CShader							m_pixelShader;		//ピクセルシェーダー
	CPrimitive						m_primitive;		//プリミティブ
	CConstantBuffer					m_cb;
	CMatrix							m_viewProj;

};