#pragma once
//����̎�ނ̗񋓌^
enum EnPlayerWeapon
{
	enWeaponSword,			//�Ў茕
	enWeaponLongSword,		//���茕
	enWeaponArrow,			//�|��
	enWeaponTwinSword,		//��
	enWeaponNum,
	enInvalid			//�����Ȃ�
};


//����̃X�e�[�^�X
struct SWeaponStatus
{
	int attack = 0;							//�U����
	int diffence = 0;						//�h���
	EnPlayerWeapon weaponNum = enInvalid;	//����̎��
};