#pragma once
//����̎�ނ̗񋓌^
enum EnPlayerWeapon
{
	enWeaponSword,			//�Ў茕
	enWeaponLongSword,		//���茕
	enWeaponArrow,			//�|��
	enWeaponTwinSword,		//��
	enWeaponNum,			//����̐�
	enInvalid			//�����Ȃ�
};

//enum EnAttackWeapon
//{
//	enAttackWeaponLongSword,
//	enAttackWeaponSword,
//	enAttackWeaponRightSword,
//	enAttackWeaponLeftSword,
//	enAttackWeaponArrow,
//	enAttackWeaponNone,
//	enAttackWeaponNum
//};

//����̃X�e�[�^�X
struct SWeaponStatus
{
	int attack = 0;							//�U����
	int diffence = 0;						//�h���
	EnPlayerWeapon weaponNum = enInvalid;	//����̎��
};

struct SWeaponEnemyAttackInfo
{
	bool		isAttack = false;	//�U�����[�V�������U���̔�������邩�̃t���O(�������̕�������邽��
	CVector3	attackPos[2];		//�����蔻��p�̍��W
};

struct SWeaponTraceDrawInfo
{
	bool		isDraw = false;				//�`�悷�邩�̃t���O
	CVector3	rootPos[2];					//����̍�����
	CVector3	pointPos[2];				//����̐������
};