#include "engineStdafx.h"
#include "Animation.h"
#include "Skelton.h"
#include "AnimationClip.h"

void CAnimation::Init(wchar_t* animFilePath[], int animNum)
{
	m_blendRate = 0.0f;
	m_currentAnimationNum = 0;
	m_curCurrentAnimationNum = 0;
	m_animationClips.reset(new CAnimationClip[animNum]);
	for (int i = 0;i < animNum;i++)
	{
		m_animationClips[i].Load(animFilePath[i]);
	}

}

void CAnimation::SetSkelton(CSkelton* skelton)
{
	m_skelton = skelton;
	for (int i = 0; i < m_skelton->GetBoneNum(); i++)
	{
		m_rootBoneID = m_skelton->GetBone(i)->GetParentID();
		if (m_rootBoneID == -1)
		{
			m_rootBoneID = m_skelton->GetBone(i)->GetBoneID();
			break;
		}
	}
}

void CAnimation::Play(int animationNum)
{
	m_curCurrentAnimationNum = m_currentAnimationNum;
	m_currentAnimationNum = animationNum;
	m_animationClips[m_currentAnimationNum].Play();
	m_animationClips[m_curCurrentAnimationNum].Reset();
	BlendAnimationClear();
}

void CAnimation::Play(int animationNum, float interpolationTime)
{
	Play(animationNum);
	m_blendRate = 1.0f;
	m_isInterpolation = true;
	m_interpolationTime = 1.0f / interpolationTime;
}

void CAnimation::AddBlendAnimation(int boneID, int animationNum)
{
	m_animationBlend.push_back({ animationNum, boneID });

}

void CAnimation::UpdateBoneMatrix(int boneID, const std::vector<CMatrix>& localMat1, const std::vector<CMatrix>& localMat2)
{
	const CBone* bone = m_skelton->GetBone(boneID);

	CMatrix boneMat = localMat1[boneID];
	//補間する場合
	if (m_isInterpolation)
	{
		if (0.0f < m_blendRate)
		{
			CMatrix mat1 = localMat1[boneID];
			CMatrix mat2 = localMat2[boneID];
			boneMat.Lerp(m_blendRate, mat1, mat2);
		}
		else
		{
			m_isInterpolation = false;
		}
	}
	m_skelton->SetBoneMatrix(boneID, boneMat);
	for (auto& child : bone->GetChildren())
	{
		UpdateBoneMatrix(child->GetBoneID(), localMat1, localMat2);
	}
}


void CAnimation::Update(float deltaTime)
{

	float progressTime = deltaTime;
	//補間時間を計算
	if (m_isInterpolation)
	{
		progressTime *= m_interpolationTime;
	}
	m_blendRate -=  progressTime;
	//同じアニメーションのアップデートを複数回呼ばないための配列
	std::vector<int> animationUpdateVector;
	for (int i = 0; i < m_animationBlend.size(); i++)
	{
		bool isAnimationUpdate = true;
		for (int animUpdateNum : animationUpdateVector)
		{
			if (animUpdateNum == m_animationBlend[i].animationNum)
			{
				isAnimationUpdate = false;
				break;
			}
		}
		//再生中のアニメーションを更新
		if (isAnimationUpdate)
		{
			m_animationClips[m_animationBlend[i].animationNum].Update(deltaTime);
			m_animationClips[m_animationBlend[i].animationNum].AnimationInvoke(this);
			animationUpdateVector.push_back(m_animationBlend[i].animationNum);
		}
		//再生が終わり、ループフラグが立っていればもう一度再生する
		if (!m_animationClips[m_currentAnimationNum].IsPlay() && m_animationClips[m_currentAnimationNum].IsLoop())
		{
			m_animationClips[m_animationBlend[i].animationNum].Reset();
			m_animationClips[m_animationBlend[i].animationNum].Play();
		}
		const std::vector<CMatrix>& localMatrix = m_animationClips[m_animationBlend[i].animationNum].GetLocalMatrix();
		const std::vector<CMatrix>& localMatrix2 = m_animationClips[m_curCurrentAnimationNum].GetLocalMatrix();
		if (i == 0)
		{
			UpdateBoneMatrix(m_animationBlend[i].boneID, localMatrix, localMatrix2);
		}
		else
		{
			UpdateBoneMatrix(m_animationBlend[i].boneID, localMatrix, localMatrix);
		}
	}
}

