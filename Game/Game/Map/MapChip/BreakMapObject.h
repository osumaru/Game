#pragma once
#include "MapChip.h"
class CBreakMapObject :
	public MapChip
{
public:
	//�R���X�g���N�^
	CBreakMapObject();
	//�f�X�g���N�^
	~CBreakMapObject();

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

	//object��Id
	//int GetBreakId()
	//{
	//	return m_breakId;
	//}

private:


	bool m_isBreak = false;
	std::unique_ptr<CRigidBody>			m_rigidBody;		//����
	std::unique_ptr<CMeshCollider>		m_meshCollider;		//�R���C�_�[
	std::unique_ptr<CBoxCollider>		m_boxCollider;		//�R���C�_�[

};

