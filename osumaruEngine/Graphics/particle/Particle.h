#pragma once
class CTexture;
class CCamera;
#include "ParticleEmitter.h"

class CParticle : public IGameObject
{
public:
	//�p�[�e�B�N���p�̒��_���C�A�E�g
	struct PVSLayout
	{
		CVector4 pos;
		CVector2 uv;
	};
	//�R���X�g���N�^
	CParticle();

	//�f�X�g���N�^
	~CParticle();

	/*
	�p�[�e�B�N����������
	info	�p�[�e�B�N���̏��������
	camera	�r���{�[�h�����Ɏg���J����
	*/
	void Init(const SParticleEmittInfo& info, const CCamera* camera);

	//�X�V�֐�
	void Update()override;

	//���[���h�s��̍X�V
	void UpdateWorldMatrix();

	//�`�揈��
	void AfterDraw()override;

	//���W��ݒ�
	//position	���W
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}

	//�A���t�@�l��ݒ�
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

private:
	struct SParticleCB
	{
		CMatrix worldViewProj;		//���[���h�r���[�v���W�F�N�V�����s��
		float alpha;				//�A���t�@�l
	};
	CVector2			m_size;			//�T�C�Y
	CTexture*			m_pTexture;		//�e�N�X�`��
	CPrimitive			m_primitive;	//�v���~�e�B�u
	CMatrix				m_worldMatrix;	//���[���h�s��
	CQuaternion			m_rotation;		//��]
	CShader				m_vs;			//���_�V�F�[�_�[
	CShader				m_ps;			//�s�N�Z���V�F�[�_�[
	CConstantBuffer		m_cb;
	CVector3			m_position;		//���W
	const CCamera*		m_camera;		//�J����
	float				m_lifeTimer;	//����
	float				m_angle;		//��]��
	CVector3			m_gravity;		//�d��
	CVector3			m_speed;		//���x
	float				m_alpha = 1.0f;	//�A���t�@�l
	EnAlphaBlendState	m_alphaBlendState;	//�A���t�@�u�����h�̃X�e�[�g
	float				m_fadeOutTime = 0.0f;	//�t�F�[�h�A�E�g���鎞��
	float				m_fadeOutTimer = 0.0f;	//�t�F�[�h�A�E�g���鎞��
};