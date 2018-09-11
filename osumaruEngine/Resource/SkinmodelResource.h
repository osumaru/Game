#pragma once
class CSkelton;
//モデルデータのリソースを管理するクラス

class CSkinmodelResource : Uncopyable
{
public:
	/*
	filePath	ファイルパス
	skelton		骨
	*/
	DirectX::Model* Load(const wchar_t* filePath, CSkelton* skelton = nullptr);

private:
	std::map<int, std::unique_ptr<DirectX::Model>> m_skinmodels;		//モデルデータ
};