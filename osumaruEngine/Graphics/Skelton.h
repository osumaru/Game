#pragma once
//骨クラス

class CBone
{
public:
	//コンストラクタ
	CBone(std::unique_ptr<wchar_t[]> boneName, int boneID, int parentID, const Matrix& worldMat, const Matrix& invWorldMat);

	void AddChildren(CBone* children)
	{
		m_boneChilds.push_back(children);
	}

	std::vector<CBone*>& GetChildren()
	{
		return m_boneChilds;
	}

	int GetParentID()
	{
		return m_parentID;
	}

	CMatrix GetLocalMatrix()
	{
		return m_localMatrix;
	}

	void SetLocalMatrix(CMatrix localMatrix)
	{
		m_localMatrix = localMatrix;
	}

	CMatrix GetWorldMatrix()
	{
		return m_worldMatrix;
	}

	void SetWorldMatrix(CMatrix worldMatrix)
	{
		m_worldMatrix = worldMatrix;
	}

	CMatrix GetInvMatrix()
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
	CMatrix m_localMatrix;
	CMatrix m_worldMatrix;
	CMatrix m_invMatrix;
	std::vector<CBone*> m_boneChilds;
};

class CSkelton : Uncopyable
{
public:

	CSkelton();

	~CSkelton();

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

	void SetBoneMatrix(int boneIndex, CMatrix mat)
	{
		m_bones[boneIndex]->SetLocalMatrix(mat);
	}

	CMatrix GetBoneMatrix(int boneIndex)
	{
		return m_bones[boneIndex]->GetLocalMatrix();
	}


	void Update(CMatrix mat);

	void UpdateWorldMatrix(CBone* bone, CMatrix mat);

	void Render();

	int GetBoneNum()
	{
		return m_bones.size();
	}
private:
	std::vector<std::unique_ptr<CBone>> m_bones;
	ID3D11Buffer*					m_structuredBuffer;
	ID3D11ShaderResourceView*		m_shaderResourceView;
	std::unique_ptr<CMatrix[]> m_boneMat;
};
