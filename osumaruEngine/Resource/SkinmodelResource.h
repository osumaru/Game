#pragma once
class CSkelton;
//���f���f�[�^�̃��\�[�X���Ǘ�����N���X

class CSkinmodelResource : Uncopyable
{
public:
	/*
	filePath	�t�@�C���p�X
	skelton		��
	*/
	DirectX::Model* Load(const wchar_t* filePath, CSkelton* skelton = nullptr);

private:
	std::map<int, std::unique_ptr<DirectX::Model>> m_skinmodels;		//���f���f�[�^
};