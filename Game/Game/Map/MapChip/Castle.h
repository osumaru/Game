#pragma once
#include "MapChip.h"
//���C���[�Ŕ�Ԃ��߂̃{�[�������Ă��郂�f��(ZUp)�Ńi�r���b�V���̃��[�g��e�����߂̃I�u�W�F�N�g
//Castle�Ƃ�CastleWall�Ƃ�Church�Ƃ�������ɂȂ�

class CCastle : public MapChip
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
	std::unique_ptr<CMeshCollider>		m_meshCollider;		//�R���C�_�[

};