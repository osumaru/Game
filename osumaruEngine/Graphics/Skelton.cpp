#include "Skelton.h"


CBone::CBone(std::unique_ptr<wchar_t[]> boneName, int boneID, int parentID, const CMatrix& worldMat, const CMatrix& invWorldMat) :
	m_boneName(std::move(boneName)),
	m_boneID(boneID),
	m_parentID(parentID),
	m_localMatrix(worldMat),
	m_worldMatrix(worldMat),
	m_invMatrix(invWorldMat),
	m_boneChilds()
{

}

CSkelton::CSkelton() :
	m_bones(),
	m_structuredBuffer(nullptr),
	m_shaderResourceView(nullptr),
	m_boneMat(nullptr)
{

}

CSkelton::~CSkelton()
{
	if (m_structuredBuffer != nullptr)
	{
		m_structuredBuffer->Release();
		m_structuredBuffer = nullptr;
	}

	if (m_shaderResourceView != nullptr)
	{
		m_shaderResourceView->Release();
		m_shaderResourceView = nullptr;
	}
}

bool CSkelton::Load(const wchar_t* filePath)
{
	//�t�@�C�����J���ēǂݍ���
	FILE* fp = NULL;
	fp = _wfopen(filePath, L"rb");
	if (fp == NULL)
	{
		return false;
	}
	//���̐����擾�B
	int numBone = 0;
	fread(&numBone, sizeof(numBone), 1, fp);
	for (int i = 0; i < numBone; i++) {
		int nameCount = 0;
		//���̖��O���擾�B
		fread(&nameCount, 1, 1, fp);
		std::unique_ptr<char[]> name = std::make_unique<char[]>(nameCount + 1);
		fread(name.get(), nameCount + 1, 1, fp);
		//�e��ID���擾�B
		int parentId;
		fread(&parentId, sizeof(parentId), 1, fp);
		//�o�C���h�|�[�Y���擾�B
		CVector3 bindPose[4];
		fread(&bindPose, sizeof(bindPose), 1, fp);
		//�o�C���h�|�[�Y�̋t�����擾�B
		CVector3 invBindPose[4];
		fread(&invBindPose, sizeof(invBindPose), 1, fp);

		//�o�C���h�|�[�Y�B
		CMatrix bindPoseMatrix;
		memcpy(bindPoseMatrix.m[0], &bindPose[0], sizeof(bindPose[0]));
		memcpy(bindPoseMatrix.m[1], &bindPose[1], sizeof(bindPose[1]));
		memcpy(bindPoseMatrix.m[2], &bindPose[2], sizeof(bindPose[2]));
		memcpy(bindPoseMatrix.m[3], &bindPose[3], sizeof(bindPose[3]));
		bindPoseMatrix.m[0][3] = 0.0f;
		bindPoseMatrix.m[1][3] = 0.0f;
		bindPoseMatrix.m[2][3] = 0.0f;
		bindPoseMatrix.m[3][3] = 1.0f;

		//�o�C���h�|�[�Y�̋t�s��B
		CMatrix invBindPoseMatrix;
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
		//�{�[�����쐬
		std::unique_ptr<CBone> bone = std::make_unique<CBone>(std::move(boneName), i, parentId, bindPoseMatrix, invBindPoseMatrix);
		m_bones.push_back(std::move(bone));
	}
	fclose(fp);

	for (auto& bone : m_bones)
	{
		//���[�g�{�[������Ȃ���ΐe�̃{�[���Ɏq���Ƃ���bone��ǉ�����
		if (bone->GetParentID() != -1)
		{
			m_bones[bone->GetParentID()]->AddChildren(bone.get());
			CMatrix localMat;
			localMat.Mul(bone->GetWorldMatrix(), m_bones[bone->GetParentID()]->GetInvMatrix());
			bone->SetLocalMatrix(localMat);
		}
		else
		{
			bone->SetLocalMatrix(bone->GetWorldMatrix());
		}
	}
	//�{�[���p�̍s���������
	m_boneMat = std::make_unique<CMatrix[]>(m_bones.size());
	for (int i = 0;i < m_bones.size();i++)
	{
		m_boneMat[i] = m_bones[i]->GetLocalMatrix();
	}
	//�X�g���N�`���[�o�b�t�@���쐬
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = m_bones.size() * sizeof(CMatrix);
	desc.StructureByteStride = sizeof(CMatrix);
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
	D3D11_SUBRESOURCE_DATA resource;
	resource.pSysMem = m_boneMat.get();
	GetDevice()->CreateBuffer(&desc, &resource, &m_structuredBuffer);

	//�V�F�[�_�[���\�[�X�r���[����������
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	ZeroMemory(&viewDesc, sizeof(viewDesc));
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	viewDesc.Format = DXGI_FORMAT_UNKNOWN;
	viewDesc.BufferEx.FirstElement = 0;
	viewDesc.BufferEx.NumElements = m_bones.size();
	GetDevice()->CreateShaderResourceView(m_structuredBuffer, &viewDesc, &m_shaderResourceView);

	Update(CMatrix::Identity);
	return true;
}

void CSkelton::Update(const CMatrix& mat)
{
	//���[�g�{�[����T���e���烏�[���h�s����X�V���Ă���
	for (auto& bone : m_bones)
	{
		if (bone->GetParentID() != -1)
		{
			continue;
		}
		UpdateWorldMatrix(bone.get(), mat);
	}
}

void CSkelton::UpdateWorldMatrix(CBone* bone, const CMatrix& mat)
{
	//�e�̃��[���h�s����g���Ďq�̃��[���h�s����X�V
	CMatrix mBoneWorld;
	CMatrix localMatrix = bone->GetLocalMatrix();
	mBoneWorld.Mul(localMatrix, mat);
	bone->SetWorldMatrix(mBoneWorld);
	for (auto& childBone : bone->GetChildren()) {
		UpdateWorldMatrix(childBone, mBoneWorld);
	}

}


void CSkelton::Render()
{
	//�{�[���̍s����V�F�[�_�[�ɑ���
	for (int i = 0;i < m_bones.size();i++)
	{
		m_boneMat[i].Mul(m_bones[i]->GetInvMatrix(), m_bones[i]->GetWorldMatrix());
	}
	GetDeviceContext()->UpdateSubresource(m_structuredBuffer, 0, NULL, m_boneMat.get(), 0, 0);
	GetDeviceContext()->VSSetShaderResources(100, 1, &m_shaderResourceView);
}