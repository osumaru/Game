#pragma once
//骨クラス

class CBone
{
public:
	/*
	引数付きコンストラクタ
	boneName	骨の名前
	boneId		骨の番号
	parentID	親の骨の番号
	worldMat	バインドポーズ行列
	invWorldMat	バインドポーズの逆行列
	*/
	CBone(std::unique_ptr<wchar_t[]> boneName, int boneID, int parentID, const CMatrix& worldMat, const CMatrix& invWorldMat);
	
	/*
	子共を追加
	children	子共の骨
	*/
	void AddChildren(CBone* children)
	{
		m_boneChilds.push_back(children);
	}

	//子共の骨を取得。
	const std::vector<CBone*>& GetChildren() const
	{
		return m_boneChilds;
	}

	/*
	親の骨の番号を取得
	*/
	int GetParentID() const
	{
		return m_parentID;
	}

	//ローカル行列を取得
	const CMatrix& GetLocalMatrix() const
	{
		return m_localMatrix;
	}
	
	//ローカル行列を設定
	void SetLocalMatrix(const CMatrix& localMatrix)
	{
		m_localMatrix = localMatrix;
	}

	//ワールド行列を取得
	const CMatrix& GetWorldMatrix() const
	{
		return m_worldMatrix;
	}

	//ワールド行列を設定
	void SetWorldMatrix(const CMatrix& worldMatrix)
	{
		m_worldMatrix = worldMatrix;
	}

	//バインドポーズの逆行列を取得
	const CMatrix& GetInvMatrix() const
	{
		return m_invMatrix;
	}
	
	/*
	骨の名前を取得
	*/
	const wchar_t* GetBoneName() const
	{
		return m_boneName.get();
	}
	
	/*
	骨の番号を取得
	*/
	int GetBoneID() const
	{
		return m_boneID;
	}


private:
	std::unique_ptr<wchar_t[]> m_boneName;	//骨の名前
	int m_boneID;							//骨の番号
	int m_parentID;							//親の骨の番号
	CMatrix m_localMatrix;					//ローカル行列
	CMatrix m_worldMatrix;					//ワールド行列
	CMatrix m_invMatrix;					//バインドボーズの逆行列
	std::vector<CBone*> m_boneChilds;		//子供

};

//スケルトン行列
class CSkelton : Uncopyable
{
public:

	//コンストラクタ
	CSkelton();

	//デストラクタ
	~CSkelton();

	/*
	スケルトンの読み込み
	filePath	ファイルパス
	ret			成功したか？
	*/
	bool Load(const wchar_t* filePath);

	/*
	骨の名前から骨の番号を取得
	boneName	骨の名前
	ret			骨の番号
	*/
	int FindBoneID(const wchar_t* boneName) const
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

	/*
	骨のローカル行列を設定
	boneIndex	行列を設定する骨の番号
	mat			ローカル行列
	*/
	void SetBoneMatrix(int boneIndex, const CMatrix& mat)
	{
		m_bones[boneIndex]->SetLocalMatrix(mat);
	}

	/*
	骨の行列を取得
	*/
	const CMatrix& GetBoneMatrix(int boneIndex) const
	{
		return m_bones[boneIndex]->GetLocalMatrix();
	}

	/*
	行列を更新
	mat		ワールド行列
	*/
	void Update(const CMatrix& mat);

	//描画
	void Render();

	//骨の数を取得
	int GetBoneNum() const
	{
		return m_bones.size();
	}

	/*
	骨を検索する機能
	boneName	探す骨の名前
	ret			見つかった骨のインスタンスを返す、見つからなかったらnullを返す
	*/
	const CBone* FindBone(const wchar_t* boneName) const
	{
		for (int i = 0; i < m_bones.size(); i++)
		{
			if (!wcscmp(m_bones[i]->GetBoneName(), boneName))
			{
				return m_bones[i].get();
			}
		}
		return nullptr;
	}

private:

	/*
	ワールド行列の更新
	bone		骨
	mat			ワールド行列
	*/
	void UpdateWorldMatrix(CBone* bone, const CMatrix& mat);

private:
	std::vector<std::unique_ptr<CBone>>		m_bones;				//骨達
	ID3D11Buffer*							m_structuredBuffer;		//ストラクチャードバッファ
	ID3D11ShaderResourceView*				m_shaderResourceView;	//SRV
	std::unique_ptr<CMatrix[]>				m_boneMat;				//骨の行列
};
