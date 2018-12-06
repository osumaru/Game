#pragma once

class CWireDraw : public Uncopyable
{
public:
	/*
	初期化
	startPos	始点の座標
	endPos		終点の座標
	color		色
	*/
	void Init(const CVector3& startPos, const CVector3& endPos, const CVector3& color);

	void Update();

	//描画
	void Draw();

	//始点を設定
	void SetStartPosition(const CVector3& pos)
	{
		m_startPos = pos;
	}
	
	//終点を設定
	void SetEndPosition(const CVector3& pos)
	{
		m_endPos = pos;
	}

	//カラーを設定
	void SetColor(const CVector3& color)
	{
		m_color = color;
	}

	struct SVSLayout
	{
		CVector4 pos;
		CVector3 color;
	};
private:
	CVector3 m_endPos;
	CVector3 m_startPos;
	CVector3 m_color;
	CPrimitive	m_primitive;
	CShader	m_ps;
	CShader m_vs;
	CConstantBuffer m_cb;
};