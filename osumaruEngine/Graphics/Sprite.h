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
		if(pTexture == nullptr)
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

	//�`�悷�邩�̃t���O���擾
	bool IsDraw() const
	{
		return m_isDraw;
	}

	//�`�悷�邩�̃t���O��ݒ�
	void SetIsDraw(bool isDraw)
	{
		m_isDraw = isDraw;
	}

	/*
	�X�v���C�g��Z�l��ݒ�
	0.0f����Ԏ�O��1.0f���ŉ�
	*/
	void SetDepthValue(float depthValue)
	{
		m_depthValue = depthValue;
	}
private:
	//���_���C�A�E�g
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	//�萔�o�b�t�@
	struct SSpriteCB
	{
		CMatrix worldMat;	//���[���h�s��
		float alpha;		//�A���t�@�l
		float depthValue;	//Z�̒l
	};

	CTexture*						m_pTexture;			//�e�N�X�`��
	CShader							m_vertexShader;		//���_�V�F�[�_�[
	CShader							m_pixelShader;		//�s�N�Z���V�F�[�_�[
	CPrimitive						m_primitive;		//�v���~�e�B�u
	float							m_alpha;			//�A���t�@�l
	float							m_angle;			//��]�p�x
	CVector2						m_position;			//�X�v���C�g�̃E�B���h�E��ł̍��W
	CVector2						m_centerPosition;	//�X�v���C�g�̊�_��\�����W
	CVector2						m_size;				//�X�v���C�g�̃T�C�Y
	CConstantBuffer					m_cb;				//�萔�o�b�t�@
	bool							m_isDraw;			//�`�悷�邩�ǂ����H
	float							m_depthValue;		//Z�̒l
};