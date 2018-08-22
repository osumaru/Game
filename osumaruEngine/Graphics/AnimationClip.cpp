#include "engineStdafx.h"
#include "AnimationClip.h"
#include "Skelton.h"
void AnimationClip::Load(wchar_t * filePath)
{
	m_isLoop = false;
	m_currentFrameNo = 0;
	m_frameTime = 0.0f;
	m_topBoneKeyFrameList = nullptr;
	auto fp = _wfopen(filePath, L"rb");

	//アニメーションクリップのヘッダーをロード。
	AnimClipHeader header;
	fread(&header, sizeof(header), 1, fp);

	if (header.numAnimationEvent > 0) {
		//m_animationEvent = std::make_unique<CAnimationEvent[]>(header.numAnimationEvent);
		//アニメーションイベントがあるなら、イベント情報をロードする。
		for (auto i = 0; i < header.numAnimationEvent; i++) {
			AnimationEvent animEvent;
			fread(&animEvent, sizeof(animEvent), 1, fp);
			//イベント名をロードする。
			static char eventName[256];
			static wchar_t wEventName[256];
			fread(eventName, animEvent.eventNameLength + 1, 1, fp);
			mbstowcs(wEventName, eventName, 255);
			//m_animationEvent[i].SetInvokeTime(animEvent.invokeTime);
			//m_animationEvent[i].SetEventName(wEventName);
		}
	}
	//m_numAnimationEvent = header.numAnimationEvent;

	//中身をごそっとロード。
	auto keyframes = std::make_unique<KeyframeRow[]>(header.numKey);
	fread(keyframes.get(), sizeof(KeyframeRow), header.numKey, fp);
	fclose(fp);
	for (auto i = 0; i < header.numKey; i++) {
		auto keyframe = std::make_unique<Keyframe>();
		keyframe->boneIndex = keyframes[i].boneIndex;
		keyframe->transform = Matrix::Identity;
		keyframe->time = keyframes[i].time;
		for (auto j = 0; j < 4; j++) {
			keyframe->transform.m[j][0] = keyframes[i].transform[j].x;
			keyframe->transform.m[j][1] = keyframes[i].transform[j].y;
			keyframe->transform.m[j][2] = keyframes[i].transform[j].z;
		}
		m_keyframes.push_back(std::move(keyframe));
	}

	//ボーンインデックスごとのキーフレームの連結リストを作成する。
	m_keyFramePtrListArray.resize(512);

	for (auto& keyframe : m_keyframes) {
		m_keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe.get());
		if (m_topBoneKeyFrameList == nullptr) {
			m_topBoneKeyFrameList = &m_keyFramePtrListArray[keyframe->boneIndex];
		}
	}

	m_localMatrix.resize(m_keyFramePtrListArray.size());
	for (int i = 0;i < m_localMatrix.size();i++)
	{
		if (!m_keyFramePtrListArray[i].empty())
		{
			m_localMatrix[i] = m_keyFramePtrListArray[i][0]->transform;
		}
		else
		{
			m_localMatrix[i] = Matrix::Identity;
		}

	}
}


void AnimationClip::Update(float deltaTime)
{
	
	if (m_isPlay)
	{
		m_frameTime += deltaTime;
		if ((*m_topBoneKeyFrameList)[m_currentFrameNo]->time < m_frameTime)
		{
			int i = 0;
			for (auto& keyframe : m_keyFramePtrListArray)
			{
				if (!keyframe.empty())
				{
					m_localMatrix[i] = keyframe[m_currentFrameNo]->transform;
				}
				i++;
			}
			m_currentFrameNo++;
			if (m_topBoneKeyFrameList->size() <= m_currentFrameNo)
			{
				m_isPlay = false;
			}
			m_frameTime = 0.0f;
		}
	}
}

void AnimationClip::Play()
{
	m_isPlay = true;
	m_currentFrameNo = 0;
}
