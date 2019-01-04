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
	m_freezeFlg.resize(m_keyFramePtrListArray.size());
	for (int i = 0;i < m_localMatrix.size();i++)
	{
		if (!m_keyFramePtrListArray[i].empty())
		{
			m_localMatrix[i] = m_keyFramePtrListArray[i][0]->transform;
		}
		else
		{
			m_localMatrix[i] = CMatrix::Identity;
		}
		m_freezeFlg[i] = { false, false, false };
	}
}


void CAnimationClip::Update(float deltaTime)
{
	
	if (m_isPlay)
	{
		//今のキーフレームから次のキーフレームまでの時間
		float keyTime = (*m_topBoneKeyFrameList)[m_currentFrameNo]->time;
		//今のキーフレームから次のキーフレームまでの残り時間
  		float nowTime = (*m_topBoneKeyFrameList)[m_currentFrameNo]->time - m_frameTime;
		if (0 < m_currentFrameNo)
		{
			keyTime -= (*m_topBoneKeyFrameList)[m_currentFrameNo - 1]->time;
		}
		const float currentFrameNo = m_currentFrameNo;
		nowTime = keyTime - nowTime;
		//非数回避
		if (keyTime == 0.0f)
		{
			keyTime = 1.0f;
		}
		int i = 0;
		int nextFrameNum = min(m_topBoneKeyFrameList->size() - 1, m_currentFrameNo + 1);

		for (auto& keyframe : m_keyFramePtrListArray)
		{
			if (!keyframe.empty())
			{
				CMatrix localMatrix = m_localMatrix[i];
				//次のフレームまで線形補間させる
				m_localMatrix[i].Lerp(max(0.0f, nowTime / keyTime), keyframe[m_currentFrameNo]->transform, keyframe[nextFrameNum]->transform);
				if (m_freezeFlg[i].isFreezeX)
				{
					m_localMatrix[i].m[3][0] = localMatrix.m[3][0];
				}
				if (m_freezeFlg[i].isFreezeY)
				{
					m_localMatrix[i].m[3][1] = localMatrix.m[3][1];
				}
				if (m_freezeFlg[i].isFreezeZ)
				{
					m_localMatrix[i].m[3][2] = localMatrix.m[3][2];
				}
			}
			i++;
		}
		m_frameTime += deltaTime;
		while ((*m_topBoneKeyFrameList)[m_currentFrameNo]->time < m_frameTime)
		{
			m_currentFrameNo++;
			
			if (m_topBoneKeyFrameList->size() <= m_currentFrameNo)
			{
				m_isPlay = false;
				for (auto& freezeFlg : m_freezeFlg)
				{
					freezeFlg.isFreezeX = false;
					freezeFlg.isFreezeY = false;
					freezeFlg.isFreezeZ = false;
				}
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
