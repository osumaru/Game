#pragma once
#include "IWeapon.h"

class CTwinSword : public IWeapon
{
public:
	void Init()override;

	void Update()override;

	void Draw() override;

	//�G�l�~�[�Ƃ̓����蔻������֐��@��ڂ̌��p
	//void EnemyAttack() override;

	//void EnemyAttackTwin();

	SWeaponEnemyAttackInfo EnemyAttackPositionDecide()override;

	//SWeaponEnemyAttackInfo EnemyAttackPositionTwinDecide();

	SWeaponTraceDrawInfo WeaponTraceDraw()override;

	//��ڂ̌��p
	//SWeaponTraceDrawInfo WeaponTraceTwinDraw();

	//void WeaponTraceTwinDrawer();
private:
	
	const CMatrix*				m_normalTwinBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	const CMatrix*				m_attackTwinBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	CVector3					m_positionTwin;					//�ʏ펞�̍��W
	CVector3					m_attackTwinPosition;			//�U�����̍��W
	CQuaternion					m_rotationTwin;					//�ʏ펞�̉�]
	CQuaternion					m_attackTwinRotation;			//�U�����̉�]
	CSkinModel					m_skinModelTwin;				//�o������̃X�L�����f��
};