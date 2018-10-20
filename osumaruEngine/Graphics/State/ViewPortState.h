#pragma once
enum EnViewPortState
{
	enViewPortShadow,	//�V���h�E�}�b�v�p�̃r���[�|�[�g�ݒ�
	enViewPortGame,		//�Q�[���V�[���p�̃r���[�|�[�g�ݒ�
	enViewPortNum
};

//�r���[�|�[�g�̐ݒ���Ǘ�����N���X
class CViewPortState
{
public:
	//������
	void Init();

	/*
	�r���[�|�[�g�ݒ��ύX
	deviceContext		�O���t�B�b�N�f�o�C�X
	viewPortNum			�r���[�|�[�g�ݒ�
	*/
	void SetViewPort(ID3D11DeviceContext* deviceContext, EnViewPortState viewPortNum)
	{
		m_currentState = viewPortNum;
		deviceContext->RSSetViewports(1, &m_viewPort[m_currentState]);
	}

	//���݂̐ݒ�̔ԍ����擾
	EnViewPortState GetCurrentState()
	{
		return m_currentState;
	}

private:
	D3D11_VIEWPORT	m_viewPort[enViewPortNum];		//�r���[�|�[�g�ݒ�
	EnViewPortState	m_currentState = enViewPortGame;//���݂̐ݒ�
};