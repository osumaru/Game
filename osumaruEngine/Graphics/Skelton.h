#pragma once

class Bone
{
public:
	Bone()
	{
		
	}

	void Init(std::unique_ptr<wchar_t[]> boneName, int boneID, int parentID, const Matrix& worldMat, const Matrix& invWorldMat)
	{
		m_boneName = std::move(boneName);
		m_boneID = boneID;
		m_parentID = parentID;
		m_worldMatrix = worldMat;
		m_invMatrix = invWorldMat;
		m_localMatrix = worldMat;
		m_animMatrix = Matrix::Identity;
	}
	void AddChildren(Bone* children)
	{
		m_boneChilds.push_back(children);
	}

	std::vector<Bone*>& GetChildren()
	{
		return m_boneChilds;
	}

	int GetParentID()
	{
		return m_parentID;
	}

	Matrix GetLocalMatrix()
	{
		return m_localMatrix;
	}

	void SetLocalMatrix(Matrix localMatrix)
	{
		m_localMatrix = localMatrix;
	}

	Matrix GetWorldMatrix()
	{
		return m_worldMatrix;
	}

	void SetWorldMatrix(Matrix worldMatrix)
	{
		m_worldMatrix = worldMatrix;
	}

	void SetAnimationMatrix(Matrix mat)
	{
		m_animMatrix = mat;
	}

	Matrix GetAnimationMatrix()
	{
		return m_animMatrix;
	}

	void SetInvMatrix(Matrix invMatrix)
	{
		m_invMatrix = invMatrix;
	}

	Matrix GetInvMatrix()
	{
		return m_invMatrix;
	}

	wchar_t* GetBoneName()
	{
		return m_boneName.get();
	}

	int GetBoneID()
	{
		return m_boneID;
	}


private:
	std::unique_ptr<wchar_t[]> m_boneName;
	int m_boneID;
	int m_parentID;
	Matrix m_localMatrix;
	Matrix m_worldMatrix;
	Matrix m_invMatrix;
	std::vector<Bone*> m_boneChilds;
	Matrix m_animMatrix;
};

class Skelton
{
public:

	bool Load(wchar_t* filePath);

	int FindBoneID(const wchar_t* boneName)
	{
		for (auto& bone : m_bones)
		{
			if (!wcscmp(bone->GetBoneName(), boneName))
			{
				return bone->GetBoneID();
			}
		}
		return -1;
	}

	void SetBoneMatrix(int boneIndex, Matrix mat)
	{
		Matrix multi;
		multi.Mul(mat, m_bones[boneIndex]->GetInvMatrix());
		m_bones[boneIndex]->SetAnimationMatrix(multi);
	}


	void Update(Matrix mat);

	void UpdateWorldMatrix(Bone* bone, Matrix mat);

	void Render();
private:
	std::vector<std::unique_ptr<Bone>> m_bones;
	ID3D11Buffer*					m_structuredBuffer;
	ID3D11ShaderResourceView*		m_shaderResourceView;
	std::unique_ptr<Matrix[]> m_boneMat;
};
