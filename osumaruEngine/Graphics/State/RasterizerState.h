#pragma once

enum EnRasterizerState
{
	enRasterizerState3D,
	enRasterizerState2D,
	enRasterizerStateNum,

};
//���X�^���C�U�̐ݒ���Ǘ�����N���X
class CRasterizerState : Uncopyable
{
public:

	//������
	void Init(ID3D11Device* device);

	/*
	���X�^���C�U�̐ݒ��ύX
	deviceContext		�O���t�B�b�N�f�o�C�X
	rasterizerState		���X�^���C�U�̐ݒ�
	*/
	void SetRasterizerState(ID3D11DeviceContext* deviceContext, EnRasterizerState rasterizerState)
	{
		m_currentState = rasterizerState;
		deviceContext->RSSetState(m_rasterizerState[m_currentState]);
	}

	//���X�^���C�U�̌��݂̐ݒ���擾
	EnRasterizerState GetCurrentState() const
	{
		return m_currentState;
	}

private:
	ID3D11RasterizerState*	m_rasterizerState[enRasterizerStateNum];	//���X�^���C�U
	EnRasterizerState		m_currentState = enRasterizerState2D;		//���݂̐ݒ�
};