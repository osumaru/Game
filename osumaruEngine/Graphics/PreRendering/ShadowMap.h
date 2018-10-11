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

	CRenderTarget& GetRenderTarget()
	{
		return m_renderTarget;
	}

private:
	std::vector<CSkinModel*>	m_modelList;
	CRenderTarget				m_renderTarget;
};