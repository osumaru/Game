#pragma once

class Skelton;

/*!
*@brief	アニメーションクリップのヘッダー。
*/
struct AnimClipHeader {
	std::uint32_t numKey;				//!<キーフレームの数。
	std::uint32_t numAnimationEvent;	//!<アニメーションイベントの数。
};
/*!
*@brief	アニメーションイベント
*/
struct AnimationEvent {
	float	invokeTime;					//!<アニメーションイベントが発生する時間(単位:秒)
	std::uint32_t eventNameLength;		//!<イベント名の長さ。
};
/*!
*@brief	キーフレーム。
*/
struct Keyframe {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	Matrix transform;			//!<トランスフォーム。
};
/*!
*@brief	キーフレーム。
*/
struct KeyframeRow {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	Vector3 transform[4];		//!<トランスフォーム。
};

class Animation 
{
public:

	void Init(Skelton* skelton, wchar_t* filePath);

	void Update();

private:
	Skelton* m_skelton;
	std::wstring m_clipName;	//!<アニメーションクリップの名前。
	std::vector<std::unique_ptr<Keyframe>>			m_keyframes;				//キーフレーム。
	std::vector<std::vector<Keyframe*>> m_keyFramePtrListArray;
	std::vector<Keyframe*>* m_topBoneKeyFramList;
	int	m_currentFrameNo;
	int m_count;
};