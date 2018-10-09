#pragma once

enum EnAlphaBlendState
{
	enAlphaBlendState2D,
	enAlphaBlendState3D,
	enAlphaBlendStateNum,
};

class CAlphaBlendState : Uncopyable
{
public:

	~CAlphaBlendState();

	void Init(ID3D11Device* device);


	void SetBlendState(ID3D11DeviceContext* deviceContext, EnAlphaBlendState enBlendState)
	{
		deviceContext->OMSetBlendState(m_blendState[enBlendState], NULL, 0xffffffff);
	}

private:
	ID3D11BlendState*		m_blendState[enAlphaBlendStateNum] = {nullptr};		//アルファブレンドステート
};