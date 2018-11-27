#pragma once

class CWeaponTraceDraw
{
public:

	void Init();

	void Add(const CVector3& swordRootPosition, const CVector3& swordPointPosition);

	void Start();

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
	DWORD							m_indexCount = 0;
	int								m_vertexCount = 0;;
	static const int				INDEX_BUFFER_NUM = 1500;
	static const int				VERTEX_BUFFER_NUM = 1000;
	DWORD							m_indexBuffer[INDEX_BUFFER_NUM];
	SVSLayout						m_vertexBuffer[VERTEX_BUFFER_NUM];
	CTexture*						m_pTexture;			//テクスチャ
	CShader							m_vertexShader;		//頂点シェーダー
	CShader							m_pixelShader;		//ピクセルシェーダー
	CPrimitive						m_primitive;		//プリミティブ
	CConstantBuffer					m_cb;
	CMatrix							m_viewProj;

};