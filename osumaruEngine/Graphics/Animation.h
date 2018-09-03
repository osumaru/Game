#pragma once
#include "AnimationClip.h"
class CSkelton;
//�A�j���[�V�������Ǘ�����N���X

class CAnimation : Uncopyable
{
public:

	/*
	�������֐�
	animFilePath	�A�j���[�V�����̃t�@�C���p�X�̔z��
	animNum			�A�j���[�V�����̐�
	*/
	void Init(wchar_t* animFilePath[], int animNum);

	//�X�P���g����ݒ�
	void SetSkelton(CSkelton* skelton);

	/*
	�X�V�֐�
	deltaTime	�i�߂鎞��
	*/
	void Update(float deltaTime);

	/*
	�A�j���[�V�����Đ��֐�
	animationNum	�Đ�����A�j���[�V�����̔ԍ�
	*/
	void Play(int animationNum);

	/*
	��Ԃ��Ȃ���A�j���[�V�������Đ�����֐�
	animationNum	�Đ�����A�j���[�V�����̔ԍ�
	interpolationTime	��Ԃ��鎞��
	*/
	void Play(int animationNum, float interpolationTime);

	/*
	�A�j���[�V�����̃��[�v�t���O��ݒ�
	animationNum	�t���O��ݒ肷��A�j���[�V�����̔ԍ�
	isLoop			���[�v���邩�̃t���O
	*/
	void SetLoopFlg(int animationNum, bool isLoop)
	{
		m_animationClips[animationNum].SetIsLoop(isLoop);
	}

private:
	std::unique_ptr<CAnimationClip[]>	m_animationClips = nullptr;		//�A�j���[�V�����N���b�v�̔z��
	int									m_currentAnimationNum = 0;		//���Đ����Ă���A�j���[�V�����̔ԍ�
	int									m_curCurrentAnimationNum = 0;	//�ЂƂO�ɍĐ����Ă����A�j���[�V�����̔ԍ�
	CSkelton*							m_skelton = nullptr;			//�X�P���g���̔ԍ�
	float								m_blendRate = 0.0f;				//�A�j���[�V������Ԏ��̃��[�g
	bool								m_isInterpolation = false;		//��Ԃ��Ă��邩�H
	float								m_interpolationTime = 1.0f;		//�A�j���[�V������Ԏ��̌o�߂����鎞��
};