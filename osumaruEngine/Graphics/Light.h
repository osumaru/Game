#pragma once
//���C�g�N���X

class CLight
{
public:
	//�R���X�g���N�^
	CLight();

	//������ݒ�
	void SetAmbientLight(const CVector4& ambientLight)
	{
		m_ambientLight = ambientLight;
	}

	//�������擾
	const CVector4& GetAmbientLight() const
	{
		return m_ambientLight;
	}

	//
	void SetDiffuseLight(int lightNum, const CVector4& diffuseLight)
	{
		m_diffuseLight[lightNum] = diffuseLight;
	}

	const CVector4& GetDiffuseLight(int lightNum) const
	{
		return m_diffuseLight[lightNum];
	}

	void SetDiffuseLightDir(int lightNum, const CVector4& diffuseLight)
	{
		m_diffuseLight[lightNum] = diffuseLight;
	}

	const CVector4& GetDiffuseLightDir(int lightNum) const
	{
		return m_diffuseLight[lightNum];
	}

private:
	static const int DIFFUSE_LIGHT_NUM = 4;
	CVector4 m_ambientLight;
	CVector4 m_diffuseLight[DIFFUSE_LIGHT_NUM];
	CVector4 m_diffuseLightDirection[DIFFUSE_LIGHT_NUM];
};