#pragma once
#include "MapChip.h"

class CTree : public MapChip
{
public:

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

private:
	std::unique_ptr<CRigidBody>			m_rigidBody;		//����
	std::unique_ptr<CBoxCollider>		m_boxCollider;		//�R���C�_�[

};