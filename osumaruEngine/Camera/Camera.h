#pragma once
class Camera
{
public:
	//�R���X�g���N�^
	Camera();

	//�f�X�g���N�^
	~Camera();

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
	void SetTarget(const Vector3& target);

	//���_���擾
	const Vector3& GetTarget() const;

	//���W��ݒ�
	void SetPosition(const Vector3& position);

	//���W���擾
	const Vector3& GetPosition() const;

	//�J�����̏������ݒ�
	void SetUp(const Vector3& up);

	//�J�����̏�������擾
	const Vector3& GetUp() const;

	//�J�����̑O�������擾
	const Vector3& GetFlont() const;

	//�J�����̉��������擾
	const Vector3& GetRight() const;

	//�r���[�s��̐ݒ�B
	void SetViewMatrix(const Matrix& view);

	//�r���[�s��̎擾
	const Matrix& GetViewMatrix() const;

	//�v���W�F�N�V�����s��̐ݒ�B
	void SetProjectionMatrix(const Matrix& projection);

	//�v���W�F�N�V�����s��̎擾�B
	const Matrix& GetProjectionMatrix() const;

	//������
	void Init();

	//�X�V����
	void Update();

private:
	Matrix			m_viewMatrix;			//�r���[�s��B�J�����s��Ƃ������B
	Matrix			m_projectionMatrix;		//�v���W�F�N�V�����s��B�r���[��Ԃ���ˉe��Ԃɕϊ�����B
	Vector3			m_position;				//�J�����̎��_�B
	Vector3			m_target;				//�J�����̒����_
	Vector3			m_up;					//�J�����̏����
	Vector3			m_flont;				//�J�����̑O����
	Vector3			m_right;				//�J�����̉�����

	float				m_Far;					//������
	float				m_Near;					//�ߕ���
	float				m_Aspect;				//�A�X�y�N�g��
	float				m_angle;				//��p
};