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

	//�X�L�����f�����擾
	const CSkinModel& GetSkinModel() const
	{
		return m_skinModelTwin;
	}

	//���_�o�b�t�@�̍��W���i�[���Ă��郊�X�g
	const std::vector<CVector3>& GetTwinVertexBufferList() const
	{
		return m_twinVertexBufferVector;
	}

	//���_�o�b�t�@�̐�
	int GetTwinVertexBufferCount()
	{
		return m_twinVertexBufferCount;
	}

private:
	
	const CMatrix*				m_normalTwinBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	const CMatrix*				m_attackTwinBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	CVector3					m_positionTwin;					//�ʏ펞�̍��W
	CVector3					m_attackTwinPosition;			//�U�����̍��W
	CQuaternion					m_rotationTwin;					//�ʏ펞�̉�]
	CQuaternion					m_attackTwinRotation;			//�U�����̉�]
	CSkinModel					m_skinModelTwin;				//�o������̃X�L�����f��
	std::vector<CVector3>		m_twinVertexBufferVector;		//���_�o�b�t�@�̍��W���i�[���Ă��郊�X�g
	int							m_twinVertexBufferCount = 0;	//���_�o�b�t�@�̐�
};