#include "AnimationResource.h"


CAnimationResource::~CAnimationResource()
{
	for (auto& map : m_animationResource)
	{
		for (auto& keyframe : map.second->keyframes)
		{
			delete keyframe;
		}
		delete[] map.second->animationEvent;
		delete map.second;
	}

}

const SAnimationClipInfo* CAnimationResource::Load(const wchar_t* filePath)
{
	int hash = MakeHash(filePath);
	auto& map = m_animationResource.find(hash);
	if (map == m_animationResource.end())
	{
		SAnimationClipInfo* info = new SAnimationClipInfo;
		info->filePath = filePath;
		auto fp = _wfopen(filePath, L"rb");

		//アニメーションクリップのヘッダーをロード。
		SAnimClipHeader header;
		fread(&header, sizeof(header), 1, fp);

		if (header.numAnimationEvent > 0)
		{
			info->animationEvent = new CAnimationEvent[header.numAnimationEvent];
			//アニメーションイベントがあるなら、イベント情報をロードする。
			for (auto i = 0; i < header.numAnimationEvent; i++)
			{
				SAnimationEvent animEvent;
				fread(&animEvent, sizeof(animEvent), 1, fp);
				//イベント名をロードする。
				static char eventName[256];
				static wchar_t wEventName[256];
				fread(eventName, animEvent.eventNameLength + 1, 1, fp);
				mbstowcs(wEventName, eventName, 255);
				info->animationEvent[i].SetInvokeTime(animEvent.invokeTime);
				info->animationEvent[i].SetEventName(wEventName);
			}
		}
		info->animationEventNum = header.numAnimationEvent;

		//中身をごそっとロード。
		auto keyframes = std::make_unique<SKeyframeRow[]>(header.numKey);
		fread(keyframes.get(), sizeof(SKeyframeRow), header.numKey, fp);
		fclose(fp);
		for (auto i = 0; i < header.numKey; i++)
		{
			auto keyframe = new SKeyframe;
			keyframe->boneIndex = keyframes[i].boneIndex;
			keyframe->transform = CMatrix::Identity;
			keyframe->time = keyframes[i].time;
			for (auto j = 0; j < 4; j++)
			{
				keyframe->transform.m[j][0] = keyframes[i].transform[j].x;
				keyframe->transform.m[j][1] = keyframes[i].transform[j].y;
				keyframe->transform.m[j][2] = keyframes[i].transform[j].z;
			}
			info->keyframes.push_back(keyframe);
		}
		info->keyFramePtrListArray.resize(512);

		for (auto& keyframe : info->keyframes)
		{
			info->keyFramePtrListArray[keyframe->boneIndex].push_back(keyframe);

		}
		m_animationResource.insert({hash, info});
		return info;
	}
	else
	{
		return map->second;
	}
}