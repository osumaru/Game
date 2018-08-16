#pragma once
#include "AnimationClip.h"
class Skelton;



class Animation : Uncopyable
{
public:

	void Init(std::unique_ptr<AnimationClip[]> animationClip, Skelton* skelton);

	void SetSkelton(Skelton* skelton);

	void Update();

	void Play(int animationNum);

	//void Play
private:
	std::unique_ptr<AnimationClip[]> m_animationClips;
	int m_currentAnimationNum;
	int m_curCurrentAnimationNum;
	Skelton* m_skelton;
	float m_blendRate;
	bool m_isInterpolation;
};