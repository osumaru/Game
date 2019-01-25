#pragma once
#include "WeaponCommon.h"
#include "WeaponTraceDraw.h"
#include "..\PlayerSate\PlayerStateCommon.h"
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
		return { false, CVector3::Zero};
	}

	//����̋O�Ղ�`�悷����W��`�悷�邩�����߂�֐�
	virtual SWeaponTraceDrawInfo WeaponTraceDraw()
	{
		return { false, CVector3::Zero, CVector3::Zero };
	}

	//����̋O�Ղ�`�悷��
	void WeaponTraceDrawer();

	//����̋O�Ղ̕`����J�n
	void WeaponTraceDrawStart();

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

	//�U�����[�V�����̐擪���擾
	EnPlayerAnimation* GetAttackAnimation()
	{
		return m_attackAnimation.get();
	}

	//�U���I�����[�V�����̐擪���擾
	EnPlayerAnimation* GetCombineAnimation()
	{
		return m_combineAnimation.get();
	}

	//�X�^���U���̐擪���擾
	bool* GetStanAttack()
	{
		return m_stanAttack.get();
	}

	//�U�����[�V�����̐����擾
	int GetMaxAttackNum()
	{
		return m_maxAttackNum;
	}

	//���킲�Ƃ̍ő�U����
	int GetMaxWeaponHitNum()
	{
		return m_maxWeaponHitNum;
	}

	//�X�L�����f�����擾
	const CSkinModel& GetSkinModel() const
	{
		return m_skinModel;
	}

	//���_�o�b�t�@�̍��W���i�[���Ă��郊�X�g
	const std::vector<CVector3>& GetVertexBufferList() const
	{
		return m_vertexBufferVector;
	}

	//���_�o�b�t�@�̐�
	int GetVertexBufferCount()
	{
		return m_vertexBufferCount;
	}

protected:
	struct SHitEffectParam
	{
		float slowTime = 0.0f;		//�X���[�ɂ��鎞��
		float slowScale = 1.0f;		//�ǂ̂��炢�X���[�ɂ��邩�̔{��
		float shakePower = 0.0f;	//�J�����h��̋���
		float slowDelayTime = 0.0f;	//�X���[�ɂ���܂ł̒x������
		float shakeDelayTime = 0.0f;//�h���܂ł̒x������
	};

	CPlayer*								m_pPlayer = nullptr;		//�v���C���[�̃C���X�^���X
	const CMatrix*							m_normalBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	const CMatrix*							m_attackBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	CVector3								m_position;					//�ʏ펞�̍��W
	CVector3								m_attackPosition;			//�U�����̍��W
	CQuaternion								m_rotation;					//�ʏ펞�̉�]
	CQuaternion								m_attackRotation;			//�U�����̉�]
	CSkinModel								m_skinModel;				//����̃X�L�����f��
	SWeaponStatus							m_weaponStatus;				//�������̕���m�X�e�[�^�X
	int										m_maxWeaponHitNum = 0;		//����̐�
	int										m_maxAttackNum = 0;			//�ő�A���U����
	std::unique_ptr<SHitEffectParam[]>		m_hitEffectParam;			//�U���������������̃G�t�F�N�g�p�����[�^
	std::unique_ptr<EnPlayerAnimation[]>	m_attackAnimation;			//�U���̃A�j���[�V�����ԍ�
	std::unique_ptr<EnPlayerAnimation[]>	m_combineAnimation;			//�U���̌�̍����p�̃A�j���[�V�����ԍ�
	std::unique_ptr<bool[]>					m_stanAttack;				//�X�^���U��
	std::unique_ptr<bool[]>					m_attackHitNum;				//���킲�Ƃ̍U����
	std::vector<CVector3>					m_vertexBufferVector;		//���_�o�b�t�@�̍��W���i�[���Ă��郊�X�g
	int										m_vertexBufferCount = 0;	//���_�o�b�t�@�̐�
	CEffect									m_hitEffect;
};