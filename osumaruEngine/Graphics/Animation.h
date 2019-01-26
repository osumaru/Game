#pragma once
#include "AnimationClip.h"
class CSkelton;
//�A�j���[�V�������Ǘ�����N���X

class CAnimation : Uncopyable
{
public:
	using AnimationEventListener = std::function<void(const wchar_t* clipName, const wchar_t* eventName)>;
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

	//�A�j���[�V�������Đ����Ă��邩�H
	bool IsPlay() const
	{
		return	m_animationClips[m_currentAnimationNum].IsPlay();
	}

	//�⊮���Ă��邩�̃t���O���擾
	bool IsInterpolation() const
	{
		return m_isInterpolation;
	}

	//���ݍĐ����Ă�A�j���[�V�����̔ԍ����擾
	int GetCurrentAnimationNum() const
	{
		return m_currentAnimationNum;
	}

	//�C�x���g���X�i�[��ǉ�
	void AddAnimationEvent(AnimationEventListener animEvent)
	{
		m_animationEventListener.push_back(animEvent);
	}

	/*
	�A�j���[�V�����C�x���g�̒ʒm
	clipName	�A�j���[�V�����N���b�v�̖��O
	eventName	�A�j���[�V�����C�x���g�̖��O
	*/
	void AnimationEventNotification(const wchar_t* clipName, const wchar_t* eventName)
	{
		for (auto& animEvent : m_animationEventListener)
		{
			animEvent(clipName, eventName);
		}
	}

	/*
	�A�j���[�V�����u�����h�����������{�[����ǉ�
	boneName		�A�j���[�V�����u�����h�����������̖��O
	animationNum	�A�j���[�V�����̔ԍ�
	*/
	void AddBlendAnimation(const wchar_t* boneName, int animationNum);

private:
	//�{�[���̍s����X�V
	void UpdateBoneMatrix(int boneID, const std::vector<CMatrix>& localMat1, const std::vector<CMatrix>& localMat2);

	//�u�����h�A�j���[�V�������邽�߂̏���ǉ�
	void AddBlendAnimationInfo(int boneID, int animationNum, int count);


	//�A�j���[�V�����u�����h�Ɏg�����
	struct SAnimationBlendInfo
	{
		int animationNum;	//�Đ�����A�j���[�V����
		int boneID;			//�A�j���[�V������؂�ւ��鍜��ID
	};

private:
	int									m_rootBoneID;
	std::vector<SAnimationBlendInfo>	m_animationBlend;
	std::unique_ptr<CAnimationClip[]>	m_animationClips = nullptr;		//�A�j���[�V�����N���b�v�̔z��
	int									m_currentAnimationNum = 0;		//���Đ����Ă���A�j���[�V�����̔ԍ�
	int									m_curCurrentAnimationNum = 0;	//�ЂƂO�ɍĐ����Ă����A�j���[�V�����̔ԍ�
	CSkelton*							m_skelton = nullptr;			//�X�P���g���̔ԍ�
	float								m_blendRate = 0.0f;				//�A�j���[�V������Ԏ��̃��[�g
	bool								m_isInterpolation = false;		//��Ԃ��Ă��邩�H
	float								m_interpolationTime = 1.0f;		//�A�j���[�V������Ԏ��̌o�߂����鎞��
	std::vector<AnimationEventListener>	m_animationEventListener;

};