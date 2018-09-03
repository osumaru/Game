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
	anim		�A�j���[�V�����t���̃��f���̏ꍇ�A�j���[�V������������ꕨ
	*/
	void Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, CAnimation* anim = nullptr)override;

	//�X�V�֐�
	void Update()override;

	//�`��֐�
	void Draw()override;

private:
	std::unique_ptr<CRigidBody>		m_rigidBody;		//����
	std::unique_ptr<CMeshCollider>		m_boxCollider;		//�R���C�_�[
};
