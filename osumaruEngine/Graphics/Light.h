#pragma once
//���C�g�N���X

static const int DIFFUSE_LIGHT_NUM = 4;
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

	//�f�B�t���[�Y���C�g��ݒ�
	void SetDiffuseLight(int lightNum, const CVector4& diffuseLight)
	{
		m_diffuseLight[lightNum] = diffuseLight;
	}

	//�f�B�t���[�Y���C�g���擾
	const CVector4& GetDiffuseLight(int lightNum) const
	{
		return m_diffuseLight[lightNum];
	}

	//�f�B�t���[�Y���C�g�̕�����ݒ�
	void SetDiffuseLightDir(int lightNum, const CVector4& diffuseLight)
	{
		m_diffuseLightDirection[lightNum] = diffuseLight;
	}

	//�f�B�t���[�Y���C�g�̕������擾
	const CVector4& GetDiffuseLightDir(int lightNum) const
	{
		return m_diffuseLightDirection[lightNum];
	}

private:
	CVector4 m_ambientLight;							//����
	CVector4 m_diffuseLight[DIFFUSE_LIGHT_NUM];			//�f�B�t���[�Y���C�g
	CVector4 m_diffuseLightDirection[DIFFUSE_LIGHT_NUM];//�f�B�t���[�Y���C�g�̕���
};