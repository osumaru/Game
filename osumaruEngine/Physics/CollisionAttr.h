#pragma once


enum EnCollisionAttr
{
	enCollisionAttr_Unknown = -1,
	enCollisionAttr_Ground,
	enCollisionAttr_Character,
	enCollisionAttr_MoveFloor,
	enCollisionAttr_Spring,
	enCollisionAttr_Rotation,
	enCollisionAttr_Detection,
	enCollisionAttr_Item,
	enCollisionAttr_MapChip,
	enCollisionAttr_User,		//�ȉ��Ƀ��[�U�[��`�̃R���W����������ݒ肷��B
};

enum EnJudgmentColl
{
	enJudgment_Wall,
	enJudgment_Ground,
	enJudgment_Inactive,
};