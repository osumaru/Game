#pragma once
#include "AnimationClip.h"
class CSkelton;
//アニメーションを管理するクラス

class CAnimation : Uncopyable
{
public:
	using AnimationEventListener = std::function<void(const wchar_t* clipName, const wchar_t* eventName)>;
	/*
	初期化関数
	animFilePath	アニメーションのファイルパスの配列
	animNum			アニメーションの数
	*/
	void Init(wchar_t* animFilePath[], int animNum);

	//スケルトンを設定
	void SetSkelton(CSkelton* skelton);

	/*
	更新関数
	deltaTime	進める時間
	*/
	void Update(float deltaTime);


	/*
	アニメーション再生関数
	animationNum	再生するアニメーションの番号
	*/
	void Play(int animationNum);

	/*
	補間しながらアニメーションを再生する関数
	animationNum	再生するアニメーションの番号
	interpolationTime	補間する時間
	*/
	void Play(int animationNum, float interpolationTime);

	/*
	アニメーションのループフラグを設定
	animationNum	フラグを設定するアニメーションの番号
	isLoop			ループするかのフラグ
	*/
	void SetLoopFlg(int animationNum, bool isLoop)
	{
		m_animationClips[animationNum].SetIsLoop(isLoop);
	}

	//アニメーションを再生しているか？
	bool IsPlay() const
	{
		return	m_animationClips[m_currentAnimationNum].IsPlay();
	}

	//補完しているかのフラグを取得
	bool IsInterpolation() const
	{
		return m_isInterpolation;
	}

	//現在再生してるアニメーションの番号を取得
	int GetCurrentAnimationNum() const
	{
		return m_currentAnimationNum;
	}

	//イベントリスナーを追加
	void AddAnimationEvent(AnimationEventListener animEvent)
	{
		m_animationEventListener.push_back(animEvent);
	}

	/*
	アニメーションイベントの通知
	clipName	アニメーションクリップの名前
	eventName	アニメーションイベントの名前
	*/
	void AnimationEventNotification(const wchar_t* clipName, const wchar_t* eventName)
	{
		for (auto& animEvent : m_animationEventListener)
		{
			animEvent(clipName, eventName);
		}
	}

	/*
	アニメーションブレンドをさせたいボーンを追加
	boneID		アニメーションブレンドさせたい骨の番号
	animationNum	アニメーションの番号
	*/
	void AddBlendAnimation(int boneID, int animationNum);


	/*
	ブレンドしてるアニメーションの数を取得
	*/
	int GetBlendAnimationNum() const
	{
		return m_animationBlend.size();
	}

	//アニメーションブレンドをクリア
	void BlendAnimationClear()
	{
		m_animationBlend.clear();
		m_animationBlend.push_back({ m_currentAnimationNum, m_rootBoneID });
	}

	//ボーンの行列を更新
	void UpdateBoneMatrix(int boneID, const std::vector<CMatrix>& localMat1, const std::vector<CMatrix>& localMat2);

	void SetIsLenearInterpolation(bool isLenearInterpolation)
	{
		for(int i = 0;i < m_animationNum;i++)
		{
			m_animationClips[i].SetIsLinearInterpolation(isLenearInterpolation);
		}
	}
	
	//アニメーションブレンドに使う情報
	struct SAnimationBlendInfo
	{
		int animationNum;	//再生するアニメーション
		int boneID;			//アニメーションを切り替える骨のID
	};

private:
	int									m_rootBoneID;
	std::vector<SAnimationBlendInfo>	m_animationBlend;
	std::unique_ptr<CAnimationClip[]>	m_animationClips = nullptr;		//アニメーションクリップの配列
	int									m_currentAnimationNum = 0;		//今再生しているアニメーションの番号
	int									m_curCurrentAnimationNum = 0;	//ひとつ前に再生していたアニメーションの番号
	CSkelton*							m_skelton = nullptr;			//スケルトンの番号
	float								m_blendRate = 0.0f;				//アニメーション補間時のレート
	bool								m_isInterpolation = false;		//補間しているか？
	float								m_interpolationTime = 1.0f;		//アニメーション補間時の経過させる時間
	std::vector<AnimationEventListener>	m_animationEventListener;
	int									m_animationNum;					//アニメーションの数

};