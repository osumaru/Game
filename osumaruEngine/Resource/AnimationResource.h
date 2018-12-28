#pragma once
#include "../Graphics/AnimationClip.h"

struct SAnimationClipInfo
{
	const wchar_t*							filePath = nullptr;				//�A�j���[�V�����N���b�v�̖��O�B
	std::vector<SKeyframe*>					keyframes;						//�L�[�t���[���B
	CAnimationEvent*						animationEvent = nullptr;			//�A�j���[�V�����C�x���g�B
	int										animationEventNum = 0;			//�A�j���[�V�����C�x���g�̐�
	std::vector<std::vector<SKeyframe*>>	keyFramePtrListArray;				//�{�[�����̃L�[�t���[���̃��X�g
};

class CAnimationResource : Uncopyable
{
public:

	const SAnimationClipInfo* Load(const wchar_t* clipName);

private:
	std::map<int, const SAnimationClipInfo*> m_animationResource;
};