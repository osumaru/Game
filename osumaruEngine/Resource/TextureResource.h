#pragma once
class CTexture;
//�e�N�X�`���̃��\�[�X�Ǘ��N���X

class CTextureResource : Uncopyable
{
public:

	//�e�N�X�`�����擾
	CTexture* LoadTexture(const wchar_t* filePath);
private:
	std::map<int, std::unique_ptr<CTexture>> m_textures;	//�e�N�X�`��
};