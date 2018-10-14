#pragma once
class CSkinModel;

class CShadowMap
{
public:

	void Init();

	void AddModel(CSkinModel* model)
	{
		m_modelList.push_back(model);
	}

	void Draw();

	void SetViewMatrix(CMatrix& viewMatrix)
	{
		m_viewMatrix = viewMatrix;
	}

	void SetProjectionMatrix(CMatrix& projectionMatrix)
	{
		m_projectionMatrix = projectionMatrix;
	}

	CMatrix& GetViewMatrix()
	{
		return m_viewMatrix;
	}

	CMatrix& GetProjMatrix()
	{
		return m_projectionMatrix;
	}

	CRenderTarget& GetRenderTarget()
	{
		return m_renderTarget;
	}

	void SetConstantBuffer();

private:
	std::vector<CSkinModel*>				m_modelList;
	CRenderTarget							m_renderTarget;
	CMatrix									m_viewMatrix;
	CMatrix									m_projectionMatrix;
	CConstantBuffer							m_CB;
};