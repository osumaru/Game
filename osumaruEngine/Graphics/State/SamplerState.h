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
	サンプラーステートの初期化
	addressingMode	アドレッシングモード
	filter			フィルター
	*/
	void Init(EnSamplerAddressingMode addressingMode, EnSamplerFilter filter);

	//サンプラーステートを取得
	ID3D11SamplerState* GetBody()
	{
		return m_samplerState;
	}

private:
	ID3D11SamplerState* m_samplerState = nullptr;


};