#pragma once
//�萔�o�b�t�@�N���X

class ConstantBuffer
{
public:

	ConstantBuffer();

	~ConstantBuffer();

	void Create(int bufferSize, void* initData);

	void Update(void* updateData);

	ID3D11Buffer* GetBody()
	{
		return m_buffer;
	}
private:
	ID3D11Buffer*					m_buffer;
};

