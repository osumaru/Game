#pragma once
#include "AnimationEvent.h"
class CSkelton;
class CKeyframe;
class CAnimation;

/*!
*@brief	�A�j���[�V�����N���b�v�̃w�b�_�[�B
*/
struct SAnimClipHeader {
	std::uint32_t numKey;				//!<�L�[�t���[���̐��B
	std::uint32_t numAnimationEvent;	//!<�A�j���[�V�����C�x���g�̐��B
};
/*!
*@brief	�A�j���[�V�����C�x���g
*/
struct SAnimationEvent {
	float	invokeTime;					//!<�A�j���[�V�����C�x���g���������鎞��(�P��:�b)
	std::uint32_t eventNameLength;		//!<�C�x���g���̒����B
};
/*!
*@brief	�L�[�t���[���B
*/
struct SKeyframe {
	std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
	float time;					//!<���ԁB
	CMatrix transform;			//!<�g�����X�t�H�[���B
};
/*!
*@brief	�L�[�t���[���B
*/
struct SKeyframeRow {
	std::uint32_t boneIndex;	//!<�{�[���C���f�b�N�X�B
	float time;					//!<���ԁB
	CVector3 transform[4];		//!<�g�����X�t�H�[���B
};

struct SBoneFreeze
{
	bool isFreezeX = false;
	bool isFreezeY = false;
	bool isFreezeZ = false;
};

//�A�j���[�V�����N���b�v(��̃A�j���[�V�������Ǘ�����N���X)

class CAnimationClip : Uncopyable
{
public:
	/*
	�A�j���[�V������ǂݍ��ފ֐��B
	filePath	�A�j���[�V�����t�@�C���̃p�X
	*/
	void Load(wchar_t* filePath);


	//�X�V�֐��B
	void Update(float deltaTime);

	//�{�[���̍s����擾�B
	const std::vector<CMatrix>& GetLocalMatrix() const
	{
		return m_localMatrix;
	}

	//�A�j���[�V�������Đ��B
	void Play();

	//���[�v�t���O��ݒ�B
	void SetIsLoop(bool isLoop)
	{
		m_isLoop = isLoop;
	}

	//���[�v�t���O���擾�B
	bool IsLoop() const
	{
		return m_isLoop;
	}

	//�Đ������̃t���O���擾�B
	bool IsPlay() const
	{
		return m_isPlay;
	}

	//�A�j���[�V�����C�x���g�̍X�V
	void AnimationInvoke(CAnimation* animation);

	void Reset()
	{
		for (int i = 0; i < m_animationEventNum; i++)
		{
			m_animationEvent[i].SetInvokedFlg(false);

		}
	}

	void SetBoneFreezeFlg(int boneID, bool isFreezeX, bool isFreezeY, bool isFreezeZ)
	{
		m_freezeFlg[boneID].isFreezeX = isFreezeX;
		m_freezeFlg[boneID].isFreezeY = isFreezeY;
		m_freezeFlg[boneID].isFreezeZ = isFreezeZ;
	}

private:
	bool									m_isPlay = false;					//�Đ������H
	bool									m_isLoop = false;					//���[�v���Ă邩�H
	const wchar_t*							m_clipName = nullptr;				//�A�j���[�V�����N���b�v�̖��O�B
	std::vector<SKeyframe*>					m_keyframes;						//�L�[�t���[���B
	std::vector<std::vector<SKeyframe*>>	m_keyFramePtrListArray;				//�{�[�����̃L�[�t���[���̃��X�g
	std::vector<SKeyframe*>*				m_topBoneKeyFrameList = nullptr;	//��ԍŏ��̃L�[�t���[��
	std::vector<CMatrix>					m_localMatrix;						//�{�[���̍s���ۑ����邽�߂̂���
	std::vector<SBoneFreeze>				m_freezeFlg;						//�{�[���̍s���ۑ����邽�߂̂���
	float									m_frameTime = 0.0f;					//�t���[����i�߂邽�߂̃^�C�}�[
	int										m_currentFrameNo = 0;				//���݂̃t���[���i���o�[
	CAnimationEvent*						m_animationEvent = nullptr;			//�A�j���[�V�����C�x���g�B
	int										m_animationEventNum = 0;			//�A�j���[�V�����C�x���g�̐�
	int										m_maxFrameNum = 0;					//�ő�L�[�t���[����
};