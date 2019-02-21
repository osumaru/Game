#pragma once
#include "MapChip.h"

//�w�i�I�u�W�F�N�g

class StaticMapObject : public MapChip
{
public:
	//�R���X�g���N�^
	StaticMapObject();

	//�f�X�g���N�^
	~StaticMapObject();

	/*
	����������֐�
	position	���W
	rotation	��]
	modelName	�ǂݍ��ރ��f���̖��O
	collider	�R���C�_�[�̐ݒ�@false�Ȃ烁�b�V��	true�Ȃ�{�b�N�X
	anim		�A�j���[�V�����t���̃��f���̏ꍇ�A�j���[�V������������ꕨ
	*/
	void Init(const SMapChipInfo& info, CAnimation* anim = nullptr)override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;

	//���f�����擾
	const CSkinModel& GetSkinModel() const 
	{
		return m_skinModel;
	}

private:
	std::unique_ptr<CRigidBody>			m_rigidBody;		//����
	std::unique_ptr<CMeshCollider>		m_meshCollider;		//�R���C�_�[
	bool								isCollider;
	bool								m_isTree = false;	//�ؗp�̃R���C�_�[�̐ݒ�����邽�߂̃t���O		

};
