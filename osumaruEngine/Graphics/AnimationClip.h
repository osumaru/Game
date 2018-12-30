#pragma once
#include "AnimationEvent.h"
class CSkelton;
class CKeyframe;
class CAnimation;

/*!
*@brief	アニメーションクリップのヘッダー。
*/
struct SAnimClipHeader {
	std::uint32_t numKey;				//!<キーフレームの数。
	std::uint32_t numAnimationEvent;	//!<アニメーションイベントの数。
};
/*!
*@brief	アニメーションイベント
*/
struct SAnimationEvent {
	float	invokeTime;					//!<アニメーションイベントが発生する時間(単位:秒)
	std::uint32_t eventNameLength;		//!<イベント名の長さ。
};
/*!
*@brief	キーフレーム。
*/
struct SKeyframe {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	CMatrix transform;			//!<トランスフォーム。
};
/*!
*@brief	キーフレーム。
*/
struct SKeyframeRow {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	CVector3 transform[4];		//!<トランスフォーム。
};

struct SBoneFreeze
{
	bool isFreezeX = false;
	bool isFreezeY = false;
	bool isFreezeZ = false;
};

//アニメーションクリップ(一つのアニメーションを管理するクラス)

class CAnimationClip : Uncopyable
{
public:
	/*
	アニメーションを読み込む関数。
	filePath	アニメーションファイルのパス
	*/
	void Load(wchar_t* filePath);


	//更新関数。
	void Update(float deltaTime);

	//ボーンの行列を取得。
	const std::vector<CMatrix>& GetLocalMatrix() const
	{
		return m_localMatrix;
	}

	//アニメーションを再生。
	void Play();

	//ループフラグを設定。
	void SetIsLoop(bool isLoop)
	{
		m_isLoop = isLoop;
	}

	//ループフラグを取得。
	bool IsLoop() const
	{
		return m_isLoop;
	}

	//再生中かのフラグを取得。
	bool IsPlay() const
	{
		return m_isPlay;
	}

	//アニメーションイベントの更新
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
	bool									m_isPlay = false;					//再生中か？
	bool									m_isLoop = false;					//ループしてるか？
	const wchar_t*							m_clipName = nullptr;				//アニメーションクリップの名前。
	std::vector<SKeyframe*>					m_keyframes;						//キーフレーム。
	std::vector<std::vector<SKeyframe*>>	m_keyFramePtrListArray;				//ボーン毎のキーフレームのリスト
	std::vector<SKeyframe*>*				m_topBoneKeyFrameList = nullptr;	//一番最初のキーフレーム
	std::vector<CMatrix>					m_localMatrix;						//ボーンの行列を保存するためのもの
	std::vector<SBoneFreeze>				m_freezeFlg;						//ボーンの行列を保存するためのもの
	float									m_frameTime = 0.0f;					//フレームを進めるためのタイマー
	int										m_currentFrameNo = 0;				//現在のフレームナンバー
	CAnimationEvent*						m_animationEvent = nullptr;			//アニメーションイベント。
	int										m_animationEventNum = 0;			//アニメーションイベントの数
	int										m_maxFrameNum = 0;					//最大キーフレーム数
};