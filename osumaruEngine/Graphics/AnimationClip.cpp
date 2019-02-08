#include "engineStdafx.h"
#include "AnimationClip.h"
#include "Skelton.h"
#include "Animation.h"


void CAnimationClip::Load(wchar_t * filePath)
{
	m_clipName = filePath;
	m_isLoop = false;
	m_currentFrameNo = 0;
	m_frameTime = 0.0f;
	m_topBoneKeyFrameList = nullptr;

	const SAnimationClipInfo* info = AnimationResource().Load(filePath);
	m_animationEventNum = info->animationEventNum;
	if (0 < m_animationEventNum)
	{
		m_animationEvent = std::make_unique<CAnimationEvent[]>(m_animationEventNum);
	}
	for (int i = 0; i < m_animationEventNum; i++)
	{
		m_animationEvent[i] = info->animationEvent[i];
	}

	m_clipName = info->filePath;
	m_keyFramePtrListArray = info->keyFramePtrListArray;
	m_keyframes = info->keyframes;

	m_topBoneKeyFrameList = &m_keyFramePtrListArray[m_keyframes[0]->boneIndex];
	m_localMatrix.resize(m_keyFramePtrListArray.size());
	int keyFrameSize = m_localMatrix.size();
	for (int i = 0;i < keyFrameSize;i++)
	{
		if (!m_keyFramePtrListArray[i].empty())
		{
			m_localMatrix[i] = m_keyFramePtrListArray[i][0]->transform;
		}
		else
		{
			m_localMatrix[i] = CMatrix::Identity;
		}
	}
}


void CAnimationClip::Update(float deltaTime)
{
	
	if (m_isPlay)
	{
		int i = 0;
		//今のキーフレームから次のキーフレームまでの時間
		float keyTime = (*m_topBoneKeyFrameList)[m_currentFrameNo]->time;
		//今のキーフレームから次のキーフレームまでの残り時間
		float nowTime = (*m_topBoneKeyFrameList)[m_currentFrameNo]->time - m_frameTime;
		if (0 < m_currentFrameNo)
		{
			keyTime -= (*m_topBoneKeyFrameList)[m_currentFrameNo - 1]->time;
		}
		nowTime = keyTime - nowTime;
		//非数回避
		if (keyTime == 0.0f)
		{
			keyTime = 1.0f;
		}
		int nextFrameNum = min(m_topBoneKeyFrameList->size() - 1, m_currentFrameNo + 1);
		for (auto& keyframe : m_keyFramePtrListArray)
		{
			if (!keyframe.empty())
			{
				if (m_isLinearInterpolation)
				{
					m_localMatrix[i].Lerp(max(0.0f, nowTime / keyTime), keyframe[m_currentFrameNo]->transform, keyframe[nextFrameNum]->transform);
				}
				else
				{
					m_localMatrix[i] = keyframe[m_currentFrameNo]->transform;
				}
			}
			i++;
		}

		m_frameTime += deltaTime;
		int keyFrameSize = m_topBoneKeyFrameList->size();
		while ((*m_topBoneKeyFrameList)[m_currentFrameNo]->time < m_frameTime)
		{
			m_currentFrameNo++;
			
			if (keyFrameSize <= m_currentFrameNo)
			{
				m_isPlay = false;
				break;
			}
		}
	}
}

void CAnimationClip::AnimationInvoke(CAnimation* animation)
{
	for (int i = 0; i < m_animationEventNum; i++)
	{
		if (m_animationEvent[i].GetInvokeTime() < m_frameTime && !m_animationEvent[i].IsInvoked())
		{
			animation->AnimationEventNotification(m_clipName, m_animationEvent[i].GetEventName());
			m_animationEvent[i].SetInvokedFlg(true);
		}

	}
}

void CAnimationClip::Play()
{
	m_isPlay = true;
	m_currentFrameNo = 0;
	m_frameTime = 0.0f;
	int i = 0;
	for (auto& keyframe : m_keyFramePtrListArray)
	{
		if (!keyframe.empty())
		{
			m_localMatrix[i] = keyframe[0]->transform;
		}
		i++;
	}
}
