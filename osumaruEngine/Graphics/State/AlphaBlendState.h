#pragma once

enum EnAlphaBlendState
{
	enAlphaBlendStateAdd,				//���Z����	
	enAlphaBlendStateTranslucent,		//����������
	enAlphaBlendStateNone,				//�A���t�@�u�����h��
	enAlphaBlendStateNum,
};

//�A���t�@�u�����h�̐ݒ���Ǘ�����N���X
class CAlphaBlendState : Uncopyable
{
public:

	//�f�X�g���N�^
	~CAlphaBlendState();

	//������
	void Init(ID3D11Device* device);


	/*
	�A���t�@�u�����h�ݒ��ύX
	deviceContext		�O���t�B�b�N�f�o�C�X
	enBlendState		�A���t�@�u�����h�̐ݒ�
	*/
	void SetBlendState(ID3D11DeviceContext* deviceContext, EnAlphaBlendState enBlendState)
	{
		m_currentState = enBlendState;
		deviceContext->OMSetBlendState(m_blendState[m_currentState], NULL, 0xffffffff);
	}

	//���݂̐ݒ���擾
	EnAlphaBlendState GetCurrentBlendState()
	{
		return m_currentState;
	}

private:
	ID3D11BlendState*		m_blendState[enAlphaBlendStateNum] = {nullptr};		//�A���t�@�u�����h�X�e�[�g
	EnAlphaBlendState		m_currentState = enAlphaBlendStateAdd;				//���݂̐ݒ�
};