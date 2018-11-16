#pragma once
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

	void Drawer();

	virtual void Draw(){}

	virtual void AfterDraw(){}

	void AfterDrawer();

	virtual void EnemyAttack(){ }

	void EnemyAttacker();

	const CVector3 GetPosition() const
	{
		return m_worldPos;
	}
protected:
	CPlayer*					m_pPlayer = nullptr;		//�v���C���[�̃C���X�^���X
	const CMatrix*				m_normalBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	const CMatrix*				m_attackBoneMat = nullptr;	//�v���C���[�̃{�[���s��
	CVector3					m_position;					//�ʏ펞�̍��W
	CVector3					m_attackPosition;			//�U�����̍��W
	CQuaternion					m_rotation;					//�ʏ펞�̉�]
	CQuaternion					m_attackRotation;			//�U�����̉�]
	CVector3					m_worldPos;					//�����蔻��p�̍��W
	CSkinModel					m_skinModel;				//����̃X�L�����f��
	
};