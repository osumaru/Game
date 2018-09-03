#pragma once
#include "SkinModelEffectFactory.h"
class CSkelton;
class CAnimation;
//�X�L�����f���N���X

class CSkinModel : Uncopyable
{
public:
	struct SSkinModelCB
	{
		CMatrix worldMat;		//���[���h�s��
		CMatrix viewProjMat;			//�r���[�v���W�F�N�V�����s��
	};

	//�R���X�g���N�^
	CSkinModel();

	//�f�X�g���N�^
	~CSkinModel();

	/*
	���[���h�s����X�V
	position	���W
	rotation	��]
	scale		�g��
	isZup		Z�A�b�v�œf���o�������f����true,Y�A�b�v�œf���o�����ꍇ��false
	*/
	void Update(const CVector3& position, const CQuaternion& rotation, const CVector3& scale, bool isZup = false);

	/*
	���f���̓ǂݍ���
	filePath	���f���̃t�@�C���p�X
	animation	�A�j���[�V�������L�郂�f���Ȃ�A�j���[�V�����̃C���X�^���X
	*/
	void Load(wchar_t* filePath, CAnimation* animation = nullptr);

	/*
	�`��֐�
	view	�r���[�s��
	proj	�v���W�F�N�V�����s��
	*/
	void Draw(const CMatrix& view, const CMatrix& proj);

	//���f�����擾
	DirectX::Model* GetBody()
	{
		return m_skinModel.get();
	}

	//�X�P���g�����擾
	CSkelton* GetSkelton()
	{
		return m_skelton.get();
	}

	//���[���h�s��̎擾
	const CMatrix& GetWorldMatrix()
	{
		return worldMatrix;
	}

private:
	std::unique_ptr<CSkelton>		m_skelton = nullptr;			//�X�P���g��
	CConstantBuffer					constantBuffer;					//�萔�o�b�t�@
	std::unique_ptr<DirectX::Model> m_skinModel = nullptr;			//�X�L�����f��
	CMatrix							worldMatrix = CMatrix::Identity;	//���[���h�s��
	
};