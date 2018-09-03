#pragma once
#include "AnimationClip.h"
class CSkelton;
//アニメーションを管理するクラス

class CAnimation : Uncopyable
{
public:

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

private:
	std::unique_ptr<CAnimationClip[]>	m_animationClips = nullptr;		//アニメーションクリップの配列
	int									m_currentAnimationNum = 0;		//今再生しているアニメーションの番号
	int									m_curCurrentAnimationNum = 0;	//ひとつ前に再生していたアニメーションの番号
	CSkelton*							m_skelton = nullptr;			//スケルトンの番号
	float								m_blendRate = 0.0f;				//アニメーション補間時のレート
	bool								m_isInterpolation = false;		//補間しているか？
	float								m_interpolationTime = 1.0f;		//アニメーション補間時の経過させる時間
};