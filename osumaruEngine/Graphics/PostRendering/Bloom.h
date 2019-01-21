#pragma once

class CBloom : Uncopyable
{
public:

	//������
	void Init();

	//�K�E�X�u���[�̃E�F�C�g��ݒ�
	void SetWeight(float rate);

	//�`��
	void Draw();

	//�A�N�e�B�u�t���O��ݒ�
	void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}

private:
	//���_���C�A�E�g
	struct VSLayout
	{
		CVector4 pos;
		CVector2 uv;
	};

	//�萔�o�b�t�@
	struct SBloomCB
	{
		CVector4 textureSize;
		CVector4 offset;
		CVector4 weight1;
		CVector4 weight2;

	};

private:
	bool			m_isActive = false;		//�A�N�e�B�u���ǂ����̃t���O
	static const int BLUR_RANGE = 8;		//�u���[��������͈�
	static const int DOWN_SAMPLING_NUM = 5;	//�_�E���T���v�����O�̐�
	CRenderTarget	m_downSamplingTarget[DOWN_SAMPLING_NUM][2];
	CPrimitive		m_primitive;			//�v���~�e�B�u
	CRenderTarget	m_luminanceTarget;		//�P�x���o�p�̃����_�����O�^�[�Q�b�g
	CRenderTarget	m_combineTarget;		//�ڂ��������p�̃����_�����O�^�[�Q�b�g
	float			m_weight[BLUR_RANGE];	//�K�E�X�u���[�p�̃E�F�C�g
	CShader			m_mainPS;				//���C���̃s�N�Z���V�F�[�_�[
	CShader			m_mainVS;				//���C���̒��_�V�F�[�_�[
	CShader			m_combinePS;			//�ڂ��������p�̃s�N�Z���V�F�[�_�[
	CShader			m_finalPS;				//�ŏI�����p�̃s�N�Z���V�F�[�_�[
	CShader			m_XBlurVS;				//X�u���[�p�̒��_�V�F�[�_�[
	CShader			m_YBlurVS;				//Y�u���[�p�̒��_�V�F�[�_�[
	CShader			m_BlurPS;				//�u���[�p�̃s�N�Z���V�F�[�_�[
	CConstantBuffer	m_cb;					//�萔�o�b�t�@
	CSamplerState	m_sampler;				//�T���v���[
};