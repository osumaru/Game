#include "engineStdafx.h"
#include "Animation.h"
#include "Skelton.h"
#include "AnimationClip.h"

void Animation::Init(std::unique_ptr<AnimationClip[]> animationClip, Skelton* skelton)
{
	m_blendRate = 0.0f;
	m_currentAnimationNum = 0;
	m_curCurrentAnimationNum = 0;
	m_animationClips = std::move(animationClip);
	m_skelton = skelton;
}

void Animation::SetSkelton(Skelton* skelton)
{
}

void Animation::Play(int animationNum)
{
	m_curCurrentAnimationNum = m_currentAnimationNum;
	m_currentAnimationNum = animationNum;
	m_animationClips[m_currentAnimationNum].Play();
}


void Animation::Update()
{
	if (!m_animationClips[m_currentAnimationNum].Update())
	{
		m_animationClips[m_currentAnimationNum].Play();
	}

	std::vector<Matrix> localMatrix = m_animationClips[m_currentAnimationNum].GetLocalMatrix();
	if (0.0f < m_blendRate)
	{
		std::vector<Matrix> localMatrix2 = m_animationClips[m_curCurrentAnimationNum].GetLocalMatrix();
		for (int i = 0;i < m_skelton->GetBoneNum();i++)
		{
			Matrix mat = localMatrix[i];
			Matrix mat2 = localMatrix2[i];
			for (int j = 0;j < 16;j++)
			{
				mat.m[0][j] *= 1.0f - m_blendRate;
				mat2.m[0][j] *= m_blendRate;
				mat.m[0][j] += mat2.m[0][j];
			}
			m_skelton->SetBoneMatrix(i, mat);
		}
		m_blendRate -= GetGameTime().GetDeltaFrameTime();
	}
	else
	{
		for (int i = 0;i < m_skelton->GetBoneNum();i++)
		{
			m_skelton->SetBoneMatrix(i, localMatrix[i]);
		}
	}

	//static bool flg = true;
	//static bool flg2 = true;
	//static float flg2count = 0.0f;
	//if (flg)
	//{
	//	if (flg2)
	//	{
	//		flg2count += 0.1f;
	//		if (flg2count >= 10.0f)
	//		{
	//			flg2count = 0.0f;
	//			flg2 = false;
	//		}
	//	}
	//	else
	//	{
	//		m_blendRate += 0.01f;
	//		if (m_blendRate >= 1.0f)
	//		{
	//			flg = !flg;
	//			flg2 = true;
	//			m_blendRate = 1.0f;
	//		}
	//	}
	//}
	//else
	//{
	//	if (flg2)
	//	{
	//		flg2count += 0.1f;
	//		if (flg2count >= 10.0f)
	//		{
	//			flg2count = 0.0f;
	//			flg2 = false;
	//		}
	//	}
	//	else
	//	{
	//		m_blendRate -= 0.01f;
	//		if (m_blendRate <= 0.0f)
	//		{
	//			flg = !flg;
	//			flg2 = true;
	//			m_blendRate = 0.0f;

	//		}
	//	}
	//}

	//m_frameTime += GetGameTime().GetDeltaFrameTime();
	//if ((*m_topBoneKeyFrameList)[m_currentFrameNo]->time < m_frameTime )
	//{
	//	for (auto& keyframe : m_keyFramePtrListArray)
	//	{
	//		if (!keyframe.empty())
	//		{
	//			m_skelton->SetBoneMatrix(keyframe[m_currentFrameNo]->boneIndex, keyframe[m_currentFrameNo]->transform);
	//		}
	//	}
	//	m_currentFrameNo++;
	//	if (m_topBoneKeyFrameList->size() <= m_currentFrameNo)
	//	{
	//		m_currentFrameNo = 0;
	//	}
	//	m_frameTime = 0.0f;
	//}

	//m_frameTime2 += GetGameTime().GetDeltaFrameTime();
	//if ((*m_topBoneKeyFrameList2)[m_currentFrameNo2]->time < m_frameTime2)
	//{
	//	for (auto& keyframe : m_keyFramePtrListArray2)
	//	{
	//		if (!keyframe.empty())
	//		{
	//			Matrix mat = m_skelton->GetBoneMatrix(keyframe[m_currentFrameNo2]->boneIndex);
	//			Matrix mat2 = keyframe[m_currentFrameNo2]->transform;
	//			mat.m[0][0] = mat.m[0][0] * m_blendRate;
	//			mat.m[0][1] = mat.m[0][1] * m_blendRate;
	//			mat.m[0][2] = mat.m[0][2] * m_blendRate;
	//			mat.m[0][3] = mat.m[0][3] * m_blendRate;
	//			mat.m[1][0] = mat.m[1][0] * m_blendRate;
	//			mat.m[1][1] = mat.m[1][1] * m_blendRate;
	//			mat.m[1][2] = mat.m[1][2] * m_blendRate;
	//			mat.m[1][3] = mat.m[1][3] * m_blendRate;
	//			mat.m[2][0] = mat.m[2][0] * m_blendRate;
	//			mat.m[2][1] = mat.m[2][1] * m_blendRate;
	//			mat.m[2][2] = mat.m[2][2] * m_blendRate;
	//			mat.m[2][3] = mat.m[2][3] * m_blendRate;
	//			mat.m[3][0] = mat.m[3][0] * m_blendRate;
	//			mat.m[3][1] = mat.m[3][1] * m_blendRate;
	//			mat.m[3][2] = mat.m[3][2] * m_blendRate;
	//			mat.m[3][3] = mat.m[3][3] * m_blendRate;
	//			mat2.m[0][0] = mat2.m[0][0] * (1.0f - m_blendRate);
	//			mat2.m[0][1] = mat2.m[0][1] * (1.0f - m_blendRate);
	//			mat2.m[0][2] = mat2.m[0][2] * (1.0f - m_blendRate);
	//			mat2.m[0][3] = mat2.m[0][3] * (1.0f - m_blendRate);
	//			mat2.m[1][0] = mat2.m[1][0] * (1.0f - m_blendRate);
	//			mat2.m[1][1] = mat2.m[1][1] * (1.0f - m_blendRate);
	//			mat2.m[1][2] = mat2.m[1][2] * (1.0f - m_blendRate);
	//			mat2.m[1][3] = mat2.m[1][3] * (1.0f - m_blendRate);
	//			mat2.m[2][0] = mat2.m[2][0] * (1.0f - m_blendRate);
	//			mat2.m[2][1] = mat2.m[2][1] * (1.0f - m_blendRate);
	//			mat2.m[2][2] = mat2.m[2][2] * (1.0f - m_blendRate);
	//			mat2.m[2][3] = mat2.m[2][3] * (1.0f - m_blendRate);
	//			mat2.m[3][0] = mat2.m[3][0] * (1.0f - m_blendRate);
	//			mat2.m[3][1] = mat2.m[3][1] * (1.0f - m_blendRate);
	//			mat2.m[3][2] = mat2.m[3][2] * (1.0f - m_blendRate);
	//			mat2.m[3][3] = mat2.m[3][3] * (1.0f - m_blendRate);
	//			mat.m[0][0] = mat.m[0][0] + mat2.m[0][0];
	//			mat.m[0][1] = mat.m[0][1] + mat2.m[0][1];
	//			mat.m[0][2] = mat.m[0][2] + mat2.m[0][2];
	//			mat.m[0][3] = mat.m[0][3] + mat2.m[0][3];
	//			mat.m[1][0] = mat.m[1][0] + mat2.m[1][0];
	//			mat.m[1][1] = mat.m[1][1] + mat2.m[1][1];
	//			mat.m[1][2] = mat.m[1][2] + mat2.m[1][2];
	//			mat.m[1][3] = mat.m[1][3] + mat2.m[1][3];
	//			mat.m[2][0] = mat.m[2][0] + mat2.m[2][0];
	//			mat.m[2][1] = mat.m[2][1] + mat2.m[2][1];
	//			mat.m[2][2] = mat.m[2][2] + mat2.m[2][2];
	//			mat.m[2][3] = mat.m[2][3] + mat2.m[2][3];
	//			mat.m[3][0] = mat.m[3][0] + mat2.m[3][0];
	//			mat.m[3][1] = mat.m[3][1] + mat2.m[3][1];
	//			mat.m[3][2] = mat.m[3][2] + mat2.m[3][2];
	//			mat.m[3][3] = mat.m[3][3] + mat2.m[3][3];
	//			m_skelton->SetBoneMatrix(keyframe[m_currentFrameNo2]->boneIndex, mat);
	//		}
	//	}


	//	m_currentFrameNo2++;
	//	if (m_topBoneKeyFrameList2->size() <= m_currentFrameNo2)
	//	{
	//		m_currentFrameNo2 = 0;
	//	}
	//	m_frameTime2 = 0.0f;
	//}

}

