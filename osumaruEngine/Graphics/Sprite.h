#pragma once
class Texture;
#include "Shader.h"
#include "Primitive.h"
//�X�v���C�g�N���X

class Sprite
{
public:
	//�R���X�g���N�^
	Sprite();

	//�f�X�g���N�^
	~Sprite();

	/*
	�������֐�
	texture	�X�v���C�g�ɒ���t����e�N�X�`��
	*/
	void Init(Texture* texture);

	//�`��֐�
	void Draw();

	//���W��ݒ�
	void SetPosition(const Vector2& position)
	{
		m_position = position;
	}

	//���W���擾
	const Vector2& GetPosition() const
	{
		return m_position;
	}

	//�T�C�Y��ݒ�
	void SetSize(const Vector2& size)
	{
		m_size = size;
	}

	//�s�����x��ݒ�
	void SetAlpha(float alpha)
	{
		m_alpha = alpha;
	}

	//�T�C�Y���擾
	const Vector2& GetSize() const
	{
		return m_size;
	}

	//�e�N�X�`����ݒ�
	void SetTexture(Texture* pTexture)
	{
		if(pTexture != nullptr)
		{
			return;
		}
		m_pTexture = pTexture;
	}

private:
	struct VSLayout
	{
		Vector4 position;
		Vector2	uv;
	};

	struct SpriteCB
	{
		Matrix worldMat;
		float alpha;
	};

	Texture*						m_pTexture;
	Shader							m_vertexShader;
	Shader							m_pixelShader;
	Primitive						m_primitive;
	float							m_alpha;
	Vector2							m_position;			//�X�v���C�g�̃E�B���h�E��ł̍��W
	Vector2							m_centerPosition;	//�X�v���C�g�̊�_��\�����W
	Vector2							m_size;				//�X�v���C�g�̃T�C�Y
	ConstantBuffer					m_cb;
};