#pragma once
#include "Effect.h"
//�G�t�F�N�g�G���W��

class CEffectEngine : Uncopyable
{
public:
	//������
	void Init();

	//�X�V
	void Update();

	//�`��
	void Draw();

	//�G�t�F�N�g�`��p�̃J������ݒ�
	void SetCamera(const CCamera* camera)
	{
		m_pCamera = camera;
	}

	/*
	�G�t�F�N�g���Đ�
	effect	�Đ�����G�t�F�N�g�̃C���X�^���X
	
	*/
	Effekseer::Handle Play(CEffect& effect);

	//�G�t�F�N�g�}�l�[�W���[���擾
	Effekseer::Manager* GetEffectManager()
	{
		return m_manager;
	}
private:
	const CCamera*						m_pCamera = nullptr;	//�`��Ɏg���J����
	Effekseer::Manager*				m_manager = nullptr;	//�}�l�[�W���[
	EffekseerRenderer::Renderer*	m_renderer = nullptr;	//�����_���[
};