#include "engineStdafx.h"
#include "Skelton.h"


void Skelton::Init()
{
	FILE* fp;
	fp = fopen("Assets/modelData/unity.tks", "rb");
	//骨の数を取得。
	int numBone = 0;
	fread(&numBone, sizeof(numBone), 1, fp);
	for (int i = 0; i < numBone; i++) {
		int nameCount = 0;
		//骨の名前を取得。
		fread(&nameCount, 1, 1, fp);
		std::unique_ptr<char[]> name = std::make_unique<char[]>(nameCount + 1);
		fread(name.get(), nameCount + 1, 1, fp);
		//親のIDを取得。
		int parentId;
		fread(&parentId, sizeof(parentId), 1, fp);
		//バインドポーズを取得。
		Vector3 bindPose[4];
		fread(&bindPose, sizeof(bindPose), 1, fp);
		//バインドポーズの逆数を取得。
		Vector3 invBindPose[4];
		fread(&invBindPose, sizeof(invBindPose), 1, fp);

		//バインドポーズ。
		Matrix bindPoseMatrix;
		memcpy(bindPoseMatrix.m[0], &bindPose[0], sizeof(bindPose[0]));
		memcpy(bindPoseMatrix.m[1], &bindPose[1], sizeof(bindPose[1]));
		memcpy(bindPoseMatrix.m[2], &bindPose[2], sizeof(bindPose[2]));
		memcpy(bindPoseMatrix.m[3], &bindPose[3], sizeof(bindPose[3]));
		bindPoseMatrix.m[0][3] = 0.0f;
		bindPoseMatrix.m[1][3] = 0.0f;
		bindPoseMatrix.m[2][3] = 0.0f;
		bindPoseMatrix.m[3][3] = 1.0f;

		//バインドポーズの逆行列。
		Matrix invBindPoseMatrix;
		memcpy(invBindPoseMatrix.m[0], &invBindPose[0], sizeof(invBindPose[0]));
		memcpy(invBindPoseMatrix.m[1], &invBindPose[1], sizeof(invBindPose[1]));
		memcpy(invBindPoseMatrix.m[2], &invBindPose[2], sizeof(invBindPose[2]));
		memcpy(invBindPoseMatrix.m[3], &invBindPose[3], sizeof(invBindPose[3]));
		invBindPoseMatrix.m[0][3] = 0.0f;
		invBindPoseMatrix.m[1][3] = 0.0f;
		invBindPoseMatrix.m[2][3] = 0.0f;
		invBindPoseMatrix.m[3][3] = 1.0f;

		std::unique_ptr<wchar_t[]> boneName;
		boneName = std::make_unique<wchar_t[]>(256);
		mbstowcs(boneName.get(), name.get(), 256);
		std::unique_ptr<Bone> bone = std::make_unique<Bone>();
		bone->Init(std::move(boneName), i, parentId, bindPoseMatrix, invBindPoseMatrix); 
		m_bones.push_back(std::move(bone));
	}
	fclose(fp);

	for (auto& bone : m_bones)
	{
		if (bone->GetParentID() != -1)
		{
			m_bones[bone->GetParentID()]->AddChildren(bone.get());
			Matrix localMat;
			localMat.Mul(m_bones[bone->GetParentID()]->GetInvMatrix(), bone->GetWorldMatrix());
			bone->SetLocalMatrix(localMat);
		}
		else
		{
			bone->SetLocalMatrix(bone->GetWorldMatrix());
		}
	}

	Update(Matrix::Identity);
}

void Skelton::Update(Matrix mat)
{
	for (auto& bone : m_bones)
	{
		if (bone->GetParentID() != -1)
		{
			continue;
		}
		UpdateWorldMatrix(bone.get(), mat);
	}
}

void Skelton::UpdateWorldMatrix(Bone* bone, Matrix mat)
{
	Matrix mBoneWorld;
	Matrix localMatrix = bone->GetLocalMatrix();
	mBoneWorld.Mul(localMatrix, mat);

	bone->SetWorldMatrix(mBoneWorld);
	for (auto childBone : bone->GetChildren()) {
		UpdateWorldMatrix(childBone, mBoneWorld);
	}
}
