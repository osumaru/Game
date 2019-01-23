#pragma once
class CParticle;
class CCamera;

struct SParticleEmittInfo
{
	wchar_t*	filePath;			//�e�N�X�`���̃t�@�C���p�X
	float width;				//�p�[�e�B�N���̉���
	float height;				//�p�[�e�B�N���̏c��
	CVector4 uv;				//�e�N�X�`����uv���W�B�����uv�A�E����uv
	CVector3 randomPosition;		//�p�[�e�B�N�����W�̃����_����
	CVector3 gravity;		//�p�[�e�B�N���̏d��
	float	lifeTime;			//�p�[�e�B�N���̎���
	float	emittIntervalTime;	//�p�[�e�B�N�����o��C���^�[�o���̎���
	float	emitterLifeTime;	//�G�~�b�^�[�̎���
	CVector3 emitterPosition;//�G�~�b�^�[�̍��W
	CVector3 moveSpeed;			//�p�[�e�B�N���̈ړ����x
	CVector3 randomMoveSpeed;	//�p�[�e�B�N���̈ړ����x�̃����_����
	int particleNum;			//�����ɏo��p�[�e�B�N���̐�
	bool isFirstTimeRandom;		//��ԍŏ��Ƀp�[�e�B�N���o���Ƃ��������Ԃ����炷��
	EnAlphaBlendState alphaBlendState;//�A���t�@�u�����h�̃X�e�[�g
};

//�p�[�e�B�N���G�~�b�^�[
class CParticleEmitter : public IGameObject
{
public:
	//�R���X�g���N�^
	CParticleEmitter();

	//�f�X�g���N�^
	~CParticleEmitter();

	/*
	�G�~�b�^�[�̏�����
	info�@�p�[�e�B�N���ƃG�~�b�^�[�̏��������
	camera	�r���{�[�h�����Ɏg���J����
	*/
	void Init(const SParticleEmittInfo& info, const CCamera* camera);

	//�X�V�֐�
	void Update()override;

	//���W��ݒ�B
	void SetPosition(const CVector3& position)
	{
		m_info.emitterPosition = position;
	}

private:
	const CCamera*			m_pCamera;		//�J����
	SParticleEmittInfo		m_info;			//�p�[�e�B�N���ƃG�~�b�^�[�̏��������
	float					m_lifeTimer;	//����
	float					m_intervalTime;	//�p�[�e�B�N�����o���C���^�[�o���^�C��
	int						m_particleNum;	//1�t���[���ɏo��p�[�e�B�N���̐�
};