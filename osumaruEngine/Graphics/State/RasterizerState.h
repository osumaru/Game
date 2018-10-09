#pragma once

enum EnRasterizerState
{
	enRasterizerState3D,
	enRasterizerState2D,
	enRasterizerStateNum,

};

class CRasterizerState : Uncopyable
{
public:
	~CRasterizerState();

	void Init(ID3D11Device* device);

	void SetRasterizerState(ID3D11DeviceContext* deviceContext, EnRasterizerState rasterizerState)
	{
		deviceContext->RSSetState(m_rasterizerState[rasterizerState]);
	}

private:
	ID3D11RasterizerState* m_rasterizerState[enRasterizerStateNum];
};