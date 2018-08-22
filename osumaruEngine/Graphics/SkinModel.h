#pragma once
#include "SkinModelEffectFactory.h"
class Skelton;
class Animation;
//�X�L�����f���N���X

class SkinModel : Uncopyable
{
public:
	struct SkinModelCB
	{
		Matrix worldMat;		//���[���h�s��
		Matrix viewMat;			//�r���[�s��
		Matrix projMat;			//�v���W�F�N�V�����s��
	};

	//�R���X�g���N�^
	SkinModel();

	//�f�X�g���N�^
	~SkinModel();

	/*
	���[���h�s����X�V
	position	���W
	rotation	��]
	scale		�g��
	*/
	void Update(Vector3 position, Quaternion rotation, Vector3 scale);

	/*
	���f���̓ǂݍ���
	filePath	���f���̃t�@�C���p�X
	animation	�A�j���[�V�������L�郂�f���Ȃ�A�j���[�V�����̃C���X�^���X
	*/
	void Load(wchar_t* filePath, Animation* animation = nullptr);

	/*
	�`��֐�
	view	�r���[�s��
	proj	�v���W�F�N�V�����s��
	*/
	void Draw(Matrix view, Matrix proj);

	//���f�����擾
	DirectX::Model* GetBody()
	{
		return m_skinModel.get();
	}

	//�X�P���g�����擾
	Skelton* GetSkelton()
	{
		return m_skelton.get();
	}

private:
	std::unique_ptr<Skelton>		m_skelton = nullptr;			//�X�P���g��
	ConstantBuffer					constantBuffer;					//�萔�o�b�t�@
	std::unique_ptr<DirectX::Model> m_skinModel = nullptr;			//�X�L�����f��
	Matrix							worldMatrix = Matrix::Identity;	//���[���h�s��
	
};