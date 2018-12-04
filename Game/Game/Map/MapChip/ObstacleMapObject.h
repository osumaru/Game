#pragma once
#include "MapChip.h"

class CObstacleMapObject : public MapChip
{
public:

	CObstacleMapObject();

	~CObstacleMapObject();
	
	/*
	����������֐�
	position	���W
	rotation	��]
	modelName	�ǂݍ��ރ��f���̖��O
	collider	�R���C�_�[�̐ݒ�@false�Ȃ烁�b�V��	true�Ȃ�{�b�N�X
	anim		�A�j���[�V�����t���̃��f���̏ꍇ�A�j���[�V������������ꕨ
	*/
	void Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, const bool collider, CAnimation* anim = nullptr)override;

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
	CRigidBody							m_rigidBody;		//����
	CBoxCollider						m_boxCollider;		//�R���C�_�[
};