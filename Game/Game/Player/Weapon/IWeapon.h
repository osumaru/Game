#pragma once
#include "WeaponCommon.h"
#include "WeaponTraceDraw.h"

class CPlayer;
//����̊��N���X

class IWeapon
{
public:
	//�f�X�g���N�^
	virtual ~IWeapon(){}

	//�������֐�
	void Init(CPlayer* player);

	//�p���p�p�̏������֐�
	virtual void Init(){}

	//�X�V����
	void Updater();
	
	//�p���p�̍X�V����
	virtual void Update(){}

	//�`�揈��
	void Drawer();

	//�p���p�̕`�揈��
	virtual void Draw(){}

	//�|�X�g�G�t�F�N�g��̕`�揈��
	void AfterDrawer();

	//�p���p�̃|�X�g�G�t�F�N�g��̕`�揈��
	virtual void AfterDraw(){}

	//�G�l�~�[�Ƃ̓����蔻������֐�
	void EnemyAttack();

	//�����蔻�����邽�߂̕���̍��W�����߂邽�߂̊֐�
	virtual SWeaponEnemyAttackInfo EnemyAttackPositionDecide()
	{
		return { false, CVector3::Zero };
	}

	//����̋O�Ղ�`�悷����W��`�悷�邩�����߂�֐�
	virtual SWeaponTraceDrawInfo WeaponTraceDraw()
	{
		return { false, CVector3::Zero, CVector3::Zero };
	}

	//����̋O�Ղ�`�悷��
	void WeaponTraceDrawer();


	//����̃X�e�[�^�X���擾
	SWeaponStatus& GetWeaponStatus()
	{
		return m_weaponStatus;
	}

	//����̃X�e�[�^�X��ݒ�
	void SetWeaponStatus(SWeaponStatus& weaponStatus)
	{
		m_weaponStatus = weaponStatus;
	}

protected:
	CPlayer*					m_pPlayer = nullptr;		//�v���C���[�̃C���X�^���X
	const CMatrix*				m_normalBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	const CMatrix*				m_attackBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	CVector3					m_position;					//�ʏ펞�̍��W
	CVector3					m_attackPosition;			//�U�����̍��W
	CQuaternion					m_rotation;					//�ʏ펞�̉�]
	CQuaternion					m_attackRotation;			//�U�����̉�]
	CSkinModel					m_skinModel;				//����̃X�L�����f��
	SWeaponStatus				m_weaponStatus;				//�������̕���m�X�e�[�^�X
};