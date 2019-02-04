#pragma once
#include "WeaponCommon.h"

class CWeaponEraseEffect : Uncopyable
{
public:
	/*
	初期化
	skinmodel　武器のモデルの配列
	*/
	void Init(const CSkinModel* skinmodel[enWeaponNum]);

	//描画するかのフラグを設定
	void SetIsDraw(bool isDraw)
	{
		m_isDraw = isDraw;
	}

	/*
	ワールド行列を使ってプリミティブの位置を更新
	mat			ワールド行列
	weaponNum	武器の種類
	*/
	void SetWorldMatrix(const CMatrix& mat, EnPlayerWeapon weaponNum);

	//描画関数
	void Draw();

	//Clipする値を設定
	void SetDissolve(float dissolve)
	{
		m_dissolve = dissolve;
	}


	struct SVSLayout
	{
		CVector4 position;//座標
		CVector3 color;	//カラー
		float dissolve;	//Clipする値
	};
public:
	bool						m_isDraw = true;					//描画フラグ
	std::vector<SVSLayout>		m_vertexBuffer;						//頂点バッファ
	std::vector<unsigned short> m_indexBuffer;						//インデックスバッファ
	std::vector<CVector3>		m_weaponVertexBuffer[enWeaponNum];	//武器毎の頂点バッファ
	std::vector<unsigned short> m_weaponIndexBuffer[enWeaponNum];	//武器毎の頂点バッファ
	CVector3					m_color;							//色(x,y,z) = (r,g,b)
	CPrimitive					m_primitive;						//プリミティブ
	CShader						m_ps;								//ピクセルシェーダー
	CShader						m_vs;								//頂点シェーダー
	CConstantBuffer				m_cb;								//定数バッファ
	CConstantBuffer				m_alphaCB;							//
	float						m_dissolve = 1.0f;					//武器を
};