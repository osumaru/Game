#pragma once

class CMotionBlur : Uncopyable
{
public:

	void Init();

	void Update();

	void Draw();

private:
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	bool				m_isActive = false;		//�A�N�e�B�u���ǂ����̃t���O
	static const int	BLUR_RANGE = 8;		//�u���[��������͈�
	static const int	DOWN_SAMPLING_NUM = 5;	//�_�E���T���v�����O�̐�
	CPrimitive			m_primitive;			//�v���~�e�B�u
	CShader				m_vs;					//���_�V�F�[�_�[
	CShader				m_ps;					//�s�N�Z���V�F�[�_�[
	CSamplerState		m_sampler;				//�T���v���[
};