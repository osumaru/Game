#pragma once
class CTexture;
#include "Shader.h"
#include "Primitive.h"
//�X�v���C�g�N���X

class CSprite
{
public:
	//�R���X�g���N�^
	CSprite();

	//�f�X�g���N�^
	~CSprite();

	/*
	�������֐�
	texture	�X�v���C�g�ɒ���t����e�N�X�`��
	*/
	void Init(CTexture* texture);

	//�`��֐�
	void Draw();

	//���W��ݒ�
	void SetPosition(const CVector2& position)
	{
		m_position = position;
	}

	//���W���擾
	const CVector2& GetPosition() const
	{
		return m_position;
	}

	//�T�C�Y��ݒ�
	void SetSize(const CVector2& size)
	{
		m_size = size;
	}

	//�s�����x��ݒ�
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	//�T�C�Y���擾
	const CVector2& GetSize() const
	{
		return m_size;
	}

	//�e�N�X�`����ݒ�
	void SetTexture(CTexture* pTexture)
	{
		if(pTexture != nullptr)
		{
			return;
		}
		m_pTexture = pTexture;
	}

	/*
	�X�v���C�g�̊��̍��W��ύX
	���オ(x,y) = (0.0f, 0.0f)
	�E����(x,y) = (1.0f, 1.0f)
	�^�񒆂�(x, y) = (0.5f, 0.5f)
	*/
	void SetCenterPosition(CVector2 position)
	{
		m_centerPosition = position;
	}
	/*
	�X�v���C�g�̉�]�̊p�x��ݒ�
	angle	�p�x�i���W�A���l�j
	*/
	void SetRotationAngle(float angle)
	{
		m_angle = angle;
	}

private:
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	struct SSpriteCB
	{
		CMatrix worldMat;
		float alpha;
	};

	CTexture*						m_pTexture;
	CShader							m_vertexShader;
	CShader							m_pixelShader;
	CPrimitive						m_primitive;
	float							m_alpha;
	float							m_angle;			//��]�p�x
	CVector2						m_position;			//�X�v���C�g�̃E�B���h�E��ł̍��W
	CVector2						m_centerPosition;	//�X�v���C�g�̊�_��\�����W
	CVector2						m_size;				//�X�v���C�g�̃T�C�Y
	CConstantBuffer					m_cb;
};