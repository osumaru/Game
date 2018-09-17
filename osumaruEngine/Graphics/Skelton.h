#pragma once
//���N���X

class CBone
{
public:
	/*
	�����t���R���X�g���N�^
	boneName	���̖��O
	boneId		���̔ԍ�
	parentID	�e�̍��̔ԍ�
	worldMat	�o�C���h�|�[�Y�s��
	invWorldMat	�o�C���h�|�[�Y�̋t�s��
	*/
	CBone(std::unique_ptr<wchar_t[]> boneName, int boneID, int parentID, const CMatrix& worldMat, const CMatrix& invWorldMat);
	
	/*
	�q����ǉ�
	children	�q���̍�
	*/
	void AddChildren(CBone* children)
	{
		m_boneChilds.push_back(children);
	}

	//�q���̍����擾�B
	const std::vector<CBone*>& GetChildren() const
	{
		return m_boneChilds;
	}

	/*
	�e�̍��̔ԍ����擾
	*/
	int GetParentID() const
	{
		return m_parentID;
	}

	//���[�J���s����擾
	const CMatrix& GetLocalMatrix() const
	{
		return m_localMatrix;
	}
	
	//���[�J���s���ݒ�
	void SetLocalMatrix(const CMatrix& localMatrix)
	{
		m_localMatrix = localMatrix;
	}

	//���[���h�s����擾
	const CMatrix& GetWorldMatrix() const
	{
		return m_worldMatrix;
	}

	//���[���h�s���ݒ�
	void SetWorldMatrix(const CMatrix& worldMatrix)
	{
		m_worldMatrix = worldMatrix;
	}

	//�o�C���h�|�[�Y�̋t�s����擾
	const CMatrix& GetInvMatrix() const
	{
		return m_invMatrix;
	}
	
	/*
	���̖��O���擾
	*/
	const wchar_t* GetBoneName() const
	{
		return m_boneName.get();
	}
	
	/*
	���̔ԍ����擾
	*/
	int GetBoneID() const
	{
		return m_boneID;
	}


private:
	std::unique_ptr<wchar_t[]> m_boneName;	//���̖��O
	int m_boneID;							//���̔ԍ�
	int m_parentID;							//�e�̍��̔ԍ�
	CMatrix m_localMatrix;					//���[�J���s��
	CMatrix m_worldMatrix;					//���[���h�s��
	CMatrix m_invMatrix;					//�o�C���h�{�[�Y�̋t�s��
	std::vector<CBone*> m_boneChilds;		//�q��

};

//�X�P���g���s��
class CSkelton : Uncopyable
{
public:

	//�R���X�g���N�^
	CSkelton();

	//�f�X�g���N�^
	~CSkelton();

	/*
	�X�P���g���̓ǂݍ���
	filePath	�t�@�C���p�X
	ret			�����������H
	*/
	bool Load(const wchar_t* filePath);

	/*
	���̖��O���獜�̔ԍ����擾
	boneName	���̖��O
	ret			���̔ԍ�
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
	���̃��[�J���s���ݒ�
	boneIndex	�s���ݒ肷�鍜�̔ԍ�
	mat			���[�J���s��
	*/
	void SetBoneMatrix(int boneIndex, const CMatrix& mat)
	{
		m_bones[boneIndex]->SetLocalMatrix(mat);
	}

	/*
	���̍s����擾
	*/
	const CMatrix& GetBoneMatrix(int boneIndex) const
	{
		return m_bones[boneIndex]->GetLocalMatrix();
	}

	/*
	�s����X�V
	mat		���[���h�s��
	*/
	void Update(const CMatrix& mat);

	//�`��
	void Render();

	//���̐����擾
	int GetBoneNum() const
	{
		return m_bones.size();
	}

	/*
	������������@�\
	boneName	�T�����̖��O
	ret			�����������̃C���X�^���X��Ԃ��A������Ȃ�������null��Ԃ�
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
	���[���h�s��̍X�V
	bone		��
	mat			���[���h�s��
	*/
	void UpdateWorldMatrix(CBone* bone, const CMatrix& mat);

private:
	std::vector<std::unique_ptr<CBone>>		m_bones;				//���B
	ID3D11Buffer*							m_structuredBuffer;		//�X�g���N�`���[�h�o�b�t�@
	ID3D11ShaderResourceView*				m_shaderResourceView;	//SRV
	std::unique_ptr<CMatrix[]>				m_boneMat;				//���̍s��
};
