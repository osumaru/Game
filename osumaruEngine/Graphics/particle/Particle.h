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

	//�`�揈��
	void AfterDraw()override;

private:
	CVector2		m_size;			//�T�C�Y
	CTexture*		m_pTexture;		//�e�N�X�`��
	CPrimitive		m_primitive;	//�v���~�e�B�u
	CMatrix			m_worldMatrix;	//���[���h�s��
	CQuaternion		m_rotation;		//��]
	CShader			m_vs;			//���_�V�F�[�_�[
	CShader			m_ps;			//�s�N�Z���V�F�[�_�[
	CConstantBuffer m_cb;
	CVector3		m_position;		//���W
	const CCamera*	m_camera;		//�J����
	float			m_lifeTimer;	//����
	float			m_angle;		//��]��
	CVector3		m_gravity;		//�d��
	CVector3		m_speed;		//���x
};