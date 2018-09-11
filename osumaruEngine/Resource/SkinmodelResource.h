#pragma once
class CSkelton;

class CSkinmodelResource : Uncopyable
{
public:

	~CSkinmodelResource()
	{

	}

	DirectX::Model* Load(const wchar_t* filePath, CSkelton* skelton = nullptr);

private:
	std::map<int, std::unique_ptr<DirectX::Model>> m_skinmodels;
};