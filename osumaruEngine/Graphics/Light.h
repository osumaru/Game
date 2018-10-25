#pragma once
//ライトクラス

static const int DIFFUSE_LIGHT_NUM = 4;
class CLight
{
public:
	//コンストラクタ
	CLight();

	//環境光を設定
	void SetAmbientLight(const CVector4& ambientLight)
	{
		m_ambientLight = ambientLight;
	}

	//環境光を取得
	const CVector4& GetAmbientLight() const
	{
		return m_ambientLight;
	}

	//ディフューズライトを設定
	void SetDiffuseLight(int lightNum, const CVector4& diffuseLight)
	{
		m_diffuseLight[lightNum] = diffuseLight;
	}

	//ディフューズライトを取得
	const CVector4& GetDiffuseLight(int lightNum) const
	{
		return m_diffuseLight[lightNum];
	}

	//ディフューズライトの方向を設定
	void SetDiffuseLightDir(int lightNum, const CVector4& diffuseLight)
	{
		m_diffuseLightDirection[lightNum] = diffuseLight;
	}

	//ディフューズライトの方向を取得
	const CVector4& GetDiffuseLightDir(int lightNum) const
	{
		return m_diffuseLightDirection[lightNum];
	}

private:
	CVector4 m_ambientLight;							//環境光
	CVector4 m_diffuseLight[DIFFUSE_LIGHT_NUM];			//ディフューズライト
	CVector4 m_diffuseLightDirection[DIFFUSE_LIGHT_NUM];//ディフューズライトの方向
};