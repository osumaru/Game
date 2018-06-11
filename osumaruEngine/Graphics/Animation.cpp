#include "engineStdafx.h"
#include "Animation.h"
#include "Skelton.h"


void Animation::Init(Skelton* skelton, wchar_t* filePath)
{
	m_count = 0;
	m_currentFrameNo = 0;
	m_skelton = skelton;
	m_topBoneKeyFramList = nullptr;
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
		if (m_topBoneKeyFramList == nullptr) {
			m_topBoneKeyFramList = &m_keyFramePtrListArray[keyframe->boneIndex];
		}
	}
}



void Animation::Update()
{
	m_count++;
	if (m_count >= 10)
	{
		int i = 0;
		for (auto& keyframe : m_keyFramePtrListArray)
		{
			if (!keyframe.empty())
			{
				m_skelton->SetBoneMatrix(keyframe[m_currentFrameNo]->boneIndex, keyframe[m_currentFrameNo]->transform);
			}
			i++;
		}
		m_currentFrameNo++;
		if (m_topBoneKeyFramList->size() <= m_currentFrameNo)
		{
			m_currentFrameNo = 0;
		}
		m_count = 0;
	}

}

