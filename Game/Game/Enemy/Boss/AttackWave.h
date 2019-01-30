/*
*	�{�X�̍U���Ŕ�������g�N���X
*/

#pragma once

class CCamera;

class CAttackWave : public IGameObject
{
public:
	//������
	//camera	�J����
	//position	���W
	void Init(const CCamera* camera, const CVector3& position);

	//�X�V
	void Update() override;

	//�`��
	void AfterDraw() override;
private:
	//���_���C�A�E�g
	struct SLayout
	{
		CVector4 position;
		CVector2 uv;
	};

	struct SConstantBuffer
	{
		CMatrix worldViewProj;		//���[���h�r���[�v���W�F�N�V�����s��
		float alpha;				//�A���t�@�l
	};

	const CCamera*		m_camera = nullptr;	//�J����
	CShader				m_vs;				//���_�V�F�[�_�[
	CShader				m_ps;				//�s�N�Z���V�F�[�_�[
	CConstantBuffer		m_cb;				//�R���X�^���g�o�b�t�@
	CPrimitive			m_primitive;		//�v���~�e�B�u
	CTexture*			m_texture;			//�e�N�X�`��
	CVector2			m_size;				//�T�C�Y
	CMatrix				m_worldMatrix;		//���[���h�s��
	CVector3			m_position;			//���W
	CQuaternion			m_rotation;			//��]
	float				m_alpha = 1.0f;		//�A���t�@�l
	float				m_lifeTimer = 0.0f;	//����
	float				m_waveHitLength = 1.0f; //�g�������鋗��
};