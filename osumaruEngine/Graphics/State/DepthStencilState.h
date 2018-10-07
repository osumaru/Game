#pragma once
enum EnDepthStencilState
{
	enDepthStencilState2D,
	enDepthStencilState3D,
	enDepthStencilStateNum,
};

class CDepthStencilState : Uncopyable
{
public:

	~CDepthStencilState();

	void Init(ID3D11Device* device);

	void SetDepthStencilState(ID3D11DeviceContext* deviceContext, EnDepthStencilState depthStencilState)
	{
		deviceContext->OMSetDepthStencilState(m_depthStencilState[depthStencilState], 0);
	}

private:
	ID3D11DepthStencilState* m_depthStencilState[enDepthStencilStateNum] = {nullptr};	//深度ステート
};
