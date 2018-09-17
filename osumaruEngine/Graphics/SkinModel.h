#pragma once
#include "SkinModelEffectFactory.h"
#include "Light.h"
class CSkelton;
class CAnimation;
//�X�L�����f���N���X

class CSkinModel : Uncopyable
{
public:
	//�萔�o�b�t�@�p�̍\����
	struct SSkinModelCB
	{
		CMatrix worldMat;				//���[���h�s��
		CMatrix viewProjMat;			//�r���[�v���W�F�N�V�����s��
		int		isNormalMap;			//�m�[�}���}�b�v�����邩�̃t���O
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
	void Load(const wchar_t* filePath, CAnimation* animation = nullptr);

	/*
	�`��֐�
	view	�r���[�s��
	proj	�v���W�F�N�V�����s��
	*/
	void Draw(const CMatrix& view, const CMatrix& proj);


	//���f�����擾
	DirectX::Model* GetBody() const
	{
		return m_skinModel;
	}

	//�X�P���g�����擾
	const CSkelton* GetSkelton() const
	{
		return m_skelton.get();
	}

	//���[���h�s��̎擾
	const CMatrix& GetWorldMatrix() const
	{
		return worldMatrix;
	}

	/*
	���̃��[���h�s����擾
	boneName	�T�����̖��O
	ret			�����������̃��[���h�s���Ԃ��A������Ȃ�������P�ʍs���Ԃ�
	*/
	const CMatrix& FindBoneWorldMatrix(const wchar_t* boneName) const;

	//���C�g�̐ݒ�
	void SetLight(const CLight& light)
	{
		m_light = light;
	}
	/*
	�@���}�b�v�̓ǂݍ���

	*/
	void LoadNormalmap(const wchar_t* filePath);
	
private:
	std::unique_ptr<CSkelton>		m_skelton = nullptr;				//�X�P���g��
	CConstantBuffer					constantBuffer;						//�萔�o�b�t�@
	CConstantBuffer					m_lightCB;							//���C�g�̃o�b�t�@
	CLight							m_light;							//���C�g
	DirectX::Model*					m_skinModel = nullptr;				//�X�L�����f��
	CMatrix							worldMatrix = CMatrix::Identity;	//���[���h�s��
	CTexture*						m_pNormalTexture = nullptr;
	int								m_isNormalMap = 0;
};