#pragma once
#include "IWeapon.h"

class CTwinSword : public IWeapon
{
public:
	void Init()override;

	void Update()override;

	void Draw() override;

	SWeaponEnemyAttackInfo EnemyAttackPositionDecide()override;

	SWeaponTraceDrawInfo WeaponTraceDraw()override;

	SWeaponTraceDrawInfo WeaponTraceTwinDraw();

	//����̋O�Ղ�`�悷��
	void WeaponTraceTwinDrawer();

private:
	
	const CMatrix*				m_normalTwinBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	const CMatrix*				m_attackTwinBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	CVector3					m_positionTwin;					//�ʏ펞�̍��W
	CVector3					m_attackTwinPosition;			//�U�����̍��W
	CQuaternion					m_rotationTwin;					//�ʏ펞�̉�]
	CQuaternion					m_attackTwinRotation;			//�U�����̉�]
	CSkinModel					m_skinModelTwin;				//�o������̃X�L�����f��
};