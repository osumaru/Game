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

private:
	CEffect		m_rippleEffect;					//�G�t�F�N�g					
	CVector3	m_position;						//���W
	const float	WAVE_WIDTH = 1.0f;				//�g�̕�
	float		m_waveHitLength = WAVE_WIDTH;	//�g�������鋗��
	float		m_timer = 0.0f;					//�^�C�}�[
};