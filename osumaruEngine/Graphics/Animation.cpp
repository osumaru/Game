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
	//再生中のアニメーションを更新
	m_animationClips[m_currentAnimationNum].Update(deltaTime);
	m_animationClips[m_curCurrentAnimationNum].AnimationInvoke(this);
	//再生が終わり、ループフラグが立っていればもう一度再生する
	if (!m_animationClips[m_currentAnimationNum].IsPlay() && m_animationClips[m_currentAnimationNum].IsLoop())
	{
		m_animationClips[m_currentAnimationNum].Play();
	}

	std::vector<CMatrix> localMatrix = m_animationClips[m_currentAnimationNum].GetLocalMatrix();
	std::vector<CMatrix> localMatrix2 = m_animationClips[m_curCurrentAnimationNum].GetLocalMatrix();

	float progressTime = deltaTime;
	//補間時間を計算
	if (m_isInterpolation)
	{
		progressTime *= m_interpolationTime;
	}
	m_blendRate -=  progressTime;

	for (int i = 0;i < m_skelton->GetBoneNum();i++)
	{
		CMatrix boneMat = localMatrix[i];
		//補間する場合
		if (m_isInterpolation)
		{
			if (0.0f < m_blendRate)
			{
				CMatrix mat1 = localMatrix[i];
				CMatrix mat2 = localMatrix2[i];
				CVector3 scale1;
				scale1.x = ((CVector3*)mat1.m[0])->Length();
				scale1.y = ((CVector3*)mat1.m[1])->Length();
				scale1.z = ((CVector3*)mat1.m[2])->Length();
				mat1.m[0][0] /= scale1.x;
				mat1.m[0][1] /= scale1.x;
				mat1.m[0][2] /= scale1.x;
				mat1.m[1][0] /= scale1.y;
				mat1.m[1][1] /= scale1.y;
				mat1.m[1][2] /= scale1.y;
				mat1.m[2][0] /= scale1.z;
				mat1.m[2][1] /= scale1.z;
				mat1.m[2][2] /= scale1.z;
				CVector3 scale2;
				scale2.x = ((CVector3*)mat2.m[0])->Length();
				scale2.y = ((CVector3*)mat2.m[1])->Length();
				scale2.z = ((CVector3*)mat2.m[2])->Length();
				mat2.m[0][0] /= scale2.x;
				mat2.m[0][1] /= scale2.x;
				mat2.m[0][2] /= scale2.x;
				mat2.m[1][0] /= scale2.y;
				mat2.m[1][1] /= scale2.y;
				mat2.m[1][2] /= scale2.y;
				mat2.m[2][0] /= scale2.z;
				mat2.m[2][1] /= scale2.z;
				mat2.m[2][2] /= scale2.z;
				CQuaternion rot1;
				rot1.SetRotation(mat1);
				CQuaternion rot2;
				rot2.SetRotation(mat2);
				rot1.Slerp(m_blendRate, rot1, rot2);
				CVector3 pos1;
				pos1.x = mat1.m[3][0];
				pos1.y = mat1.m[3][1];
				pos1.z = mat1.m[3][2];
				CVector3 pos2;
				pos2.x = mat2.m[3][0];
				pos2.y = mat2.m[3][1];
				pos2.z = mat2.m[3][2];
				scale1.Lerp(m_blendRate, scale1, scale2);
				pos1.Lerp(m_blendRate, pos1, pos2);
				CMatrix transMat;
				transMat.MakeTranslation(pos1);
				CMatrix rotMat;
				rotMat.MakeRotationFromQuaternion(rot1);
				CMatrix scaleMat;
				scaleMat.MakeScaling(scale1);
				boneMat = CMatrix::Identity;
				boneMat.Mul(boneMat, scaleMat);
				boneMat.Mul(boneMat, rotMat);
				boneMat.Mul(boneMat, transMat);
			}
			else
			{
				m_isInterpolation = false;
			}
		}
		m_skelton->SetBoneMatrix(i, boneMat);
	}

}

