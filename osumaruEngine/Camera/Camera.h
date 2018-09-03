#pragma once
class CCamera
{
public:
	//�R���X�g���N�^
	CCamera();

	//�f�X�g���N�^
	~CCamera();

	//�A�X�y�N�g���ݒ�
	void SetAspect(float _aspect);

	//�A�X�y�N�g����擾
	float GetAspect() const;

	//�t�@�[��ݒ�
	void SetFar(float _far);

	//�t�@�[���擾
	float GetFar() const;

	//�j�A��ݒ�
	void SetNear(float _near);

	//�j�A���擾
	float GetNear() const;

	//��p��ݒ�B
	void SetAngle(float angle);

	//��p���擾
	float GetAngle() const;

	//���_��ݒ�
	void SetTarget(const CVector3& target);

	//���_���擾
	const CVector3& GetTarget() const;

	//���W��ݒ�
	void SetPosition(const CVector3& position);

	//���W���擾
	const CVector3& GetPosition() const;

	//�J�����̏������ݒ�
	void SetUp(const CVector3& up);

	//�J�����̏�������擾
	const CVector3& GetUp() const;

	//�J�����̑O�������擾
	const CVector3& GetFlont() const;

	//�J�����̉��������擾
	const CVector3& GetRight() const;

	//�r���[�s��̐ݒ�B
	void SetViewMatrix(const CMatrix& view);

	//�r���[�s��̎擾
	const CMatrix& GetViewMatrix() const;

	//�v���W�F�N�V�����s��̐ݒ�B
	void SetProjectionMatrix(const CMatrix& projection);

	//�v���W�F�N�V�����s��̎擾�B
	const CMatrix& GetProjectionMatrix() const;

	//������
	void Init();

	//�X�V����
	void Update();

private:
	CMatrix			m_viewMatrix;			//�r���[�s��B�J�����s��Ƃ������B
	CMatrix			m_projectionMatrix;		//�v���W�F�N�V�����s��B�r���[��Ԃ���ˉe��Ԃɕϊ�����B
	CVector3			m_position;				//�J�����̎��_�B
	CVector3			m_target;				//�J�����̒����_
	CVector3			m_up;					//�J�����̏����
	CVector3			m_flont;				//�J�����̑O����
	CVector3			m_right;				//�J�����̉�����

	float				m_Far;					//������
	float				m_Near;					//�ߕ���
	float				m_Aspect;				//�A�X�y�N�g��
	float				m_angle;				//��p
};