#pragma once
//�G�t�F�N�g�N���X

class CEffect
{
public:
	/*
	�������֐�
	filePath	�t�@�C���̃p�X
	*/
	void Init(wchar_t* filepath);

	//�Đ��֐�
	void Play();

	//�X�V
	void Update();

	Effekseer::Effect* GetBody()
	{
		return m_effect;
	}

	//���W���擾
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//���W��ݒ�
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}

	//��]���擾
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

	//��]��ݒ�
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}

	//�g�嗦��ݒ�
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}

private:
	CVector3				m_scale = CVector3::One;
	CVector3				m_position = CVector3::Zero;		//���W
	CQuaternion				m_rotation = CQuaternion::Identity;	//��]
	Effekseer::Effect*		m_effect = nullptr;					//�G�t�F�N�g
	Effekseer::Handle		m_handle = -1;						//�G�t�F�N�g�����ʂ��邽�߂̔ԍ�
};