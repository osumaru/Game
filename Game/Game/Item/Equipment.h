/*
*	�����A�C�e���N���X
*/

#pragma once

#include "IItem.h"

class CEquipment : public IItem
{
public:
	//������
	void Init();

	//�X�V����O�Ɉ�x�����Ă΂��
	bool Start() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�|�b�v������
	//position		���W
	void Pop(CVector3 position);
private:
	////�����̃p�����[�^�[
	//struct SEquipParameter
	//{
	//	int hp;			//HP
	//	int	strength;	//�U����
	//	int defense;	//�h���
	//};

	//SEquipParameter m_equipParameter;
};