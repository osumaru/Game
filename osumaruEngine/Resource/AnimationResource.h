#pragma once
#include "../Graphics/AnimationClip.h"

struct SAnimationClipInfo
{
	const wchar_t*							filePath = nullptr;				//アニメーションクリップの名前。
	std::vector<SKeyframe*>					keyframes;						//キーフレーム。
	CAnimationEvent*						animationEvent = nullptr;			//アニメーションイベント。
	int										animationEventNum = 0;			//アニメーションイベントの数
	std::vector<std::vector<SKeyframe*>>	keyFramePtrListArray;				//ボーン毎のキーフレームのリスト
};

class CAnimationResource : Uncopyable
{
public:

	const SAnimationClipInfo* Load(const wchar_t* clipName);

private:
	std::map<int, const SAnimationClipInfo*> m_animationResource;
};