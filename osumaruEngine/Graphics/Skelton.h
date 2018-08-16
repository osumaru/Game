#pragma once

class Bone
{
public:
	Bone();

	void Init(std::unique_ptr<wchar_t[]> boneName, int boneID, int parentID, const Matrix& worldMat, const Matrix& invWorldMat)
	{
		m_boneName = std::move(boneName);
		m_boneID = boneID;
		m_parentID = parentID;
		m_worldMatrix = worldMat;
		m_invMatrix = invWorldMat;
		m_localMatrix = worldMat;
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
};

class Skelton : Uncopyable
{
public:

	Skelton();

	~Skelton();

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
		m_bones[boneIndex]->SetLocalMatrix(mat);
	}

	Matrix GetBoneMatrix(int boneIndex)
	{
		return m_bones[boneIndex]->GetLocalMatrix();
	}


	void Update(Matrix mat);

	void UpdateWorldMatrix(Bone* bone, Matrix mat);

	void Render();

	int GetBoneNum()
	{
		return m_bones.size();
	}
private:
	std::vector<std::unique_ptr<Bone>> m_bones;
	ID3D11Buffer*					m_structuredBuffer;
	ID3D11ShaderResourceView*		m_shaderResourceView;
	std::unique_ptr<Matrix[]> m_boneMat;
};
