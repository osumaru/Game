#include "engineStdafx.h"
#include "Animation.h"
#include "Skelton.h"
#include "AnimationClip.h"

void CAnimation::Init(wchar_t* animFilePath[], int animNum)
{
	m_blendRate = 0.0f;
	m_currentAnimationNum = 0;
	m_curCurrentAnimationNum = 0;
	m_animationClips.reset(new AnimationClip[animNum]);
	for (int i = 0;i < animNum;i++)
	{
		m_animationClips[i].Load(animFilePath[i]);
	}
}

void CAnimation::SetSkelton(CSkelton* skelton)
{
	m_skelton = skelton;
}

void CAnimation::Play(int animationNum)
{
	m_curCurrentAnimationNum = m_currentAnimationNum;
	m_currentAnimationNum = animationNum;
	m_animationClips[m_currentAnimationNum].Play();
}

void CAnimation::Play(int animationNum, float interpolationTime)
{
	Play(animationNum);
	m_blendRate = 1.0f;
	m_isInterpolation = true;
	m_interpolationTime = 1.0f / interpolationTime;
}


void CAnimation::Update(float deltaTime)
{
	m_animationClips[m_currentAnimationNum].Update(deltaTime);
	if (!m_animationClips[m_currentAnimationNum].IsPlay() && m_animationClips[m_currentAnimationNum].IsLoop())
	{
		m_animationClips[m_currentAnimationNum].Play();
	}

	std::vector<CMatrix> localMatrix = m_animationClips[m_currentAnimationNum].GetLocalMatrix();
	std::vector<CMatrix> localMatrix2 = m_animationClips[m_curCurrentAnimationNum].GetLocalMatrix();

	float progressTime = deltaTime;
	if (m_isInterpolation)
	{
		progressTime *= m_interpolationTime;
	}
	m_blendRate -=  progressTime;
	for (int i = 0;i < m_skelton->GetBoneNum();i++)
	{
		CMatrix boneMat = localMatrix[i];
		if (m_isInterpolation)
		{
			if (0.0f < m_blendRate)
			{
				CMatrix mat = localMatrix[i];
				CMatrix mat2 = localMatrix2[i];
				for (int j = 0;j < 16;j++)
				{
					mat.m[0][j] *= 1.0f - m_blendRate;
					mat2.m[0][j] *= m_blendRate;
					mat.m[0][j] += mat2.m[0][j];
				}
				boneMat = mat;

			}
			else
			{
				m_isInterpolation = false;
			}
		}
		m_skelton->SetBoneMatrix(i, boneMat);
	}

}

