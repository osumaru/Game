#pragma once

enum EnSamplerAddressingMode
{
	enAddressingModeWrap,
	enAddressingModeClamp,
};

enum EnSamplerFilter
{
	enFilterLinear,
};
class CSamplerState
{
public:
	/*
	�T���v���[�X�e�[�g�̏�����
	addressingMode	�A�h���b�V���O���[�h
	filter			�t�B���^�[
	*/
	void Init(EnSamplerAddressingMode addressingMode, EnSamplerFilter filter);

	//�T���v���[�X�e�[�g���擾
	ID3D11SamplerState* GetBody()
	{
		return m_samplerState;
	}

private:
	ID3D11SamplerState* m_samplerState = nullptr;


};