#pragma once
//�}�b�v�Ŕz�u����I�u�W�F�N�g�̊��N���X
class Player;
#include "../Map.h"

class MapChip : public IGameObject
{
public:

	//�R���X�g���N�^
	MapChip();

	//�f�X�g���N�^
	virtual ~MapChip();

	/*
	����������֐�
	position	���W
	rotation	��]
	modelName	�ǂݍ��ރ��f���̖��O
	anim		�A�j���[�V�����t���̃��f���̏ꍇ�A�j���[�V������������ꕨ
	*/
	virtual void Init(const CVector3& position, const CQuaternion& rotation, const wchar_t* modelName, const bool collider, CAnimation* anim = nullptr);

	//�������֐�
	virtual bool Start()override;

	//�X�V�֐�
	virtual void Update()override;

	//�`��֐�
	virtual void Draw()override;

	/*
	�C�e���[�^�[���Z�b�g
	map			���g���f���[�g���邽�߂̃C���X�^���X
	iterator	���g�̃C�e���[�^�[
	*/
	void SetIterator(Map* map, std::list<MapChip*>::iterator iterator);

	//�A�N�e�B�u���̃t���O��ݒ肷��
	/*void SetIsActive(bool isActive)
	{
		m_isActive = isActive;
	}*/

protected:
	//�f���[�g����֐�
	void MapChipDelete();

protected:
	CSkinModel		m_skinModel;				//�X�L�����f��
	CVector3		m_position;					//���W
	CQuaternion		m_rotation;					//��]
	CVector3		m_scale;					//�g��
	Map*			m_pMap;						//�f���[�g���鎞�̂��߂̃|�C���^
	std::list<MapChip*>::iterator m_iterator;	//���g�̃C�e���[�^�[
	bool			m_isActive;					//�A�N�e�B�u���H
	CMatrix			m_worldMatrix;
};