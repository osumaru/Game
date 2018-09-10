#pragma once
class CSkelton;

class CSkinmodelResource
{
public:
	DirectX::Model* Load(const wchar_t* filePath, CSkelton* skelton = nullptr);

private:
	std::map<int, std::unique_ptr<DirectX::Model>> m_skinmodels;
};